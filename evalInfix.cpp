/*
 * evalInfix.cpp
 * Ryan Konkul
 * CS340
 * Project 3: STL
 * 10/18/11
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>
#include "Complex.h"
#include "input_parse.h"
#include <stack>
#include <vector>
#include <complex>
#include <string>
#include <set>
#include <map>

using namespace std;

inline void get_line(string &s) {
    cout.flush();
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, s);
    return;
}

string remove_ws(string s) {
    string no_ws = "";
    for(unsigned int i=0; i<s.size(); i++) {
        if(s[i] != ' ') {
            no_ws += s[i];
        }
    }
    return no_ws;
}

//Returns true if operand a has greater precedence than operand b.
bool is_op_less(string a, string b) {
    int prec_a = 0;
    int prec_b = 0;
    //encode precedence as ints
    if(a == "+" || a == "-") prec_a = 0;
    if(b == "+" || b == "-") prec_b = 0;
    if(a == "*" || a == "/") prec_a = 1;
    if(b == "*" || b == "/") prec_b = 1;
    if(a == "^") prec_a = 2;
    if(b == "^") prec_b = 2;
    if(a == "(" || a == ")") prec_a = 3;
    if(b == "(" || b == ")") prec_b = 3;
    return prec_a < prec_b;
}

//Returns true if operand a has greater precedence than operand b.
bool is_op_less_equal(string a, string b) {
    int prec_a, prec_b;
    //encode precedence as ints
    if(a == "+" || a == "-") prec_a = 0;
    if(b == "+" || b == "-") prec_b = 0;
    if(a == "*" || a == "/") prec_a = 1;
    if(b == "*" || b == "/") prec_b = 1;
    if(a == "^") prec_a = 2;
    if(b == "^") prec_b = 2;
    if(a == "(" || a == ")") prec_a = 3;
    if(b == "(" || b == ")") prec_b = 3;
    return prec_a <= prec_b;
}

void convert_to_postfix(vector<string>& infix, vector<string>& postfix, stack<string>& operators) {
	for(unsigned int i=0; i<infix.size(); i++) {
        if(infix[i] == "(")
        	operators.push("(");
        else if(infix[i] == ")") {
        	while(operators.top() != "(") {
        		postfix.push_back(operators.top());
        		operators.pop();
        	}
            operators.pop(); // pop the (
        } 
        else if(is_operand(infix[i])) {
            postfix.push_back(infix[i]);
        }
        else if(is_operator(infix[i])) {
            if(infix[i] != "^") {
               while(!operators.empty() && operators.top() != "(" && !is_op_less(operators.top(), infix[i])) {
                    if(infix[i] != "(")
                        postfix.push_back(operators.top());
                    operators.pop();
                }
                operators.push(infix[i]);
            }
            else {
                while(!operators.empty() && operators.top() != "(" && !is_op_less_equal(operators.top(), infix[i])) {
                    if(infix[i] != "(")
                        postfix.push_back(operators.top());
                    operators.pop();
                }
                operators.push(infix[i]);
            }
        }
        else cout << "Error: unidentified value" << endl;
	}
    while(!operators.empty()) {
        if(operators.top() != "(" && operators.top() != ")")
            postfix.push_back(operators.top());
        operators.pop();
    }
    cout << "Postfix form: ";
    for(unsigned int i=0; i<postfix.size(); i++) {
        cout << postfix[i] << " ";
    }
    cout << "\n";
}


string evaluation(string left, string optr, string right, map<string,string>& variables) {
    string result;
    std::ostringstream strs;
    if(is_variable(left)) { //get values from map if there are variables
        if(variables.find(left) == variables.end()) 
            cout << "\nError: variable " << left << " is not initialized";
        else
           left = variables[left];
    }
    if(is_variable(right)) {
        if(variables.find(right) == variables.end()) 
            cout << "\nError: variable " << right << " is not initialized";
        else
            right = variables[right];
    }
    if(is_complex_num(left) || is_complex_num(right)) { //if either are complex
        Complex c_left(left); //convert them to complex whether doubles or not
        Complex c_right(right);
        Complex res;
        if(optr == "+") {
            res = c_left + c_right;
            strs << res;
            result = res.to_string();
            strs.clear();
        }
        else if(optr == "-") {
            res = c_left - c_right;
            strs << res;
            result = res.to_string();
            strs.clear();
        }
        else if(optr == "*") {
            res = c_left * c_right;
            strs << res;
            result = res.to_string();
            strs.clear();
        }
        else if(optr == "/") {
            res = c_left / c_right;
            strs << res;
            result = res.to_string();
            strs.clear();
        }
        else if(optr == "^") {
            res = c_left ^ c_right;
            strs << res;
            result = res.to_string();
            strs.clear();
        }
    }
    else { //not variable not complex, so double
        double l = atof((char*)left.c_str());
        double r = atof((char*)right.c_str());
        double res;
        if(optr == "+") {
            res = l + r;
            strs << res;
            result = strs.str();
            strs.clear();
        }
        else if(optr == "-") {
            res = l - r;
            strs << res;
            result = strs.str();
            strs.clear();
        }
        else if(optr == "*") {
            res = l * r;
            strs << res;
            result = strs.str();
            strs.clear();
        }
        else if(optr == "/") {
            if(r == 0.0) {
                cout << "\nError: cannot divide by zero\n";
                res = l;
            }
            else 
                res = l / r;   
            strs << res;
            result = strs.str();
            strs.clear();
        }
        else if(optr == "^") {
            r = (int)r;
            if(r < 0) {
                cout << "\nError: can not have negative exponents.\n";
                res = (double)l;
            }
            else {
                res = pow(l , (double)r);
            }
            strs << res;
            result = strs.str();
            strs.clear();
        }
    }
    return result;
}
string eval_expression(vector<string>& infix, vector<string>& postfix, stack<string>& stck,
                       map<string,string>& variables) {

    convert_to_postfix(infix, postfix, stck);
    while(!stck.empty()) stck.pop(); //clear out stack
    string result;
    for(unsigned int i=0; i<postfix.size(); i++) {
        if(is_operand(postfix[i])) {
            stck.push(postfix[i]);
        }
        else if(is_operator(postfix[i])) {
            string right = "", left = "";
            if(!stck.empty())
                right = stck.top();
            else {
                cout << "Error\n";
                return "";
            }
            stck.pop();
            if(!stck.empty())
                left = stck.top();
            else {
                cout << "Error\n";
                return "";
            }
            stck.pop();
            string res = evaluation(left, postfix[i], right, variables);
            stck.push(res);
        }
    }
    if(stck.empty()) {
        cout << "Error\n";
        return "";
    }
    if(is_complex_num(stck.top())) {
        Complex temp(stck.top());
        stck.pop();
        stck.push(temp.to_string());
    }
	return stck.top();
}

bool command_read(istream& stream, set<string>& open_files, map<string,string>& variables) {
    string user_input;
    string no_ws_user_input = "";
    string multiple_line = "";
    bool quit = false;
    
    vector<string> expressions;
    stack<string> operands;
    //read in commands
    while(!quit && !stream.eof()) {
        if(stream == cin) //don't display prompt when reading files
            cout << ">";
        getline(stream, user_input);
        if(user_input.size() == 0) continue;
        while(user_input[user_input.size()-1] == '\\') { //if continuing line
            user_input = user_input.substr(0, user_input.size()-1);
            cout << "\nfound \\ \n" << user_input << "\n";
            multiple_line += user_input;
            get_line(user_input);
            multiple_line += user_input;
            user_input = multiple_line;
        }
        no_ws_user_input = remove_ws(user_input); //wipe out all the whitespace
        multiple_line = "";
        if(no_ws_user_input.size() == 1 && no_ws_user_input[0] == '.') 
            return true; //user wants to quit
        else if(no_ws_user_input.size() > 0 && no_ws_user_input[0] == '?') {
            cout << "\nThis is the help command. This program evaluates expressions by converting\n"
                 << "to postfix form and then doing the evaluation. You may enter expressions such\n"
                 << "as 3+3-9*1/4-(4+4i)\nand\n2+3i/-4.5+-2i/(4-2.2)\nThe result may be stored into a variable.\n"
                 << "The variable may not have numbers, only alphabetical characters. It may be \n"
                 << "entered as =variable(-3.4+2i)\nStores the value -3.4+2i into variable 'variable'.\n"
                 << "Spaces are not required but if there is a complex number it must have the plus\n"
                 << "sign before it such as -2+-4.4i\nEnter @[filename] to read commands from a file\n"
                 << "Enter #[string] to display the comment.\nEnter a single . to quit the program\n";
        }
        else if(no_ws_user_input.size() > 1 && no_ws_user_input[0] == '@') {
            string file = no_ws_user_input.substr(1,string::npos);
            cout << "Reading from file " << file << "\n";
            if(open_files.find(file) != open_files.end()) {
                cout << "Circular reference found in file " << file
                    << "\nIgnoring... " << endl;
            }
            else {
                ifstream file_stream((char*)file.c_str());
                open_files.insert(file); //insert into open files set
                quit = command_read(file_stream, open_files, variables);
                set<string>::iterator it = open_files.find(file);
                if(it != open_files.end())
                    open_files.erase(it); //remove from open files set
                else cout << "Bad error: could not find a file that should be in open_files";
            }
        }
        else if(no_ws_user_input.size() > 0 && no_ws_user_input[0] == '#') {
            cout << user_input << endl;
        }
        else {
            //expression eval
            vector<string> infix;
            parse_raw_input(infix, no_ws_user_input);
            if(infix.size() == 1 && is_variable(infix[0])) {
                if(variables.find(infix[0]) != variables.end())
                    cout << variables[infix[0]] << "\n";
                else
                    cout << "Error: variable " << infix[0] << " is not initialized" << endl;
                continue;
            }
            cout << "\n";
            if(infix.size() > 0 && infix[0] == "=") {
                if(infix.size()>2 && is_variable(infix[1])) {
                    string var_name = infix[1];
                    infix.erase(infix.begin(), infix.begin()+2);
                    string result = eval_expression(infix, expressions, operands, variables);
                    variables[var_name] = result; //store variable into map
                    expressions.clear(); //clear out expressions
                    while(!operands.empty()) operands.pop(); //clear stack
                }
                else
                    cout << "Error: must assign something some value" << endl;
            }
            else {
                bool ready = true;
                for(unsigned int i=0; i<infix.size(); i++) {
                    if(infix[i] == "-(") {
                        cout << "Error: negating parenthesized expressions do not work\n";
                        ready = false;
                    }
                }
                if(ready) {
                    string result = eval_expression(infix, expressions, operands, variables);
                    cout << result << endl;
                    expressions.clear(); //clear out expressions
                    while(!operands.empty()) operands.pop(); //clear stack
                }
            }
        }
    }
    return quit;
}

int main() {
    set<string> open_files;
    map<string, string> variables;//first string varname, second is value
    command_read(cin, open_files, variables);
    return 0;
}
