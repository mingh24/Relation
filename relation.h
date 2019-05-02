#pragma once

#include<iostream>
using namespace std;

class Relation
{

protected:
	int dimension;
	int* matrix;

public:
	//====================================================================================================
	Relation(int d = 1);												// Construct an empty relation of dimension d.(If not specified, default is d = 1)
	Relation(int d, const int* M);								// Construct a relation from the dimension of its relational matrix and the array of the relational matrix
	Relation(const char* filename);							// Read the matrix of a relation from a file
	Relation(const Relation& r);								// Copy constructor
	Relation& operator =(const Relation& r);			// Overloaded of assignment operator
	~Relation();															// Destructor
	//====================================================================================================
	int getDimension() const;											// Get the dimension of relational matrix
	int getAtPosition(int row, int column) const;				//Gets the value at the cross position in row-th row and column-th column of the relational matrix, and this function returns -1 if it is over the boundary
	int operator() (int row, int column) const;					// You can use R(row, column) to get the value at the cross position in row-th row and column-th column of the relational matrix, and this function returns - 1 if it is over the boundary
	bool getMatrix(int* result) const;								// Get the relational matrix
	//====================================================================================================
	void output() const;													// Display the matrix of the relation on the screen
	bool outputToFile(const char* filename) const;			// Output to a file
	//====================================================================================================
	bool isReflexive() const;										// Determine whether this relation is reflexive or not
	bool isIrreflexive() const;										// Determine whether this relation is irreflexive or not
	bool isSymmetric() const;									// Determine whether this relation is symmetric or not
	bool isAsymmetric() const;									// Determine whether this relation is asymmetric or not
	bool isAntisymmetric() const;								// Determine whether this relation is antisymmetric or not
	bool isTransitive() const;										// Determine whether this relation is transitive or not
	//====================================================================================================
	Relation getReflexiveClosure() const;							// Get the relational matrix of its reflexive closure
	Relation getSymmetricClosure() const;						// Get the relational matrix of its symmetric closure
	Relation getTransitiveClosure() const;							// Get the relational matrix of its transitive closure
	//====================================================================================================
	bool isEquivalence() const;								// Determine whether this relation is an equalence relation or not
	//====================================================================================================
	bool getEquivalenceClasses(int* result) const;			/* If this relation is an equivalence relation, then stores the number of the equivalent class 
																							of the elements of the current relation (the number is started from 0) in the array result, and returnes true.
																							Otherwise, the value of any item in the array result is set as -1 and returnes false. */

};
