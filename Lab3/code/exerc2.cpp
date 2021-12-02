/*****************************************
 * Lab 4: uppgift 2                       *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>



using Map = std::map<std::string, std::set<std::string>>;
using Pair = std::pair<std::string, std::set<std::string>>;


// Define a testing function to check the contents of the anagrams Map
void test(const Map& t, const std::string& file_name);


struct Insert {
	// Constructor
	explicit Insert(Map& T) : T{ T } {
	}

	// Operator() to insert anagrams and subject 
	// String& w is an anagram
	void operator()(const std::string& w) {
		// Create a copy, which will be the subject for the anagram
		std::string subject = w;
		// Sort the copy alphabetically
		std::sort(std::begin(subject), std::end(subject));
		// Insert anagram for every subject
		T[subject].insert(w);

	}

private:
	Map& T;
};

// Class that prints out a word
struct PrintWord {
	// Constructor
	explicit PrintWord(std::ofstream& os) : os{ os } {
	}
	// Operator () that writes the word to an output file
	void operator()(const std::string& word) {
		os << word << " ";
	}

private:
	std::ofstream& os;
};

// Class to display all anagrams for one subject
struct Display {
	// Constructor
	explicit Display(std::ofstream& os) : os{ os } {
	}
	// Operator() that prints all anagrams for one subject
	// Then returns output fule
	// Takes a Pair as an argument
	std::ofstream& operator()(const Pair& T) {
		// Only print if there is more than 1 anagrams for the subject
		if (T.second.size() > 1)
		{
			// Call class PrintWord for every anagram
			std::for_each(T.second.begin(), T.second.end(), PrintWord{ os });
			os << " --> " << T.second.size() << " words.\n";
		}

		return os;
	}

private:
	std::ofstream& os;

};

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
	std::string name;
	std::cout << "Text file: ";
	std::cin >> name;

	// File to read in from
	std::ifstream in_File{ name };

	// Test if file is in good state
	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

	// Points to the beginning of the file
	auto inIt = std::istream_iterator<std::string>{ in_File };
	// Points to the end of the file
	auto inItEnd = std::istream_iterator<std::string>{};

	// Insert all words from file to vector words
	auto words = std::vector < std::string >(inIt, inItEnd);

	// Initialize new Map
	auto subjects = Map{};

	// For every word read from vector words
	// Insert to anagrams
	std::for_each(words.begin(), words.end(), Insert{ subjects });

	// new outFile
	std::ofstream utFil("ex2.txt");

	// Write to OutFile
	utFil << "Number of words = " << words.size() << "\n\n";
	utFil << "-- ANAGRAMS --\n";

	// Display all anagrams
	std::for_each(subjects.begin(), subjects.end(), Display{ utFil });

	// Call testing function
	test(subjects, name);
}

/*******************************
 *       Test function	       *
 *******************************/

void test(const Map& t, const std::string& file_name) {

	std::ifstream file{ "out_" + file_name };

	// Test if stream is in good state
	assert(bool(file) == true);

	Map result1;
	std::string anagram;

	// load expected anagram Map 
	while (file >> anagram) {
		std::string temp = anagram;
		// Sort alphabetically
		std::sort(std::begin(temp), std::end(temp));

		result1[temp].insert(anagram);

	}

	// Check that maps are equal
	assert(t == result1);

	std::cout << "\nPassed all tests successfully!!\n";
}
