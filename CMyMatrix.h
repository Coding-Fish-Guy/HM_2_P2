#pragma once
#include "CMyVector.h"

class CMyMatrix {

public: std::vector<CMyVektor> matrix;

public:
	CMyMatrix();
	CMyMatrix(int dimension_N, int dimension_M);
	CMyMatrix(const CMyMatrix& orig) : matrix{ orig.matrix } {}
	~CMyMatrix() { matrix.clear(); }
	void erase() { matrix.clear(); }
	void add_dimension(const CMyVektor& vektor) { this->matrix.push_back(vektor); }
	void erase_dimension() { this->matrix.pop_back(); }
	int get_size() { return this->matrix.size(); }
	int get_CmyV_dimension() { return this->matrix[0].get_dimension(); }
	void set_komponente(int dimension_N, int dimension_M, double wert) { this->matrix[dimension_N][dimension_M] = wert; }
	double get_komponente(int dimension_N, int dimension_M) { return this->matrix[dimension_N][dimension_M]; }
	CMyMatrix& operator=(const CMyMatrix& orig);
	CMyVektor& operator[](int index);
	CMyMatrix invers();
	friend std::ostream& operator<<(std::ostream& out, CMyMatrix& orig);
};