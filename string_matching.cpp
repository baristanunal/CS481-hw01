// string_matching.cpp
#include "string_matching.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

const int alphabetSize = 4; // Size of the alphabet (A, C, T, G)

vector<vector<int>> StringMatching::bruteForce(const string& text, const vector<string>& patterns) {
    vector<vector<int>> matches(patterns.size());

    for (size_t i = 0; i < patterns.size(); ++i) {
        size_t patternSize = patterns[i].size();
        for (size_t j = 0; j <= text.size() - patternSize; ++j) {
            if (text.substr(j, patternSize) == patterns[i]) {
                matches[i].push_back(static_cast<int>(j + 1)); // Adjust indices to start from 1
            }
        }
        // If no match is found, add -1 to indicate no match
        if (matches[i].empty()) {
            matches[i].push_back(-1);
        }
    }

    return matches;
}


int StringMatching::hashFunction(char ch) {
    // Assign a unique number to each character in the alphabet
    switch(ch) {
        case 'A': return 0;
        case 'C': return 1;
        case 'T': return 2;
        case 'G': return 3;
        default: return -1; // Handle invalid characters
    }
}


vector<vector<int>> StringMatching::rabinKarp(const string& text, const vector<string>& patterns) {
    const int q = 101; // A prime number larger than the alphabet size

    vector<vector<int>> matches(patterns.size());

    // Iterate through all patterns
    for (size_t p = 0; p < patterns.size(); ++p) {
        const int m = patterns[p].size(); // Length of the current pattern

        // Calculate the value of c for the hash function
        int c = 1;
        for (int i = 0; i < m - 1; ++i) {
            c = (c * 10) % q;
        }

        int fp = 0; // Hash value for the current pattern
        int ft = 0; // Hash value for the first window in the text

        // Preprocessing: Calculate the hash values for the pattern and the first window in the text
        for (int i = 0; i < m; ++i) {
            fp = (10 * fp + hashFunction(patterns[p][i])) % q;
            ft = (10 * ft + hashFunction(text[i])) % q;
        }

        // Matching: Slide the window through the text and check for matches
        for (int s = 0; s <= text.size() - m; ++s) {
            if (fp == ft) {
                bool match = true;
                for (int i = 0; i < m; ++i) {
                    if (patterns[p][i] != text[s + i]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    matches[p].push_back(s + 1); // Adjust index to start from 1
                }
            }

            // Update the hash value for the next window in the text
            if (s < text.size() - m) {
                ft = ((ft - hashFunction(text[s]) * c) * 10 + hashFunction(text[s + m])) % q;
                if (ft < 0) {
                    ft += q; // Ensure the hash value is positive
                }
            }
        }

        // If no match is found, add -1 to indicate no match
        if (matches[p].empty()) {
            matches[p].push_back(-1);
        }
    }

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

    // Remove newline characters from the text
    string text = textBuffer.str();
    text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

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
