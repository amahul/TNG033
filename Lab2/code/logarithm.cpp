/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <iomanip>



 // Default constructor
Logarithm::Logarithm()
	: c1{ 0 }, c2{ 1 }, b{ 2 } {

	std::vector<double> poly = { 0.0, 1.0 };

	Ex = new Polynomial{ poly };
}

// Constructor: create a logaritm from argument
Logarithm::Logarithm(const Expression& inEx, double inC1, double inC2, int inB)
	: c1{ inC1 }, c2{ inC2 }, b{ inB }, Ex{ inEx.clone() }{


}

// Copy constructor
Logarithm::Logarithm(const Logarithm& L)
	: c1{ L.c1 }, c2{ L.c2 }, b{ L.b }, Ex{ L.Ex->clone() }
{
	// make copy of L.ex
	//Ex = L.Ex->clone();
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Logarithm& Logarithm::operator=(Logarithm L) {

	// Swap the vector storing values

	std::swap(c1, L.c1);
	std::swap(c2, L.c2);
	std::swap(b, L.b);
	std::swap(Ex, L.Ex);

	return *this;
}

// Destructor
Logarithm::~Logarithm() {
	/*c1 = 0;
	c2 = 0;
	b = 0;*/
	delete Ex;
	Ex = nullptr;

}

void Logarithm::display(std::ostream& os)  const {

	os << std::fixed << std::setprecision(2);
	os << c1 << " + " << c2 << " * Log_" << b << "( " << *Ex << " )";
}

// Display logarithm
std::ostream& operator<<(std::ostream& os, const Logarithm& L) {

	L.display(os);

	return os;
}

// Return clone of logarithm
Logarithm* Logarithm::clone() const {
	return new Logarithm{ *this };

}

// Modifies the base of the logarithm to x
void Logarithm::set_base(int x) {
	b = x;
}

// Function call operator() for const objects
double Logarithm::operator()(double d) const {

	// log b (d) = log (d) / log(b) 

	double sum = c1 + c2 * (log((*Ex)(d)) / log(b));

	return sum;
}
// ADD implementation of the member functions for class Logarithm
