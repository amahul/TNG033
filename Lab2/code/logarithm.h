/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

#include "expression.h"
#include <vector>

class Logarithm : public Expression {
public:
	// Default constructor
	Logarithm();

	// Constructor: create a logarithm from arguments
	Logarithm(const Expression& inEx, const double inC1, const double inC2, const int inB);

	// Copy constructor
	Logarithm(const Logarithm& L);

	// Assignment operator
	Logarithm& operator=(Logarithm L);

	// Destructor
	~Logarithm();

	// Function call operator() for const objects
	// Override checks that the function is virtual and 
	// is overriding a virtual function from a base class
	double operator()(double d) const override;

	void set_base(int x);

	//clone(); Return a pointer to a copy of object o. Polymorphic copying
	Logarithm* clone() const override;

	// Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Logarithm& L);

private:
	double c1;
	double c2;
	int b;
	Expression* Ex;

	// Write out a logarithm
	void display(std::ostream& os) const override;

};
