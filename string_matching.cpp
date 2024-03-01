// string_matching.cpp
#include "string_matching.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

vector<vector<int>> StringMatching::bruteForce(const string& text, const vector<string>& patterns) {
    vector<vector<int>> matches(patterns.size());

    for (size_t i = 0; i < patterns.size(); ++i) {
        size_t patternSize = patterns[i].size();
        for (size_t j = 0; j <= text.size() - patternSize; ++j) {
            if (text.substr(j, patternSize) == patterns[i]) {
                matches[i].push_back(static_cast<int>(j + 1)); // Adjust indices to start from 1
            }
        }
    }

    return matches;
}

vector<vector<int>> StringMatching::rabinKarp(const string& text, const vector<string>& patterns) {
    // TODO: Implement Rabin-Karp algorithm
    // Note: This is a placeholder. You need to complete this function.
    vector<vector<int>> matches(patterns.size());
    
    // Your Rabin-Karp algorithm implementation goes here
    
    return matches;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " -t <text_file> -p <patterns_file> -m <BF/RB>\n";
        return 1;
    }

    string textFile, patternsFile, method;
    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-t") {
            textFile = argv[i + 1];
        } else if (arg == "-p") {
            patternsFile = argv[i + 1];
        } else if (arg == "-m") {
            method = argv[i + 1];
        } else {
            cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    ifstream textStream(textFile);
    ifstream patternsStream(patternsFile);

    if (!textStream.is_open() || !patternsStream.is_open()) {
        cerr << "Error opening input files.\n";
        return 1;
    }

    stringstream textBuffer, patternsBuffer;
    textBuffer << textStream.rdbuf();
    patternsBuffer << patternsStream.rdbuf();

    string text = textBuffer.str();
    vector<string> patterns;
    string pattern;

    while (getline(patternsBuffer, pattern)) {
        patterns.push_back(pattern);
    }

    auto start = high_resolution_clock::now();

    vector<vector<int>> matches;
    if (method == "BF") {
        matches = StringMatching::bruteForce(text, patterns);
    } else if (method == "RB") {
        matches = StringMatching::rabinKarp(text, patterns);
    } else {
        cerr << "Invalid method. Use BF for Brute-force or RB for Rabin-Karp.\n";
        return 1;
    }

    auto stop = high_resolution_clock::now();
    auto elapsed_time = duration_cast<duration<double>>(stop - start);

    for (size_t i = 0; i < matches.size(); ++i) {
        cout << "match@ [";
        for (size_t j = 0; j < matches[i].size(); ++j) {
            cout << matches[i][j];
            if (j < matches[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]\n";
    }

    cout << fixed << setprecision(6);  // Set precision to 6 decimal places
    cout << "time: " << elapsed_time.count() << "s\n";

    return 0;
}