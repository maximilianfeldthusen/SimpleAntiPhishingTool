
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

class PhishingChecker {
public:
    PhishingChecker(const std::string& phishingListPath) {
        loadPhishingUrls(phishingListPath);
    }

    bool isPhishing(const std::string& url) {
        // Handle case insensitivity by transforming both the url and phishing URLs to lowercase
        std::string lowerUrl = toLower(url);
        return std::find_if(phishingUrls.begin(), phishingUrls.end(), 
                             [&lowerUrl](const std::string& phishingUrl) {
                                 return toLower(phishingUrl) == lowerUrl;
                             }) != phishingUrls.end();
    }

private:
    std::vector<std::string> phishingUrls;

    void loadPhishingUrls(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << path << std::endl;
            return;
        }
        
        std::string url;
        while (std::getline(file, url)) {
            // Trim whitespace
            url = trim(url);
            if (!url.empty()) { // Avoid adding empty lines
                phishingUrls.push_back(url);
            }
        }
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return ""; // No content
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last - first + 1);
    }

    std::string toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
                       [](unsigned char c) { return std::tolower(c); });
        return lowerStr;
    }
};

int main() {
    PhishingChecker checker("phishing_urls.txt"); // Path to the phishing URLs file
    std::string url;

    std::cout << "Enter a URL to check: ";
    std::cin >> url;

    if (url.empty()) {
        std::cout << "No URL entered. Please provide a URL." << std::endl;
        return 1; // Exit with an error code
    }

    if (checker.isPhishing(url)) {
        std::cout << "The URL is potentially phishing. Access blocked!" << std::endl;
    } else {
        std::cout << "The URL is safe to access." << std::endl;
    }

    return 0;
}
