#include "CMyMatrix.h"
#include <iostream>
#include <cmath>

CMyMatrix::CMyMatrix() {
	CMyVektor vektor(2, 0.0);
	matrix.assign(2, vektor);
}

CMyMatrix::CMyMatrix(int dimension_N, int dimension_M) {
	CMyVektor vektor(dimension_M, 0.0);
	matrix.assign(dimension_N, vektor);
}

CMyMatrix& CMyMatrix::operator = (const CMyMatrix& orig) {
	matrix.clear();
	matrix = orig.matrix;
	return (*this);
}

CMyVektor& CMyMatrix::operator[](int index) {
	if (index < 0 || index >= matrix.size())
		std::cout << "Index ausserhalb der Reichweite\n";
	return matrix[index];
}

std::ostream& operator<<(std::ostream& out, CMyMatrix& orig) {
	for (int i = 0; i < orig.matrix[0].get_dimension(); i++) {
		out << "| ";
		for (int j = 0; j < orig.matrix.size(); j++) {
			out << std::to_string(orig.matrix[j][i]) << " ";
		}
		out << "|\n";
	}
	return out;
}

CMyMatrix CMyMatrix::invers() {
	CMyMatrix erg(2, 2);
	if (matrix[0].get_dimension() == 2 && matrix.size() == 2) {
		double a = matrix[0][0], b = matrix[1][0], c = matrix[0][1], d = matrix[1][1];
		double det = 1.0 / ((a * d) - (b * c));
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				this->matrix[x][y] *= det;
			}
		}
		erg.set_komponente(0, 0, this->matrix[1][1]);
		erg.set_komponente(0, 1, this->matrix[0][1] * -1);
		erg.set_komponente(1, 0, this->matrix[1][0] * -1);
		erg.set_komponente(1, 1, this->matrix[0][0]);
		
		return erg;
	}
	else {
		std::cout << "Fehlerhafte Matrix -> Falsche Dimension!" << std::endl;
		return erg;
	}
}