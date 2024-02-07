// g++ -std=c++11 main.cpp web_crawler_for_db.cpp -o crawler -lcurl

#include <iostream>
#include <thread>
#include "web_crawler.h"

int main() {
    std::string api_endpoint = "https://picsartacademy.am/";

    web_crawler crawler(api_endpoint, 1);

    // Uncomment the line below if you want to run crawling asynchronously
    crawler.get_thread() = std::thread(&web_crawler::start_crawling, &crawler);

    crawler.collect_user_data(api_endpoint);

    try {
        (crawler.get_thread()).join();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
