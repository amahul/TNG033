#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

#include "set.hpp"

int main() {
	/******************************************************
	 * TEST PHASE 0                                       *
	 * Default constructor                                *
	 * constructor: int -> Set                            *
	 * operator<<                                         *
	 ******************************************************/
	std::cout << "TEST PHASE 0: default constructor and constructor int -> Set\n";

	{
		Set S1{};
		assert(Set::get_count_nodes() == 1);


		Set S2{ -5 };
		assert(Set::get_count_nodes() == 3);

		// Test
		std::ostringstream os{};

		os << S1 << " " << S2;

		std::string tmp{ os.str() };

		assert((tmp == std::string{ "Set is empty! { -5 }" }));

	}

	assert(Set::get_count_nodes() == 0);

	/******************************************************
	 * TEST PHASE 1                                       *
	 * Constructor: create a Set from a non-sorted vector *
	 ******************************************************/
	std::cout << "\nTEST PHASE 1: constructor from a vector\n";


	{
		std::vector<int> A1{ 5, 3, 1 };
		std::vector<int> A2{ 4, 3, 4, 20, 15 };

		Set S1{ A1 };

		assert(Set::get_count_nodes() == 4);

		Set S2{ A2 };
		assert(Set::get_count_nodes() == 9);

		//Test
		std::ostringstream os{};
		os << S1 << " " << S2;

		std::string tmp{ os.str() };
		assert((tmp == std::string{ "{ 1 3 5 } { 3 4 15 20 }" }));
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 2                                       *
	// * Copy constructor                                   *
	// ******************************************************/
	std::cout << "\nTEST PHASE 2: copy constructor\n";

	{
		std::vector<int> A1{ 3, 3, 5, 1 };

		Set S1{ A1 };
		assert(Set::get_count_nodes() == 4);

		Set S2{ S1 }; // s2 = s1
		assert(Set::get_count_nodes() == 8);

		// Test
		std::ostringstream os{};
		os << S1 << " " << S2;

		std::string tmp{ os.str() };
		assert((tmp == std::string{ "{ 1 3 5 } { 1 3 5 }" }));
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 3                                       *
	// * Assignment operator: operator=                     *
	// ******************************************************/
	std::cout << "\nTEST PHASE 3: operator=\n";

	{
		Set S1{};

		assert(Set::get_count_nodes() == 1);

		std::vector<int> A1{ 1, 3, 5 };
		Set S2{ A1 };
		assert(Set::get_count_nodes() == 5);

		std::vector<int> A2{ 3, 8, 2, -1 };
		Set S3{ A2 };
		assert(Set::get_count_nodes() == 10);

		S1 = S2 = S3;
		assert(Set::get_count_nodes() == 15);

		// Test
		std::ostringstream os1{};
		os1 << S1 << " " << S2 << " " << S3;

		std::string tmp1{ os1.str() };
		assert((tmp1 == std::string{ "{ -1 2 3 8 } { -1 2 3 8 } { -1 2 3 8 }" }));

		S1 = Set{};
		assert(Set::get_count_nodes() == 11);

		// Test
		std::ostringstream os2{};
		os2 << S1;

		std::string tmp2{ os2.str() };
		assert((tmp2 == std::string{ "Set is empty!" }));
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 4                                       *
	// * member                                             *
	// ******************************************************/
	std::cout << "\nTEST PHASE 4: member\n";

	{
		std::vector<int> A1{ 5, 1, 3, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 4);

		// Test
		assert(S1.member(1));
		assert(S1.member(2) == false);
		assert(S1.member(3));
		assert(S1.member(5));
		assert(S1.member(99999) == false);
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 5                                       *
	// * cardinality                                        *
	// * empty                                              *
	// ******************************************************/
	std::cout << "\nTEST PHASE 5: cardinality and empty\n";

	{
		std::vector<int> A1{ 5, 1, 3, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 4);

		// Test
		assert(S1.cardinality() == 3);
		assert(S1.empty() == false);

		S1 = Set();
		assert(Set::get_count_nodes() == 1);
		assert(S1.empty());
	}

	assert(Set::get_count_nodes() == 0);

	///*****************************************************
	// * TEST PHASE 6                                       *
	// * Overloaded operators: equality, subset, and        *
	// * strict subset                                      *
	// ******************************************************/
	std::cout << "\nTEST PHASE 6: equality, subset, strict subset\n";

	{
		std::vector<int> A1{ 8, 3, 5, 1, 3 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 5);

		std::vector<int> A2{ 3, 5 };
		Set S2{ A2 };
		assert(Set::get_count_nodes() == 8);

		// Test
		assert(S2 <= S1);
		assert((S1 <= S2) == false);
		assert((S1 < S1) == false);
		assert((S1 == S2) == false);

		assert(S1 != S2);

		std::vector<int> A3{ 10, 3, 5, 8 };
		assert((Set{ A3 } <= S2) == false);
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 7                                       *
	// * Overloaded operator: union                         *
	// ******************************************************/
	std::cout << "\nTEST PHASE 7: union\n";

	{
		std::vector<int> A1{ 5, 3, 1, 8, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 5);

		std::vector<int> A2{ 2, 7, 3 };
		Set S2{ A2 };
		assert(Set::get_count_nodes() == 9);

		Set S3{};
		assert(Set::get_count_nodes() == 10);

		S3 = S1 + S2;
		assert(Set::get_count_nodes() == 16);

		// test
		std::vector<int> A3{ 1, 2, 3, 5, 7, 8 };
		assert(S3 == Set{ A3 });

		Set S4 = Set{} +S1 + Set{};
		assert(Set::get_count_nodes() == 21);

		assert(S4 == S1);
		assert(S1 + S1 == S1);
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 8                                       *
	// * Overloaded operator: intersection                  *
	// ******************************************************/
	std::cout << "\nTEST PHASE 8: intersection\n";

	{
		std::vector<int> A1{ 5, 3, 1, 8, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 5);

		std::vector<int> A2{ 2, 7, 3 };
		Set S2{ A2 };
		assert(Set::get_count_nodes() == 9);

		Set S3 = S1 * S2;
		assert(Set::get_count_nodes() == 11);

		// test
		std::vector<int> A3{ 3 };
		assert(S3 == Set{ A3 });

		assert(Set{} *S1 == Set{});
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 9                                       *
	// * Overloaded operator: difference                    *
	// ******************************************************/
	std::cout << "\nTEST PHASE 9: difference\n";

	{
		std::vector<int> A1{ 5, 3, 1, 8, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 5);

		std::vector<int> A2{ 2, 7, 3 };
		Set S2{ A2 };
		assert(Set::get_count_nodes() == 9);

		Set S3 = S1 - S2;

		// test
		std::vector<int> A3{ 1, 5, 8 };
		assert(S3 == Set{ A3 });

		assert(S1 - Set{} == S1);
		assert(Set{} -S1 == Set{});
		assert(S1 - S1 == Set{});
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 10                                      *
	// * Overloaded operators: mixed-mode set difference    *
	// ******************************************************/
	std::cout << "\nTEST PHASE 10: mixed-mode set difference\n";

	{
		std::vector<int> A1{ 5, 3, 1, 8, 1 };
		Set S1{ A1 };
		assert(Set::get_count_nodes() == 5);

		Set S2 = S1 - 5;
		assert(Set::get_count_nodes() == 9);

		// test
		std::vector<int> A2{ 1, 3, 8 };
		assert(S2 == Set{ A2 });

		S2 = S2 - 999;
		assert(S2 == S2);

		assert(Set{ 33 } -33 == Set{});
	}

	assert(Set::get_count_nodes() == 0);

	///******************************************************
	// * TEST PHASE 11                                      *
	// * Overloaded operators: union, intersection, and     *
	// * difference                                         *
	// ******************************************************/
	std::cout << "\nTEST PHASE 11: union, intersection, and difference\n";

	{
		std::vector<int> A1{ 1, 3, 5 };
		std::vector<int> A2{ 3, 2, 4 };
		std::vector<int> A3{ 10, 3 };

		Set S1{ A1 };
		Set S2{ A2 };
		Set S3{ A3 };
		assert(Set::get_count_nodes() == 11);

		S3 = S1 - 5 - (S1 + S2) - 99999;
		assert(Set::get_count_nodes() == 9);

		// test
		assert(S3 == Set{});

		std::ostringstream os{};

		os << ((S2 - 2) * (S1 + S3));

		std::string tmp{ os.str() };

		assert(((S2 - 2) * (S1 + S3)) == Set{ 3 });
	}

	assert(Set::get_count_nodes() == 0);

	std::cout << "\nSuccess!!\n";
}
