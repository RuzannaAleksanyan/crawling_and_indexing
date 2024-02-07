#include "web_crawler.h"

web_crawler::web_crawler(const std::string& api_endpoint, int num)
    : api_endpoint(api_endpoint), ID(num) {
    // No need to call thread.join() here
}

size_t web_crawler::write_callback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(reinterpret_cast<char*>(contents), totalSize);
    return totalSize;
}

void web_crawler::collect_user_data(const std::string& api_url) {
    // Check if apiUrl has the same domain as apiEndpoint
    if (!is_same_domain(api_url, api_endpoint)) {
        return;
    }

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_body;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            // Output clickable link
            std::cout << "\033]8;;" << api_url << "\a" << api_url << "\033]8;;\a" << std::endl;

            visited_users.insert(api_url);

            // Extract links from the current page
            std::set<std::string> links = extract_links(response_body);

            // Crawl through each link to fetch additional data
            for (const std::string& link : links) {
                if (visited_users.count(link) == 0) {
                    collect_user_data(link);
                }
            }

            // Set the inker content
            inker_content = response_body;
        }

        curl_easy_cleanup(curl);
    }
}

bool web_crawler::is_same_domain(const std::string& url1, const std::string& url2) {
    // Extract the host from each URL
    std::regex domainRegex(R"((https?://([^/]+)))");
    std::smatch match1, match2;

    if (std::regex_search(url1, match1, domainRegex) && std::regex_search(url2, match2, domainRegex)) {
        return match1[2] == match2[2];
    }

    return false;
}


std::set<std::string> web_crawler::extract_links(const std::string& htmlContent) {
    std::set<std::string> links;

    // Correct regex pattern for capturing links
    std::regex linkRegex("<a\\s+[^>]*\\s*href=[\"']([^\"']+)[\"'][^>]*>");

    std::sregex_iterator linkBegin(htmlContent.begin(), htmlContent.end(), linkRegex);
    std::sregex_iterator linkEnd;

    for (std::sregex_iterator it = linkBegin; it != linkEnd; ++it) {
        std::smatch match = *it;

        // Print the size of the match

        if (match.size() >= 2) {
            std::string link = match[1].str();
            links.insert(link);
        }
    }

    return links;
}

void web_crawler::crawl(const std::string& api_url, int depth) {
    if (depth > MAX_DEPTH || visited_users.count(api_url) > 0) {
        return;
    }

    collect_user_data(api_url);

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_body;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            std::set<std::string> links = extract_links(response_body);
            visited_users.insert(api_url);

            for (const std::string& link : links) {
                crawl(link, depth + 1);
            }
        }
        curl_easy_cleanup(curl);
    }
}

std::thread& web_crawler::get_thread() {
    return thread;
}

void web_crawler::start_crawling() {
    crawl(api_endpoint, 0);
}
