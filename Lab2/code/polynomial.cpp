/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <iomanip>
#include <iostream>
#include <math.h> // pow

 //Default constructor
//Polynomial::Polynomial()
//{ }

// Conversion constructor
//Creating a polynomial from a double
Polynomial::Polynomial(double v)
	: Polynomial{} // call default constructor
{
	values.push_back(v);
}

// Copy constructor
//Polynomial::Polynomial(const Polynomial& P) : Polynomial{} {
//
//	// copy vector from P to this vector
//	values = P.values;
//
//}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Polynomial::Polynomial(const std::vector<double>& V) :
	values{ V } {

	//values = V;

}


//// Destructor
//Polynomial::~Polynomial() {
//
//	// vector call its own destructor
//}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
//Polynomial& Polynomial::operator=(Polynomial P) {
//	// Swap the vector storing values
//	std::swap(values, P.values);
//	//values = L.values;
//
//
//	return *this;
//}

std::ostream& operator<<(std::ostream& os, const Polynomial& P) {
	P.display(os);
	return os;
}

// Can modify
double& Polynomial::operator[](int x) {

	return values[x];
}

// Return value
double Polynomial::operator[](int x) const {
	return values[x];
}


//Function call operator() for const objects
double Polynomial::operator()(double d) const {

	double sum = this->values[0];

	for (size_t i = 1; i < values.size(); i++)
	{
		sum += this->values[i] * (pow(d, i));
	}
	return sum;
}

// Addition of a polynomial 

void Polynomial::operator+=(const Polynomial& p) {

	// Check which vector is the smallest
	if (this->values.size() < p.values.size())
	{
		// Counter keeping track where in the vector we are
		int count = 0;

		// Loop through the smallest vector
		// Until count is the same size as the smallest vector
		// Add values from P to *this
		while (count != this->values.size())
		{
			this->values[count] += p.values[count];
			// Increase counter
			++count;
		}

		// If there is remain values in 
		while (count != p.values.size())
		{
			this->values.push_back(p.values[count]);
			++count;

		}
	}
	else {
		for (size_t i = 0; i < p.values.size(); i++)
		{
			this->values[i] += p.values[i];
		}
	}

}

// Addition of a polynomial and a double
void Polynomial::operator+=(double& d) {

	this->values[0] += d;

}

// add rhs to lhs
Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {

	// Call function operator +=
	lhs += rhs;

	return lhs;

}

// Return clone of logarithm
Polynomial* Polynomial::clone() const {

	return new Polynomial{ *this };

}

void Polynomial::display(std::ostream& os) const {
	os << std::fixed << std::setprecision(2);

	os << values[0];

	for (size_t i = 1; i < values.size(); i++)
	{
		os << " + " << values[i] << " * X^" << i;
	}

}


// ADD implementation of the member functions for class Polynomial