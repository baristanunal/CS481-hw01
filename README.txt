
# CS481 Homework 1
# Author:   Barış Tan Ünal
# Date:     01/03/2024
# Desc:     This program takes a pattern and a string as input and returns the runtime duration and indices of the string where the pattern is found.

# Contents
string_matching.cpp:    The main C++ source code file containing the implementation of the string matching algorithms.
string_matching.h:      Header file for the string matching class.
Makefile:               Makefile for compiling and building the executable.
README.txt:             This file, providing an overview of the project and instructions for use.

# Overview
This C++ program, string_matching.cpp, implements string matching algorithms to find occurrences of patterns within a given text. 
It currently supports the Brute-Force algorithm (BF) and the Rabin-Karp algorithm (RB).

# Prerequisites
C++ Compiler:       The code is written in C++ and requires a C++ compiler (e.g., g++).

# Compilation
To compile the code, use the provided Makefile. Open a terminal and navigate to the project directory, then run the following command:
make

This will compile the source code and generate an executable named 'sm'.

# Execution
To run the program, use the following command template:
./sm -t <text_file> -p <patterns_file> -m <BF/RB>

<text_file>:        The path to the text file containing the input text (accepts .fasta).
<patterns_file>:    The path to the patterns file containing the patterns to match (accepts .fasta).
<BF/RB>:            Specify the method to use for string matching. Use BF for brute-force or RB for Rabin-Karp.

# Example
./sm -t input.txt -p patterns.txt -m BF

# Cleaning Up
To clean up the compiled files, use the following command:
make clean

