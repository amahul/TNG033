#include "set.hpp"

// size_t is defined in the C++ standard library
// size_t is an unsigned integer type that can store the maximum size of any possible object

// Initialize the counter of the total number of existing nodes
size_t Set::Node::count_nodes = 0;

// Used for debug purposes
// Return number of existing nodes
size_t Set::get_count_nodes() {
	return Set::Node::count_nodes;

}

/* ******************************************************** */

// Default constructor
Set::Set()
	: counter{ 0 }, head{ new Node } { // Member initializer list

}

// Constructor for creating a set from an int
Set::Set(int v)
	: Set{} // call default constructor
{
	insert(head, v); // insert node after head with value v

}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V)
	: Set{} {

	// copy V to nyVec
	std::vector<int> nyVec = V;
	Node* temp = head;
	// sort new vector
	std::sort(nyVec.begin(), nyVec.end());

	for (size_t i = 0; i < nyVec.size(); i++) // loop through copied vector
	{
		if (!((i != nyVec.size() - 1) && (nyVec[i] == nyVec[i + 1]))) // check if a value is equal to next value, & don't check last value in vec
		{
			insert(temp, nyVec[i]); // insert new node if value in nyVec is not equal to next value
			temp = temp->next;
		}
	}
}

// copy constructor
Set::Set(const Set& source)
	: Set{} { // call default constructor

	Node* temp = head;
	Node* tempSource = source.head->next;

	while (tempSource != nullptr) // while node in source still points to another node
	{
		insert(temp, tempSource->value); // insert value to this set
		temp = temp->next;
		tempSource = tempSource->next;

	}

}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {

	// swap pointer of head
	std::swap(head, s.head);

	//swap value of counter
	std::swap(counter, s.counter);

	return *this;
	//Destructer is callded for s and deallocates old memory
}

// Destructor: deallocate all nodes
Set::~Set() {
	//temporary pointer to first node
	Node* temp = head->next;

	while (temp != nullptr) // while node points to another node
	{
		remove(head);
		head = temp; // set head to next node
		temp = temp->next; // set temp to next node
	}
	remove(head); // remove the last node
	head = nullptr;

}

// Test if x is an element of the set
bool Set::member(int x) const {

	Node* CheckNode = head->next;

	while (CheckNode != nullptr) // while node in this set points to another node
	{
		if (CheckNode->value == x) // return true if value in this set is equal to x
		{
			return true;
		}
		CheckNode = CheckNode->next; // move to next node
	}
	return false; // if x is not found, return false
}

// Test if set is empty
bool Set::empty() const {

	// return true if counter is 0, else false
	return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {

	return counter;
}

// Check if b is a subset of this set
bool Set::operator<=(const Set& b) const {

	Node* r = head->next;

	while (r != nullptr) // while the node still points at a node
	{
		// check if value from r does not exist in set b
		// then return false
		if (!(b.member(r->value)))
		{
			return false;
		}
		r = r->next;
	}

	return true; // return true if all values in r exists in b
}


// check if b is equal to this set
bool Set::operator==(const Set& b) const {
	// check if *this is subset of b and b is subset of *this
	/*if (*this <= b && b <= *this) {
		return true;
	}*/
	// else return false
	return (*this <= b && b <= *this);
}

// Check if B is not equal to this set
bool Set::operator!=(const Set& b) const {

	// call operator ==
	// return false if b is equal to this set
	/*if (b == *this) {
		return false;
	}
	else {
		return true;
	}*/
	return (!(b == *this));

}

// Check is b is a proper subset of this set
bool Set::operator<(const Set& b) const {

	if (b == *this) { // check that set is not equal, then it is not a proper subset
		return false;
	}
	else {
		return (*this <= b); // check if b is a subset of this set
	}

}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {

	Set Merged{};
	Node* in = Merged.head;
	Node* p1 = head->next;
	Node* p2 = b.head->next;

	while (p1 != nullptr && p2 != nullptr) // while both nodes still points to a next node
	{

		if (p1->value < p2->value) // insert value from p1 if smaller
		{
			Merged.insert(in, p1->value);
			p1 = p1->next; // move to next node in p1
		}
		else if (p1->value == p2->value) // insert one of the values if equal
		{
			Merged.insert(in, p1->value);
			// move to next node in p1 & p2
			p1 = p1->next;
			p2 = p2->next;

		}
		else { // insert value from p2 if smaller
			Merged.insert(in, p2->value);
			p2 = p2->next; // move to next node in p2

		}
		in = in->next; // move to next node in Merged
	}

	// add remaining values from p1
	while (p1 != nullptr)
	{
		Merged.insert(in, p1->value);
		in = in->next;
		p1 = p1->next;

	}

	// add remaining values from p2
	while (p2 != nullptr)
	{

		Merged.insert(in, p2->value);
		in = in->next;
		p2 = p2->next;

	}

	return Merged;

}

// Set intersection
Set Set::operator*(const Set& b) const {

	Set Intersect{};
	Node* in = Intersect.head;

	Node* p1 = head->next;

	while (p1 != nullptr) // while node still points to another node
	{
		if (b.member(p1->value)) // check if value from this set exists in b
		{
			Intersect.insert(in, p1->value);
			in = in->next;
		}
		p1 = p1->next;

	}

	return Intersect;
}

// Set difference
Set Set::operator-(const Set& b) const {

	Set Diff{};

	Node* in = Diff.head;

	Node* p1 = head->next;

	while (p1 != nullptr) // while node still points to another node
	{
		if (!(b.member(p1->value))) // check if value from this set doed not exists in b
		{
			Diff.insert(in, p1->value);
			in = in->next;
		}
		p1 = p1->next;

	}

	return Diff;
}

// set difference with set {x}
Set Set::operator-(int x) const {

	// create a new set with node with value x
	Set Temp{ x };

	Set Res = *this - Temp; // call operator that return set with difference of R and S

	return Res;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
	if (theSet.empty()) {
		os << "Set is empty!";
	}
	else {
		Set::Node* temp = theSet.head->next;
		os << "{ ";

		while (temp != nullptr) {
			os << temp->value << " ";
			temp = temp->next;
		}
		os << "}";
	}
	return os;
}

/********** Private member functions ************/

// Insert a new node after node pointed by p
// the new node should store value
void Set::insert(Node* p, int value) {
	// create new empty node
	Node* newNode = new Node(value, p->next);
	// set value of node
	//newNode->value = value;
	// link the new node to the node after p
	//newNode->next = p->next;
	// link p to the new node
	p->next = newNode;
	// increase counter with 1
	++counter;

}

// Remove the node pointed by p
void Set::remove(Node* p) {


	delete p;
	// decrease counter with 1
	--counter;
}
