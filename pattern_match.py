# CS481 Homework 1
# Author:  Barış Tan Ünal
# Date:   01/03/2024
# Desc:   This program takes a pattern and a string as input and returns the indices of the string where the pattern is found.

import argparse
import time
import sys
import os
import re

# Function Description: Brute Force String Matching. Provide the argument -m to specify the method as BF for Brute-force and RB for Rabin-Karp.
# Input 1:  A text file containing k patterns p to search. The file will hold one pattern per line. 
#           The path of this file will be passed as CLI argument to the program with the -p switch.
# Input 2: A text file containing a text to be searched. The file can have multiple lines.
#           The path of this file will be passed as CLI argument to the program with the -t switch.
# Output 1: Coordinates of the matches or no matches.
# Output 2: Total wall-clock time taken by your program.

import argparse
import time

def brute_force_matching(pattern, text):
    matches = []
    for i in range(len(text) - len(pattern) + 1):
        if text[i:i+len(pattern)] == pattern:
            matches.append(i + 1)  # Adjust index to start from 1 instead of 0
    return matches

def rabin_karp_matching(pattern, text):
    return

def main():
    parser = argparse.ArgumentParser(description="String Pattern Matching")
    parser.add_argument("-t", "--text", help="Path to the text file", required=True)
    parser.add_argument("-p", "--patterns", help="Path to the patterns file", required=True)
    parser.add_argument("-m", "--method", help="Matching method (BF for Brute-force, RB for Rabin-Karp)", required=True)
    args = parser.parse_args()

    with open(args.text, "r") as text_file:
        text = text_file.read().strip()

    with open(args.patterns, "r") as patterns_file:
        patterns = [pattern.strip() for pattern in patterns_file.readlines()]

    start_time = time.time()

    for pattern in patterns:
        if args.method == "BF":
            matches = brute_force_matching(pattern, text)
        elif args.method == "RB":
            matches = rabin_karp_matching(pattern, text)
        else:
            print("Invalid method. Please use BF or RB.")
            return

        print(f"match@ {matches}" if matches else "no matches")

    total_time = time.time() - start_time
    print(f"time: {total_time} seconds")

if __name__ == "__main__":
    main()





