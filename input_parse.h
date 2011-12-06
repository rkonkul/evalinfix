/*
 * input_parse.h
 * Ryan Konkul
 * rkonku2
 * CS340
 * Project 3: evalInfix
 */

#ifndef INPUT_PARSE_H_
#define INPUT_PARSE_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>

//Returns true if a string has only digits
bool is_digit(std::string s);

//Returns true if char is one of the operands
bool isoperator(char c);

//Considers '-' as non digit
bool is_digit2(std::string s);

//Returns true if an operand such as ints and var names
bool is_operand(std::string s);

//Returns true if the string is an operator character
bool is_operator(std::string s);

//Returns true if complex part of complex number
bool is_complex(std::string s);

//Returns true if a variable (no digits)
bool is_variable(std::string s);

//Finds complex numbers and merges them in the vector
//[0]23 [1]+ [2]- [3]43.3i becomes [0]23+-43.3i
void merge_complex(std::vector<std::string>& infix);
void merge_complex_part2(std::vector<std::string>& infix, int i);

//Attaches negative signs if they are not operators
void merge_negatives(std::vector<std::string>& infix);

//Parses input into a vector of strings of operators and operands
void parse_raw_input(std::vector<std::string>& infix, std::string input);

//Extracts the variable and returns expression
std::string get_variable(std::string user_input, std::map<std::string, std::string>& variables);

#endif
