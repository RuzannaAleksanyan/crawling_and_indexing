// g++ -std=c++17 main.cpp web_crawler.cpp -o crawler -lcurl -lgumbo

#include <iostream>
#include <filesystem>
#include "web_crawler.h"
#include "inverted_index.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <chrono>



int main() {
    const std::string start_url = "https://picsartacademy.am";
    web_crawler crawler(start_url, 1);
    crawler.start_crawling();

    // 

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
    // display_term_document_matrix_with_terms(inverted_index, filenames);

    display_inverted_index_with_string_docIDs(inverted_index);

    return 0;
}