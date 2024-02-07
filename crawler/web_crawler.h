#ifndef S_E
#define S_E

#include <iostream>
#include <thread>
#include <set>
#include <curl/curl.h>
#include <regex>

class web_crawler {
private:
    static const int MAX_DEPTH = 3;
    std::string api_endpoint;
    int ID;
    std::thread thread;
    std::set<std::string> visited_users;
    std::string inker_content; 

public:
    web_crawler(const std::string& api_endpoint, int num);

    static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output);

    void collect_user_data(const std::string& api_url);

    std::set<std::string> extract_links(const std::string& html_content);

    void crawl(const std::string& api_url, int depth);

    std::thread& get_thread();

    // void generateHTMLReport(const std::string& outputFileName);
    bool is_same_domain(const std::string& url1, const std::string& url2);

    std::string get_inker_content() const {
        return inker_content;
    }

    void start_crawling();
};

#endif  // S_E
