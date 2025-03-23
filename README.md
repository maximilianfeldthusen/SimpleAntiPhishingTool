
## Documentation

### SimpleAntiPhishingTool

This C++ code implements a simple phishing URL checker. It reads a list of known phishing URLs from a file and allows the user to input a URL to check if it is potentially phishing. Here's a breakdown of the code:

### Includes and Class Definition

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
```

- The code includes various header files:
    - `<iostream>`: for input and output operations.
    - `<fstream>`: for file handling.
    - `<string>`: for using strings.
    - `<vector>`: for using dynamic arrays.
    - `<algorithm>`: for algorithms such as searching and transforming.
    - `<cctype>`: for character classification functions (like `tolower`).
    - `<sstream>`: for working with string streams (not used in this code).

### PhishingChecker Class

```cpp
class PhishingChecker {
public:
    PhishingChecker(const std::string& phishingListPath) {
        loadPhishingUrls(phishingListPath);
    }
```

- The `PhishingChecker` class is defined to encapsulate the functionality of checking URLs against a list of phishing URLs.
- The constructor takes the path to a file containing phishing URLs and calls the `loadPhishingUrls` method to populate the list.

### Loading Phishing URLs

```cpp
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
            url = trim(url);
            if (!url.empty()) { 
                phishingUrls.push_back(url);
            }
        }
    }
```

- `phishingUrls`: A private vector that stores the list of phishing URLs.
- `loadPhishingUrls`: This method opens the file, reads each line (URL), trims whitespace, and adds non-empty URLs to the `phishingUrls` vector. If the file cannot be opened, it prints an error message.

### Trimming and Case Conversion

```cpp
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last - first + 1);
    }

    std::string toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
                       [](unsigned char c) { return std::tolower(c); });
        return lowerStr;
    }
```

- `trim`: This method removes leading and trailing spaces from a string.
- `toLower`: This method converts a string to lowercase to handle case insensitivity when checking URLs. It uses `std::transform` to apply the `std::tolower` function to each character in the string.

### Checking for Phishing URLs

```cpp
    bool isPhishing(const std::string& url) {
        std::string lowerUrl = toLower(url);
        return std::find_if(phishingUrls.begin(), phishingUrls.end(), 
                             [&lowerUrl](const std::string& phishingUrl) {
                                 return toLower(phishingUrl) == lowerUrl;
                             }) != phishingUrls.end();
    }
```

- `isPhishing`: This method checks if a given URL is in the list of phishing URLs. It converts the input URL to lowercase, then uses `std::find_if` to search the `phishingUrls` vector for a match, again using case-insensitive comparison.

### Main Function

```cpp
int main() {
    PhishingChecker checker("phishing_urls.txt"); 
    std::string url;

    std::cout << "Enter a URL to check: ";
    std::cin >> url;

    if (url.empty()) {
        std::cout << "No URL entered. Please provide a URL." << std::endl;
        return 1; 
    }

    if (checker.isPhishing(url)) {
        std::cout << "The URL is potentially phishing. Access blocked!" << std::endl;
    } else {
        std::cout << "The URL is safe to access." << std::endl;
    }

    return 0;
}
```

- In the `main` function, an instance of `PhishingChecker` is created, loading the phishing URLs from "phishing_urls.txt".
- The user is prompted to enter a URL. If the input is empty, an error message is displayed, and the program exits.
- The entered URL is then checked using the `isPhishing` method. Depending on the result, a message is printed to indicate whether the URL is safe or potentially phishing.

### Summary

Overall, this program is a basic phishing URL checker that reads a list of known phishing URLs from a file and allows the user to check if a given URL is potentially unsafe. It handles case insensitivity and whitespace trimming for accurate comparisons.
