#include "Normalized.h"
#include <sstream>
#include <cctype>

namespace Normalized {

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

std::string CollapseSpace(const std::string& str) {
    std::string trimmed = trim(str);
    std::string result;
    bool inSpace = false;
    for (char c : trimmed) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!inSpace) { result += ' '; inSpace = true; }
        } else {
            result += c;
            inSpace = false;
        }
    }
    return result;
}

std::string removeSymbols(const std::string& str) {
    const std::string FORBIDDEN = "|{}><~`#@!%^&():;";
    std::string result = str;
    for (char& c : result)
        if (FORBIDDEN.find(c) != std::string::npos) c = ' ';
    return CollapseSpace(result);
}

std::string toLower(const std::string& str) {
    std::string result = str;
    for (char& c : result)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return result;
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return result;
}

std::string NormalizedName(const std::string& rawName) {
    std::istringstream iss(removeSymbols(rawName));
    std::string word, result;
    while (iss >> word) {
        word = toLower(word);
        word[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(word[0])));
        if (!result.empty()) result += ' ';
        result += word;
    }
    return result;
}

std::string NormalizedId(const std::string& rawId) {
    std::string cleaned = toUpper(trim(rawId));
    std::string digits;
    for (char c : cleaned)
        if (std::isdigit(static_cast<unsigned char>(c))) digits += c;
    return digits.empty() ? cleaned : digits;   // decide your intended rule
}

std::string NormalizedProvinceCode(const std::string& tinhLe) {
    std::string code;
    bool startOfWord = true;
    char last = 0;
    for (unsigned char c : tinhLe) {
        if (c == ' ') { startOfWord = true; continue; }
        if (startOfWord) code += static_cast<char>(std::toupper(c));
        startOfWord = false;
        last = static_cast<char>(std::toupper(c));
    }
    if (last) code += last;
    return code;
}

} // namespace Normalized