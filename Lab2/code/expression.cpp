/*********************************************************
 * Class Expression member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "expression.h"

 // Initialize the counter of the total number of existing Expressions
std::size_t Expression::count_expressions = 0;

// Used for debug purposes
// Return number of existing Expressions
std::size_t Expression::get_count_expressions() {
	return Expression::count_expressions;
}

//check if x is root of function
bool Expression::isRoot(int x) const {

	// get y value from function when x value is x
	//double sum = abs(this->operator()(x));
	double sum = abs((*this)(x));

	// check if y value is zero, 
	// then x is a zero point, (a root)
	if (sum < EPSILON)
	{
		return true;
	}

	return false;
}

// 
std::ostream& operator<<(std::ostream& os, const Expression& E)
{
	E.display(os); // dynamic binding
	return os;
}





/* ************************* */

