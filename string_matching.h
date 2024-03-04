/*
# CS481 Homework 1
# Author:  Barış Tan Ünal
# Date:   01/03/2024
# Desc:   This program takes a pattern and a string as input and returns the indices of the string where the pattern is found.
*/
#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#include <vector>
#include <string>

class StringMatching {
public:
    static std::vector<std::vector<int>> bruteForce(const std::string& text, const std::vector<std::string>& patterns);
    static std::vector<std::vector<int>> rabinKarp(const std::string& text, const std::vector<std::string>& patterns);
    static int hashFunction(char ch);
};

#endif // STRING_MATCHING_H
