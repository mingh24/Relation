#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Relation {

protected:
	int dimension;
	int* matrix;

public:
	//====================================================================================================
	Relation(int d = 1);										// Construct an empty relation of dimension d.(If not specified, default is d = 1)
	Relation(int d, const int* M);								// Construct a relation from the dimension of its relational matrix and the array of the relational matrix
	Relation(const string filePath);							// Read the matrix of a relation from a file
	Relation(const Relation& r);								// Copy constructor
	Relation& operator =(const Relation& r);					// Overloaded of assignment operator
	~Relation();												// Destructor
	//====================================================================================================
	int getDimension() const;											// Get the dimension of relational matrix
	int getAtPosition(int row, int column) const;						// Get the value at the cross position in row-th row and column-th column of the relational matrix, and this function returns -1 if it is over the boundary
	int operator() (int row, int column) const;							// You can use R(row, column) to get the value at the cross position in row-th row and column-th column of the relational matrix, and this function returns - 1 if it is over the boundary
	int* getMatrix() const;												// Get the relational matrix
	//====================================================================================================
	void output() const;													// Display the matrix of the relation on the screen
	bool outputToFile(const string filePath) const;							// Output to a file
	//====================================================================================================
	bool isReflexive() const;										// Determine whether this relation is reflexive or not
	bool isIrreflexive() const;										// Determine whether this relation is irreflexive or not
	bool isSymmetric() const;										// Determine whether this relation is symmetric or not
	bool isAsymmetric() const;										// Determine whether this relation is asymmetric or not
	bool isAntisymmetric() const;									// Determine whether this relation is antisymmetric or not
	bool isTransitive() const;										// Determine whether this relation is transitive or not
	bool isEquivalence() const;										// Determine whether this relation is an equalence relation or not
	bool isPartial() const;											// Determine whether this relation is a partial ordering relation or not
	//====================================================================================================
	Relation getReflexiveClosure() const;								// Get the relation of its reflexive closure
	Relation getSymmetricClosure() const;								// Get the relation of its symmetric closure
	Relation getTransitiveClosure() const;								// Get the relation of its transitive closure
	Relation getEquivalenceClosure() const;								// Get the relation of its equivalence closure
	//====================================================================================================
	int* getEquivalenceClasses() const;						// Equivalence classes
	Relation hasse() const;									// Hasse graph
	int* topoSorting() const;								// Topologically sorting
};
