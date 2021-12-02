/*******************************
 * Lab 3: uppgift 1             *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>



 /*******************************
  * 1. Declarations              *
  ********************************/


using pair = std::pair< std::string, int>;


// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
	const std::string& file_name, int n);


// Set all character in string to lowercase
void lowerCase(std::string& word) {

	std::transform(word.begin(), word.end(), word.begin(), std::tolower);
}

bool isPunc(const char& c) {
	// \"\" -  to include quotes
	// Chars to remove
	std::string chars = ".,!?:();\"";
	// std::string::npos is used to indicate no matches
	// and is defined with the value of -1
	// Return true if c is found in chars
	return chars.find(c) != std::string::npos;
}

void removeChar(std::string& word) {
	// Remove chars from string, 
	// Call function isPunc for every char in word
	word.erase(remove_if(word.begin(), word.end(), isPunc), word.end());

}

// Sort by frequency
bool sortBy(const pair& t1, const pair& t2) {
	// If the same amount of words
	if (t1.second == t2.second)
	{
		// sort alphabetically by word
		return(t1.first < t2.first);
	}

	return (t1.second > t2.second);
}


/*******************************
 * 2. Main function             *
 *******************************/

int main() {
	std::string name;
	std::cout << "Text file: ";
	std::cin >> name;

	std::ifstream in_File{ name };

	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

	std::map<std::string, int> table;
	int counter{ 0 };  // to count total number of words read from the input file


	std::string inWord;
	// While we find a new word in in_File
	while (in_File >> inWord)
	{

		// Remove special signs from inWord
		removeChar(inWord);
		// Set word to lowerCase
		lowerCase(inWord);

		table[inWord]++;

		//// Check if word exist in table
		//// Iterator for looping through table
		//std::map<std::string, int>::iterator it = table.find(inWord);
		//if (it != table.end()) { // FOUND

		//	// Increase int of word found
		//	table[inWord]++;
		//}
		//else { // NOT FOUND
		//	// Insert new word to table
		//	table.insert({ inWord, 1 });
		//}

		++counter;
	}

	std::vector<pair> freq;

	// Copy table to freq
	std::copy(table.begin(), table.end(), std::back_inserter(freq));
	// Sort freq by frequency
	std::sort(freq.begin(), freq.end(), sortBy);

	/* ************** Testing **************** */
	test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<pair>& v,
	const std::string& file_name, int n) {

	std::ifstream file{ "out_" + file_name };

	// Test if stream is in good state
	assert(bool(file) == true);

	std::map<std::string, int> result1;
	std::string word;
	int counter{ 0 };
	int total{ 0 };

	// load expected frequency table sorted alphabetically
	while (file >> word >> counter && counter > 0) {
		result1[word] = counter;
		total += counter;
	}

	assert(total == n);  // test if total number of words is correct
	assert(t == result1);

	std::vector<pair> result2;

	// load expected frequency table sorted by frequence
	while (file >> word >> counter) {
		result2.push_back(std::pair{ word, counter });
	}

	assert(v == result2);

	std::cout << "\nPassed all tests successfully!!\n";
}
