#include <iostream>
#include "CMyVector.h"
#include "CMyMatrix.h"
#include <cmath>

using namespace std;

CMyVektor operator*(CMyMatrix A, CMyVektor x) {
	CMyVektor erg(x.get_dimension());
	if (A.get_size() == x.get_dimension()) {
		for (int i = 0; i < A.get_CmyV_dimension(); i++) {
			for (int j = 0; j < x.get_dimension(); j++) {
				erg[i] += A[j][i] * x[j];
			}
		}
	}
	else {
		std::cout << "Fehlerhafte Multiplikation. Matrix-Vektor Multiplikation fehlgeschlagen\n";
		CMyVektor falsch;
		return falsch;
	}
	return erg;
}

CMyMatrix operator*(CMyMatrix A, double value) {
	for (int i = 0; i < A.get_CmyV_dimension(); i++) {
		for (int j = 0; j < A.get_size(); j++) {
			A[j][i] *= value;
		}
	}
	return A;
}

CMyMatrix jacobi(CMyVektor stelle, CMyVektor(*funktion)(CMyVektor x)) {
	double h = 1e-4;
	CMyVektor f = funktion(stelle);
	CMyMatrix jac(stelle.get_dimension(), f.get_dimension());
	CMyVektor stelle_x = stelle;
	for (int i = 0; i < f.get_dimension(); i++) {
		for (int j = 0; j < stelle.get_dimension(); j++) {
			stelle_x.set_komponente(j, stelle.get_komponente(j) + h);
			jac.set_komponente(j, i, (funktion(stelle_x)[i] - f[i]) / h);
			stelle_x.set_komponente(j, stelle.get_komponente(j));
		}
	}
	return jac;
}

CMyVektor Newtonverfahren(CMyVektor start, CMyVektor(*funktion)(CMyVektor x)) {
	CMyVektor x = start;
	CMyVektor fx = funktion(start);
	CMyMatrix jac(2, 2);
	CMyMatrix inv(2, 2);
	CMyVektor dx;
	double len = 0;
	if (x.get_dimension() == 2) {
		for (int i = 0; i < 50; i++) {
			cout << "\n======================================\n";
			cout << "Schritt " << i << ":\n";
			cout << "x = "; x.print();
			cout << "f(x) = "; fx.print();
			jac = jacobi(x, funktion);
			cout << "f'(x) =\n" << jac << endl;
			inv = jac.invers();
			cout << "(f'(x))^(-1) =\n" << inv << endl;
			fx *= -1.0;
			dx = inv * fx;
			cout << "dx = "; dx.print();
			len = fx.vektor_len();
			cout << "||f(x)|| = " << len << endl;
			x += dx;
			fx = funktion(x);
			if (fx.vektor_len() < 1e-5) {
				len = fx.vektor_len();
				cout << "\n======================================\n";
				cout << "\nEnde wegen ||f(x)|| < 1e-5 bei\n";
				cout << "x = "; x.print();
				cout << "f(x) = "; fx.print();
				cout << "||f(x)|| = " << len << endl;
				break;
			}
			else if (i == 50) {
				len = fx.vektor_len();
				cout << "\n======================================\n";
				cout << "\nDie 50 Schritte wurden erreicht\n";
				cout << "x = "; x.print();
				cout << "f(x) = "; fx.print();
				cout << "||f(x)|| = " << len << endl;
				break;
			}
		}
		return x;
	}
	else {
		cout << "Vektor ist zu klein oder zu gross !!!\n";
		return x;
	}
}

CMyVektor funktion(CMyVektor x)
{
	CMyVektor func(3);
	func[0] = x[0] * x[1] * exp(x[2]);
	func[1] = x[1] * x[2] * x[3];
	func[2] = x[3];
	return func;
}

CMyVektor funktion2(CMyVektor x) {
	CMyVektor funk(2);
	funk[0] = pow(x[0], 3) * pow(x[1], 3) - (2.0 * x[1]);
	funk[1] = x[0] - 2.0;
	return funk;
}

/*
double function(CMyVektor x) {
	return pow(x[0], 2) * sin(x[1] * x[2]);
}

double function_f(CMyVektor x) {
	return sin(x[0] * x[1]) + sin(x[0]) + cos(x[1]);
}

double function_g(CMyVektor x) {
	return (-(2 * pow(x[0], 2) - 2 * x[0] * x[1] + pow(x[1], 2) + pow(x[2], 2) - 2 * x[0] - 4 * x[2]));
}
*/
int main() {
/*
	CMyMatrix m(3, 2);
	CMyVektor v;
	m[0][0] = 4; m[0][1] = 1; m[1][0] = 3; m[1][1] = 2; m[2][0] = 2; m[2][1] = 3;
	vector<double>vec = { 2,3,4 };
	v(vec);

	cout << m << "\nmultipliziert mit\n\n" << v.print() << endl << endl;
	
	CMyVektor vneu = m * v;
	cout << "Ergebnis: " << vneu.print() << endl << endl;

	CMyMatrix mat(2, 2);
	mat[0][0] = 4; mat[0][1] = 1; mat[1][0] = 3; mat[1][1] = 2;
	cout << mat << endl << endl;
	mat.invers();
	cout << mat << endl << endl;

	CMyMatrix jack(2, 2);
	cout << jack << endl;
*/

	CMyVektor v;
	vector<double> vec = { 1 , 2 , 0 , 3 };
	v(vec);
	cout << "Stelle:" << endl;
    v.print();
	CMyMatrix v3(3, 4);
	v3 = jacobi(v, funktion);
	cout << "Jacobi Matrix" << endl;
	cout << v3;

/*
	CMyVektor v;
	vector<double> vec = { 1.0,1.0 };
	v(vec);
	CMyVektor vektor;
	vektor = Newtonverfahren(v, funktion2);
*/


	//CMyVektor vec;
	//vector<double> v = { 3,6,8 };
	//vec(v);
	//cout << "Vec: " << vec.print() << endl;
	//CMyVektor vec2;
	//vector<double> v2 = { 2,2,2 };
	//vec2(v2);
	//cout << "Vec2: " << vec2.print() << endl;
	//vec2 += vec;
	//cout << "Ergebnis Vec + Vec2: " << vec2.print() << endl << endl;
	//CMyVektor vector2;
	//vector<double> vector1 = { 2,1,3 };
	//vector2(vector1);
	//cout << "Numerischer Gradient von Vektor1 im Punkt (2,1,3) zu der Funktion: f(x,y,z) = x^2 *sin(y*z) betraegt : ";
	//CMyVektor vector3(vector2.gradient(vector2, function));
	//cout << vector3.print() << endl << endl;

	//CMyVektor s;
	//vector<double>punkt1 = { 0.2,-2.1 };
	//vector<double>punkt2 = { 0, 0, 0 };
	//s(punkt1); // f
	//CMyVektor grad;
	//CMyVektor s2;
	//grad.gradientenVerfahren(s, function_f, 1.0);
	//s2(punkt2); // g
	////grad.gradientenVerfahren(s2, function_g, 0.1);

	cout << "\n""\n";
	system("pause");
	return 0;
}