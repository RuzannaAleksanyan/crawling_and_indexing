// // g++ -std=c++17 main.cpp web_crawler.cpp -o crawler -lcurl -lgumbo

// #include <iostream>
// #include <filesystem>
// #include "web_crawler.h"
// #include "inverted_index.h"

// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <algorithm>
// #include <iterator>
// #include <chrono>
// #include <mutex>

// #include "httplib.h"

// std::mutex strMutex;

// // int main() {
//     // const std::string start_url = "https://picsartacademy.am";
//     // web_crawler crawler(start_url, 1);
//     // crawler.start_crawling();

//     // // 

//     // const std::string directory_path = std::filesystem::current_path();
//     // const std::string file_extension = ".txt";

//     // std::vector<std::string> filenames;

//     // try {
//     //     for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
//     //         // Check if the file has the desired extension
//     //         if (entry.path().extension() == file_extension) {
//     //             filenames.push_back(entry.path().filename().string());
//     //         }
//     //     }
//     // } catch (const std::filesystem::filesystem_error& ex) {
//     //     std::cerr << "Error accessing directory: " << ex.what() << std::endl;
//     // }

//     // std::vector<std::string> terms = { "brutus", "caesar", "noble", "window" };

//     // std::unordered_map<std::string, std::unordered_set<std::string>> inverted_index = build_inverted_index_with_string_docIDs(filenames);
//     // // display_term_document_matrix_with_terms(inverted_index, filenames);

//     // display_inverted_index_with_string_docIDs(inverted_index);

// //     return 0;
// // }




// int main() {
//     httplib::Server svr;

//     std::string str = "";

    // svr.Get("/extractWords", [&](const httplib::Request& req, httplib::Response& res) {
    //     res.set_header("Access-Control-Allow-Origin", "*");
    //     res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    //     res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, Accept");

    //     std::string queryString = req.get_param_value("query");

    //     std::istringstream iss(queryString);

    //     std::vector<std::string> words;

    //     std::string word;
    //     while (iss >> word) {
    //         words.push_back(word);
    //     }

    //     std::lock_guard<std::mutex> lock(strMutex);
    //     str += "{ \"words\": [";
    //     for (size_t i = 0; i < words.size(); ++i) {
    //         str += words[i];
    //         if (i < words.size() - 1) {
    //             str += ", ";
    //         }
    //     }
    //     str += "] }";

    //     // res.set_content(str.c_str(), "application/json");  // Use str.c_str() to get a C-style string
    // });

    // std::thread serverThread([&]() {
    //     svr.listen("localhost", 8080);
    // });

    // std::this_thread::sleep_for(std::chrono::seconds(15));

    // // Stop the server after 15 seconds
    // svr.stop();

    // // Join the server thread
    // serverThread.join();

    // // Lock the mutex before accessing str in the main thread
    // std::lock_guard<std::mutex> lock(strMutex);

    // std::string start_url = "https://";
    // start_url += str;
    // std::cout << "............." << std::endl;
    // std::cout << str << std::endl;
    // std::cout << start_url << std::endl;
    // std::cout << "............." << std::endl;
//     // web_crawler crawler(start_url, 1);
//     // crawler.start_crawling();

//     // const std::string directory_path = std::filesystem::current_path();
//     // const std::string file_extension = ".txt";

//     // std::vector<std::string> filenames;

//     // try {
//     //     for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
//     //         // Check if the file has the desired extension
//     //         if (entry.path().extension() == file_extension) {
//     //             filenames.push_back(entry.path().filename().string());
//     //         }
//     //     }
//     // } catch (const std::filesystem::filesystem_error& ex) {
//     //     std::cerr << "Error accessing directory: " << ex.what() << std::endl;
//     // }

//     // std::vector<std::string> terms = { "brutus", "caesar", "noble", "window" };

//     // std::unordered_map<std::string, std::unordered_set<std::string>> inverted_index = build_inverted_index_with_string_docIDs(filenames);
//     // // display_term_document_matrix_with_terms(inverted_index, filenames);

//     // display_inverted_index_with_string_docIDs(inverted_index);
//     // //

//     // // std::cout << "Server listening on port 8080..." << std::endl;

//     // // svr.listen("localhost", 8080);
    
//     // std::cout << str << std::endl;

//     return 0;
// }



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

std::mutex strMutex;  // Declare strMutex globally

int main() {
    httplib::Server svr;

    std::string str = "";

    svr.Get("/extractWords", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, Accept");

        std::string queryString = req.get_param_value("query");

        std::istringstream iss(queryString);

        std::vector<std::string> words;

        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        std::lock_guard<std::mutex> lock(strMutex);
        // str += "{ \"words\": [";
        for (size_t i = 0; i < words.size(); ++i) {
            str += words[i];
            if (i < words.size() - 1) {
                str += ", ";
            }
        }
        // str += "] }";

        // res.set_content(str.c_str(), "application/json");  // Use str.c_str() to get a C-style string
    });

    std::thread serverThread([&]() {
        svr.listen("localhost", 8080);
    });

    std::this_thread::sleep_for(std::chrono::seconds(15));

    // Stop the server after 15 seconds
    svr.stop();

    // Join the server thread
    serverThread.join();

    // Lock the mutex before accessing str in the main thread
    std::lock_guard<std::mutex> lock(strMutex);

    std::string start_url = "https://";
    start_url += str;
    std::cout << "............." << std::endl;
    std::cout << str << std::endl;
    std::cout << start_url << std::endl;
    std::cout << "............." << std::endl;

    // Continue with the rest of your code...

    return 0;
}

