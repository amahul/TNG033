/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include "expression.h"

class Polynomial : public Expression {
public:
	// Default constructor
	Polynomial() = default;

	// Conversion constructor
	//Creating a polynomial from a double
	Polynomial(double v);

	// Copy Constructor
	Polynomial(const Polynomial& P) = default;

	//Assignment operator
	//Polynomial& operator=(Polynomial p);
	Polynomial& operator=(const Polynomial& L) = default;

	// Constructor: create a set with the elements in V
	// V is not sorted and may contain repeated elements
	explicit Polynomial(const std::vector<double>& V);

	// Destructor
	~Polynomial() = default;

	//Addition of 2 polynoms
	void operator+=(const Polynomial& p);

	// Addition of a polynom and a double
	void operator+=(double& d);

	// Operator +
	friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs);

	// Function call operator() for const objects
	// Override checks that the function is virtual and 
	// is overriding a virtual function from a base class
	double operator()(double d) const override;




	// Function able to modify the value in values[x]
	double& operator[](int x);
	double operator[](int x) const;

	// Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& P);

	// return clone of Polynomial
	Polynomial* clone() const override;

private:
	std::vector<double> values; // create vector
	// Write out a logarithm
	void display(std::ostream& os) const override;


};
