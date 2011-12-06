/*
 * Complex.cpp
 * Ryan Konkul
 * rkonku2
 * CS340
 * Project 3: evalInfix
 */

#include "Complex.h"
#include <iostream>
#include <sstream>
#include <complex>

using namespace std;

Complex::Complex() {
	real_ = 0.0;
	imag_ = 0.0;
}

Complex::Complex(string s) {
    if((signed) s.find_first_of('i') != -1) { //if complete form
        unsigned int i=0;
        while(i < s.size() && s[i] != '+') 
            ++i;
        real_ = atof((char*)s.substr(0, i).c_str());
        ++i; // skip over required '+'
        imag_ = atof((char*)s.substr(i, s.size() - i - 1).c_str());
    }
    else {//just a double
        real_ = atof((char*)s.substr(0, string::npos).c_str());
        imag_ = 0;
    }
}

Complex::Complex(double p) {
	real_ = p;
	imag_ = 0.0;
}

Complex::Complex(double real, double imag) {
	real_ = real;
	imag_ = imag;
}

string Complex::to_string() {
    string s = "";
    string a;
    stringstream ostr;
    if(imag_ == 0) {
        ostr << real_;
    }
     else {
         ostr << real_ << "+" << imag_ << "i";
     }
    s = ostr.str();
    return s;
}

Complex Complex::operator-() {
	return Complex(-real_, -imag_);
}

Complex Complex::operator*(Complex c) {
    Complex result;
    //Using polynomial multiplication
    //(a+bi)(c+di) = ac + adi + bci - bd
    // = (ac - bd) + (ad + bc)i
    result.real_ = (real_ * c.real_) - (imag_ * c.imag_);
    result.imag_ = (real_ * c.imag_) + (imag_ * c.real_);
    return result;
}

Complex operator^(Complex c1, Complex c2) {
    complex<double> copy1(c1.real_, c1.imag_);
    complex<double> copy2(c2.real_, c2.imag_);
    complex<double> res = pow(copy1, copy2);
    Complex result(res.real(), res.imag());
    return result;
}

Complex operator/(Complex c1, Complex c2) {
    Complex result;
    double a,b,c,d;
    a = c1.real_;
    b = c1.imag_;
    c = c2.real_;
    d = c2.imag_;
    // (a + bi) / (c + di)
    // = (a + bi)(c - di) / (c + di)(c - di)
    // = (ac + bd) + i(bc - ad) / (cc + dd)
    // = [(ac + bd) / (cc + dd)] + [(bc - ad) / (cc + dd)]
    double denom = (c*c) + (d*d);
    result.real_ = ((a*c) + (b*d)) / denom;
    result.imag_ = ((b*c) - (a*d)) / denom;
    return result;
}

Complex operator+(Complex c1, Complex c2) {
    Complex result;
    result.real_ = c1.real_ + c2.real_;
    result.imag_ = c1.imag_ + c2.imag_;
    return result;
}

Complex operator-(Complex c1, Complex c2) {
    Complex result;
    result = -c2;
    result = c1 + result;
    return result;
}

Complex& Complex::operator=(const Complex& c) {
	if(this != &c) {
        real_ = c.real_;
        imag_ = c.imag_;
	}
	return *this;
}

ostream& operator<<(ostream& stream, Complex& c) {
	if(c.imag_ != 0) {
        stream << c.real_ << " + " << c.imag_ << "i\n";
	}
	else {
		stream << c.real_ << "\n";
	}
    return stream;
}

//Determines if the string is a Complex number
bool is_complex_num(string s) {
    int num_i = 0; int num_p = 0;
    for(unsigned int i=0; i<s.size(); i++) {
        if(s[i] == 'i') num_i++;
        if(s[i] == '+') num_p++;
    }
    if(num_i == 1 && num_p == 1 && s.size() > 3) {
        unsigned int i=0;
        while(s[i] != '+') {
            if(s[i] != '-' && s[i] != '.' && !isdigit(s[i])) {
                return false;
            }
            ++i;
        }
        ++i; //skip the '+'
        while(s[i] != 'i') {
            if(s[i] != '-' && s[i] != '.' && !isdigit(s[i])) {
                return false;
            }
            ++i;
        }
        return true;
    }
    else {
        return false;
    }
}

