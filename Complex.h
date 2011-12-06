/*
 * Complex.h
 * Ryan Konkul
 * rkonku2
 * CS340
 * Project 3: evalInfix
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <iostream>

class Complex {
private:
	double real_;
	double imag_;

public:
	//Constructs a complex number initialized to zero
	Complex();
    //Constructs a complex from a string
    Complex(std::string s);
	//Converts a double into a Complex
	Complex(double p);
	//Constructs a complex number real + imag*i
	Complex(double real, double imag = 0);
    //Converts to a string
    std::string to_string();
	//Negates the real and imaginary number
	Complex operator-();
	//Multiplies two complex numbers using polynomial multiplication
	Complex operator*(Complex);
	//Exponentiates a complex number
	//Left side is the base, right is the exponent
	friend Complex operator^(Complex c1, Complex c2);
	//Divides a Complex number
	friend Complex operator/(Complex c1, Complex c2);
	//Adds two Complex together
	friend Complex operator+(Complex c1, Complex c2);
	//Subtracts two Complex
	friend Complex operator-(Complex c1, Complex c2);
	//Assignment operator
	Complex& operator=(const Complex& c);
	//Outputs the Complex number
	friend std::ostream& operator<<(std::ostream& stream, Complex& c);
};

//Determines if the string is a Complex number
bool is_complex_num(std::string s);

#endif /* COMPLEX_H_ */
