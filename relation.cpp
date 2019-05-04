#include "relation.h"

//---------------------------------------------------------------------------------------------------

Relation::Relation(int d) {
	// Construct an empty relation of dimension d
	dimension = d;
	matrix = new int[dimension * dimension];
	memset(matrix, 0, sizeof(int) * dimension * dimension);
}

Relation::Relation(int d, const int* m) {
	// Construct a relation from the dimension of its relational matrix and the array of the relational matrix
	dimension = d;
	matrix = new int[dimension * dimension];
	memcpy(matrix, m, sizeof(int) * dimension * dimension);
}

Relation::Relation(const string filePath) {
	// Read the matrix of a relation from a file
	ifstream readStream(filePath);
	if (!readStream) {
		cout << "Fail to open." << endl;
		exit(1);
	}
	else {
		int row, column;
		readStream >> dimension;
		matrix = new int[dimension * dimension];
		for (row = 0; row < dimension; row++)
			for (column = 0; column < dimension; column++)
				readStream >> matrix[row * dimension + column];
	}
	readStream.close();
}

Relation::~Relation() {
	// Destructor
	delete[] matrix;
}

Relation::Relation(const Relation & r) {
	dimension = r.dimension;
	matrix = new int[dimension * dimension];
	memcpy(matrix, r.matrix, sizeof(int) * dimension * dimension);
}

Relation& Relation::operator =(const Relation & r) {
	dimension = r.dimension;
	matrix = new int[dimension * dimension];
	memcpy(matrix, r.matrix, sizeof(int) * dimension * dimension);
	return *this;
}

//---------------------------------------------------------------------------------------------------

int Relation::getDimension() const {
	// Get the dimension of relational matrix
	return dimension;
}

int Relation::getAtPosition(int row, int column) const {
	// Gets the value at the cross position in column-th column and flags-th flags of the relational matrix, and this function returns -1 if it is over the boundary.
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return matrix[row * dimension + column];
	else
		return -1;
}

int Relation::operator()(int row, int column) const {
	// You can use R(flags, jcolumn) to get the value at the cross position in flags-th flags and column-th column of the relational matrix, and this function returns - 1 if it is over the boundary.
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return matrix[row * dimension + column];
	else
		return -1;
}

int* Relation::getMatrix() const {
	// Get the relational matrix
	return matrix;
}

void Relation::output() const {
	// Display the matrix of the relation on the screen
	int row, column;
	cout << "The dimension is: " << dimension << endl;
	for (row = 0; row < dimension; row++)
	{
		for (column = 0; column < dimension; column++)
		{
			cout << (*this)(row, column) << "   ";
		}
		cout << endl;
	}
}

bool Relation::outputToFile(const string filePath) const {
	// Write the relation matrix to a file in the same format as the read file
	ofstream writeStream(filePath);
	if (!writeStream) {
		cout << "Fail to open." << endl;
		return false;
	}
	else {
		int row, column;
		writeStream << dimension << endl;
		for (row = 0; row < dimension; row++) {
			for (column = 0; column < dimension; column++)
				writeStream << matrix[row * dimension + column] << "   ";
			writeStream << endl;
		}
	}
	writeStream.flush();
	writeStream.close();
	return true;
}

bool Relation::isReflexive() const {
	int row;
	// Traverse all elements on the main diagonal
	for (row = 0; row < getDimension(); ++row) {
		if (getAtPosition(row, row) == 0)
			return false;
	}
	return true;
}

bool Relation::isIrreflexive() const {
	int row;
	// Traverse all elements on the main diagonal
	for (row = 0; row < getDimension(); ++row) {
		if (getAtPosition(row, row) == 1)
			return false;
	}
	return true;
}

bool Relation::isSymmetric() const {
	int row, column;
	// Traverse all elements in the martrix
	for (row = 0; row < getDimension(); ++row) {
		for (column = 0; column < getDimension(); ++column) {
			if (getAtPosition(row, column) != getAtPosition(column, row))
				return false;
		}
	}
	return true;
}

bool Relation::isAsymmetric() const {
	int row, column;
	// Traverse all elements in the martrix
	for (row = 0; row < getDimension(); ++row) {
		for (column = 0; column < getDimension(); ++column) {
			if (getAtPosition(row, column) == 1 && getAtPosition(column, row) == 1)
				return false;
		}
	}
	return true;
}

bool Relation::isAntisymmetric() const {
	int row, column;
	// Traverse all elements in the martrix
	for (row = 0; row < getDimension(); ++row) {
		for (column = 0; column < getDimension(); ++column) {
			if (getAtPosition(row, column) == 1 && getAtPosition(column, row) == 1 && row != column)
				return false;
		}
	}
	return true;
}

