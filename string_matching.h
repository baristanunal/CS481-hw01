// string_matching.h
#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#include <vector>
#include <string>

class StringMatching {
public:
    static std::vector<std::vector<int>> bruteForce(const std::string& text, const std::vector<std::string>& patterns);
    static std::vector<std::vector<int>> rabinKarp(const std::string& text, const std::vector<std::string>& patterns);
};

#endif // STRING_MATCHING_H
