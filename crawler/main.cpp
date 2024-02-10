// g++ -std=c++17 main.cpp web_crawler.cpp inverted_index.cpp -o crawler -lcurl -lgumbo

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <mutex>
#include <thread>

#include "httplib.h"
#include "web_crawler.h"
#include "inverted_index.h"

std::mutex str_mutex;

std::string clean_and_organize_URL() {
    httplib::Server svr;

    std::string str = "";

    svr.Get("/extractWords", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, Accept");

        std::string query_string = req.get_param_value("query");

        std::istringstream iss(query_string);

        std::vector<std::string> words;

        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        std::lock_guard<std::mutex> lock(str_mutex);
        for (size_t i = 0; i < words.size(); ++i) {
            str += words[i];
            if (i < words.size() - 1) {
                str += ", ";
            }
        }

        res.set_content(str.c_str(), "application/json");  // Use str.c_str() to get a C-style string
    });

    std::thread serverThread([&]() {
        svr.listen("localhost", 8080);
    });

    std::this_thread::sleep_for(std::chrono::seconds(20));

    // Stop the server after 20 seconds
    svr.stop();

    // Join the server thread
    serverThread.join();

    // Lock the mutex before accessing str in the main thread
    std::lock_guard<std::mutex> lock(str_mutex);

    std::string start_url = "https://";
    start_url += str;

    return start_url;
}

int main() {
    std::string start_url = clean_and_organize_URL();

    web_crawler crawler(start_url, 1);
    crawler.start_crawling();

    const std::string directory_path = std::filesystem::current_path();
    const std::string file_extension = ".txt";

    std::vector<std::string> filenames;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
            // Check if the file has the desired extension
            if (entry.path().extension() == file_extension) {
                filenames.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
    }

    std::vector<std::string> terms = { "brutus", "caesar", "noble", "window" };

    std::unordered_map<std::string, std::unordered_set<std::string>> inverted_index = build_inverted_index_with_string_docIDs(filenames);
    display_term_document_matrix_with_terms(inverted_index, filenames);

    // display_inverted_index_with_string_docIDs(inverted_index);

    // std::cout << "Server listening on port 8080..." << std::endl;

    // svr.listen("localhost", 8080);

    // Delete files
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
            // Check if the file has the desired extension
            if (entry.path().extension() == file_extension) {
                // Delete the file
                std::filesystem::remove(entry.path());
            }
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
    }

    return 0;
}

