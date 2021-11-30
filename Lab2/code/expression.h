/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

constexpr double EPSILON = 1.0e-5;

class Expression {
public:
	// Call for destrucot
	// Good programming practice to declare virtual destructor in base class
	virtual ~Expression() {
		--count_expressions;
	}

	// Check if x is a root to the expression
	bool isRoot(int x) const;

	// Return number of existing instances of class Expression
	// Used for debug purposes
	static std::size_t get_count_expressions();

	//Overloaded function for const objects
	virtual double operator()(double d) const = 0;

	//clone(); Return a pointer to a copy of object o. Polymorphic copying
	virtual Expression* clone() const = 0; //No need to define function in base class, use functions i subclasses instead

	// Virtual assignment operator
	//virtual Expression& operator=(const Expression& E);



	// Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Expression& E);

protected:
	// Default constructor
	Expression() {
		++count_expressions;
	}

	// Copy constructor
	Expression(const Expression&) {
		++count_expressions;
	}

	// Total number of existing expressions -- to help to detect bugs in the code
	static std::size_t count_expressions;

	//Display function in subclasses
	virtual void display(std::ostream& os) const = 0;

	// Cannot call assignment operator from main for two different expressions
	Expression& operator=(const Expression& e) = default;
};
