/*
 * input_parse.cpp
 * Ryan Konkul
 * rkonku2
 * CS340
 * Project 3: evalInfix
 */

#include "input_parse.h"
#include "Complex.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

//Returns true if a string has only digits
bool is_digit(string s) {
	for(unsigned int i=0; i<s.size(); i++) {
		if(!isdigit(s[i]) && s[i] != '.' && s[i] != '-' && s[i] != 'i')
	        return false;
	}
	return true;
}

//Returns true if char is one of the operators
bool isoperator(char c) {
    if(c == '-' || c == '+' || c == '*' ||
        c == '(' || c == ')' || c == '^' || c == '/' || c == '=')
        return true;
    return false;
}

//Considers '-' as non digit
bool is_digit2(string s) {
	for(unsigned int i=0; i<s.size(); i++) {
		if(!isdigit(s[i]) && s[i] != '.' && s[i] != 'i')
	        return false;
	}
	return true;
}

//Returns true if an operand such as ints and var names
bool is_operand(string s) {
    if(s.size() == 1 && s[0] == '-') return false;
    if(is_complex_num(s)) return true;
    for(unsigned int i=0; i<s.size(); i++) {
        if(isoperator(s[i]) && s[i] != '-') {
            return false;
        }
    }
    return true;
}

//Returns true if the string is an operator character
bool is_operator(string s) {
    if(s.size() == 1 && isoperator(s[0]))
        return true;
    return false;
}

//Returns true if complex part of complex number
bool is_complex(string s) {
	for(unsigned int i=0; i<s.size()-1; i++) {
        if(!isdigit(s[i]) && s[i] != '.' && s[i] != '-')
		    return false;
	}
	if(s[s.size()-1] != 'i') {
		return false;
	}
    return true;
}

//Returns true if a variable 
bool is_variable(std::string s) {
    if(s.size()>0 && isdigit(s[0])) return false;
    for(unsigned int i=0; i<s.size(); i++) {
        if(!isalnum(s[i])) return false;
    }
    return true;
}

void merge_complex_part2(vector<string>& infix, int i) {
	if(is_digit(infix[i])) { //if found real part of complex number
         if(infix.size() > (unsigned)(i+2) && infix[i+1] == "+") { //see a plus sign next
        	 if(infix[i+2] == "-") { //negative might be part of complex
        		 if(infix.size() > (unsigned)(i+3) && is_complex(infix[i+3])) { //if found complex part
       			 string build = ""; //rebuild into one string
        			 build += infix[i] + infix[i+1] + infix[i+2] + infix[i+3];;
        			 infix[i] = build; //assign it
        			 infix.erase(infix.begin()+i+1, infix.begin()+i+4); //erase already merged parts
        			 i=0; //check again
        		 }
        	 }
        	 else if(is_complex(infix[i+2])) { //if found complex part
        		 string build = "";
        		 build += infix[i] + infix[i+1] + infix[i+2];
        		 infix[i] = build;
        		 infix.erase(infix.begin()+i+1, infix.begin()+i+3);
        		 i=0;// check again
        	 }
         }
	}
}

//Finds complex numbers and merges them in the vector
//[0]23 [1]+ [2]- [3]43.3i becomes [0]23+-43.3i
void merge_complex(vector<string>& infix) {
    for(unsigned int i=0; i<infix.size(); i++) {
    	merge_complex_part2(infix, i);
    }
}

//Attaches negative signs if they are not operators
void merge_negatives(vector<string>& infix) {
	if(infix.size() > 1 && infix[0] == "-") {
		string build = "";
		build += "-" + infix[1];
		infix[0] = build;
		infix.erase(infix.begin()+1);
	}
    for(unsigned int i=0; i<infix.size(); i++) {
        if(is_operator(infix[i]) && infix.size() > (i+2) && infix[i+1] == "-" && !is_operator(infix[i+2])) {
        	string build = "";
        	build += infix[i+1] + infix[i+2];
        	infix[i+1] = build;
        	infix.erase(infix.begin()+i+2);
        	i=0;
        }
    }
}

//Parses input into a vector of strings of operators and operands
void parse_raw_input(vector<string>& infix, string input) {
	string builder = "";
    for(unsigned int i=0; i<input.size(); i++) {
    	if(isdigit(input[i]) || input[i] == '.' || input[i] == 'i') {
    		//first split all operands. assume negatives are operands
    		//but place i and . next to the numbers
            while(isdigit(input[i]) || input[i] == '.' || input[i] == 'i') {
                builder += input[i];
                i++;
                if(i>=input.size()) break;
            }
            i--;
            infix.push_back(builder);
            builder = "";
    	}
    	else if(isoperator(input[i])) {
    		if(builder.size() > 0) {
    			//if building the string, save it
    			infix.push_back(builder);
    			builder = "";
    		}
    		string temp = string(1, input[i]);
    		infix.push_back(temp);
    	}
        else {
            while(i<input.size() && !isoperator(input[i]) && !isdigit(input[i])) {
                builder += input[i];
                i++;
                if(i>=input.size()) break;
            }
            i--;
            infix.push_back(builder);
            builder = "";
        }
    }
    if(builder != "") {
        infix.push_back(builder);
        builder = "";
    }
    merge_negatives(infix);
    merge_complex(infix);
}
