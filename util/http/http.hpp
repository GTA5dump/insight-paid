#pragma once
#include <curl/curl.h>

namespace insight {
    class curl_wrapper {
    public:
        curl_wrapper() {
            curl_global_init(CURL_GLOBAL_ALL);
            curl = curl_easy_init();
        }
        ~curl_wrapper() {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
        }
        bool set_url(const std::string& url) {
            return curl_easy_setopt(curl, CURLOPT_URL, url.c_str()) == CURLE_OK;
        }
        bool set_follow_location(bool follow) {
            return curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, follow ? 1L : 0L) == CURLE_OK;
        }
        bool set_header(const std::string& header) {
            headers = curl_slist_append(headers, header.c_str());
            return curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers) == CURLE_OK;
        }
        bool set_headers(CURL* curl, curl_slist*& headers, const std::vector<std::string>& hdrs) {
            // Initialize headers
            headers = nullptr;

            for (const auto& header : hdrs) {
                headers = curl_slist_append(headers, header.c_str());
                if (!headers) {
                    // Handle memory allocation error
                    return false;
                }
            }

            // Set the HTTP headers
            return curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers) == CURLE_OK;
        }

        bool set_post_fields(const std::string& fields) {
            bool ret = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str()) == CURLE_OK;
            if (ret) {
                ret = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(fields.length())) == CURLE_OK;
            }
            return ret;
        }
        bool set_write_function(curl_write_callback callback) {
            return curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback) == CURLE_OK;
        }
        bool set_write_data(void* data) {
            return curl_easy_setopt(curl, CURLOPT_WRITEDATA, data) == CURLE_OK;
        }
        CURLcode perform() {
            return curl_easy_perform(curl);
        }
        std::string post(const std::string& url, const std::string& data, const std::vector<std::string>& headers = {}) {
            set_url(url);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            set_follow_location(true);

            // Initialize headers
            curl_slist* curl_headers = nullptr;
            for (const auto& header : headers) {
                curl_headers = curl_slist_append(curl_headers, header.c_str());
                if (!curl_headers) {
                    // Handle memory allocation error
                    throw std::runtime_error("Failed to append headers");
                }
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);

            set_post_fields(data);
            set_write_function(write_callback);
            set_write_data(&response_body);

            CURLcode result = perform();

            // Clean up headers
            curl_slist_free_all(curl_headers);

            if (result != CURLE_OK) {
                throw std::runtime_error("Curl error: " + std::string(curl_easy_strerror(result)));
            }

            return response_body;
        }
    private:
        CURL* curl;
        struct curl_slist* headers;
        std::string response_body;
        std::string response_headers;

        static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* data) {
            size_t num_bytes = size * nmemb;
            std::string* response = static_cast<std::string*>(data);
            response->append(ptr, num_bytes);
            return num_bytes;
        }
        static size_t header_callback(char* ptr, size_t size, size_t nmemb, void* data) {
            size_t num_bytes = size * nmemb;
            std::string* response = static_cast<std::string*>(data);
            response->append(ptr, num_bytes);
            return num_bytes;
        }
    };

    extern nlohmann::json send_request(nlohmann::json body, std::string endpoint);
}