bool Relation::isTransitive() const {
	// Traverse all elements in the martrix, and check whether the third element is in relation R
	for (int i = 0; i < getDimension(); ++i) {
		for (int j = 0; j < getDimension(); ++j) {
			if (getAtPosition(i, j) == 1) {
				for (int k = 0; k < getDimension(); ++k) {
					if (getAtPosition(j, k) == 1 && getAtPosition(i, k) != 1)
						return false;
				}
			}
		}
	}
	return true;
}

bool Relation::isEquivalence() const {
	return isReflexive() && isSymmetric() && isTransitive();
}

bool Relation::isPartial() const {
	return isReflexive() && isAntisymmetric() && isTransitive();
}

Relation Relation::getReflexiveClosure() const {
	int* m = new int[dimension * dimension];
	m = getMatrix();

	int row;
	// Traverse all elements on the main diagonal
	for (row = 0; row < dimension; ++row) {
		if (m[row * dimension + row] == 0)
			m[row * dimension + row] = 1;
	}
	Relation r(dimension, m);
	return r;
}

Relation Relation::getSymmetricClosure() const {
	int* m = new int[dimension * dimension];
	m = getMatrix();

	int* transpose = new int[dimension * dimension];
	int row, column;

	// Get the transposed matrix
	for (row = 0; row < dimension; ++row) {
		for (column = 0; column < dimension; ++column) {
			transpose[row * dimension + column] = m[column * dimension + row];
		}
	}

	// Traverse all elements in the martrix
	for (row = 0; row < dimension; ++row) {
		for (column = 0; column < dimension; ++column) {
			if (m[row * dimension + column] == 1 || transpose[row * dimension + column] == 1) {
				m[row * dimension + column] = 1;
			}
		}
	}

	Relation r(dimension, m);
	return r;
}

Relation Relation::getTransitiveClosure() const {
	int* m = new int[dimension * dimension];
	m = getMatrix();

	for (int times = 0; times < dimension; ++times) {
		for (int row = 0; row < dimension; ++row) {
			for (int column = 0; column < dimension; ++column) {
				if (row != times || column != times) {
					if (m[times * dimension + column] == 1 && m[row * dimension + times] == 1)
						m[row * dimension + column] = 1;
				}
			}
		}
	}

	Relation r(dimension, m);
	return r;
}

Relation Relation::getEquivalenceClosure() const {
	return this->getReflexiveClosure().getSymmetricClosure().getTransitiveClosure();
}

int* Relation::getEquivalenceClasses() const {
	int row, column, number = 0;
	int* result = (int*)malloc(sizeof(int) * dimension);

	//if (isEquivalence()) {
	for (row = 0; row < dimension; ++row) {
		result[row] = number;
		++number;
	}
	for (row = 0; row < dimension; ++row) {
		for (column = 0; column < dimension; ++column) {
			if (getAtPosition(row, column) == 1) {
				result[column] = result[row];
			}
		}
	}
	return result;
	//}

	//return 0;
}

int* Relation::topologicallySorting() const {
	int* vertices = (int*)malloc(sizeof(int) * dimension);
	int* arcs = getMatrix();
	int* result = (int*)malloc(sizeof(int) * dimension);
	int* flags = (int*)malloc(sizeof(int) * dimension);	// 按照列来设置标志，为1表示已经输出（不再考虑），为0表示未输出。
	int flag = 1;									// 标志符，1表示已经输出（不再考虑），为0表示未输出，赋给flags数组

	for (int i = 0; i < dimension; ++i) {
		flags[i] = 0;
		vertices[i] = i;
		result[i] = 0;
	}

	int i, j, k, m = 0, t;
	int s = 0;

	for (i = 0; i < dimension; ++i) {
		for (j = 0; j < dimension; ++j) {
			if (flags[j] == 0) {				//	活动j还未输出
				t = 1;		// 标识符
				for (k = 0; k < dimension; ++k)
					if (arcs[k * dimension + j] == 1) {		//当前活动有入度（活动k必须在活动j之前）
						t = 0;
						break;
					}
				if (t == 1) {		// 活动j没有入度
					m = j;
					break;
				}
			}
		}
		if (j != dimension) {
			flags[m] = flag;
			result[s++] = vertices[m];
			for (k = 0; k < dimension; ++k)
				arcs[m * dimension + k] = 0;		// 将已经输出的活动所到达的下个活动的入度置为0
			flag++;
		}
		else
			break;
	}

	if (flag - 1 < dimension) {	// 当flags中不是所有的元素都被赋予新值v时，说明有环存在
		return nullptr;
	}

	return result;
}