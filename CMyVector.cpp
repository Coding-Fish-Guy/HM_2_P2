#include <iostream>
#include <cmath>
#include "CMyVector.h"

void CMyVektor::insert(int stelle, double wert) {
	auto pos = vektor.begin() + stelle;
	vektor.insert(pos, wert);
}

double CMyVektor::vektor_len() {
	double summe = 0;
	for (auto it = vektor.begin(); it != vektor.end(); it++) {
		summe += pow(*it, 2.0);
	}
	return sqrt(summe);
}

void CMyVektor::set_dimension(int dimension, int value) {
	vektor.clear();
	vektor.assign(dimension, value);
}

CMyVektor CMyVektor::operator+=(CMyVektor a) {
	if (a.get_dimension() == this->get_dimension()) {
		for (int i = 0; i != a.get_dimension(); i++) {
			this->vektor[i] += a.vektor[i];
		}
	}
	return *this;
}
CMyVektor CMyVektor::operator*=(double lambda) {
	for (int i = 0; i < this->get_dimension(); i++) {
		this->vektor[i] *= lambda;
	}
	return *this;
}

CMyVektor operator+(CMyVektor a, CMyVektor b) {

	for (int i = 0; i < a.get_dimension(); i++) {
		a.set_komponente(i, a.get_komponente(i) + b.get_komponente(i));
	}
	return a;
}

CMyVektor operator*(double lambda, CMyVektor a) {

	for (int i = 0; i < a.get_dimension(); i++) {
		a.set_komponente(i, a.get_komponente(i) * lambda);
	}
	return a;
}

void CMyVektor::print() {
	std::cout << "( ";
	for (int z = 0; z < this->get_dimension(); z++) {
		std::cout << this->get_komponente(z);
		if (z != this->get_dimension() - 1) {
			std::cout << " , ";
		}
	}
	std::cout << " )" << std::endl;
}


CMyVektor CMyVektor::gradient(CMyVektor x, double (*function)(CMyVektor x)) {
	CMyVektor x_stelle = x;
	CMyVektor Gradient;
	Gradient.vektor_anlegen(x.get_dimension());
	double tmp = 0.0;
	double h = pow(10, -8);
	for (int i = 0; i < x.get_dimension(); i++) {
		x_stelle.set_komponente(i, x.get_komponente(i) + h);
		//funktion "für kleine h" wird ausgeführt und ergebnis in 'tmp' gespeichert
		tmp = ((function(x_stelle) - function(x)) / h);
		x_stelle.set_komponente(i, x.get_komponente(i));
		Gradient.set_komponente(i, tmp);
		//std::cout << "Gradient an der Stelle " << i+1 << ": " << Gradient.get_komponente(i) << std::endl;
	}
	return Gradient;
}

CMyVektor CMyVektor::gradientenVerfahren(CMyVektor x, double (*function)(CMyVektor x), double lambda) {
	CMyVektor x_neu;
	x_neu.vektor_anlegen(x.get_dimension());
	CMyVektor grad;
	grad.vektor_anlegen(x.get_dimension());
	auto func_neu = function(x);
	auto func = function(x);
	double len = x.vektor_len();
	for (int i = 0; i <= 25; i++) {
		func = function(x);
		grad = x.gradient(x, function);
		for (int z = 0; z < x.get_dimension(); z++) {
			x_neu.set_komponente(z, x.get_komponente(z) + grad.get_komponente(z) * lambda);
		}
		func_neu = function(x_neu);
		len = grad.vektor_len();
		if (len < pow(10, -5)) {
			std::cout << "Ende wegen || grad f(x) || < 1e-5 bei" << std::endl;
			break;
		}
		else if (i == 25) {
			std::cout << "Ende wegen Schrittzahl = 25 bei" << std::endl;
			break;
		}
		std::cout << "Schritt " << i << ":" << std::endl << std::endl <<
			"x = "; x.print();
		std::cout << "lambda = " << lambda << std::endl <<
			"f(x) = " << func << std::endl <<
			"grad f(x) = "; grad.print();
		std::cout << "||grad f(x)|| = " << len << std::endl << std::endl <<
			"x_neu = "; x_neu.print();
		std::cout << "f(x_neu) = " << func_neu << std::endl;
		std::cout << std::endl;
		if (func_neu > func) {
			CMyVektor xtest;
			xtest.vektor_anlegen(x.get_dimension());
			double lambdatestdouble = lambda;
			lambdatestdouble *= 2;
			auto func_neu_test = func_neu;
			for (int i = 0; i < x.get_dimension(); i++) {
				xtest.set_komponente(i, x.get_komponente(i) + grad.get_komponente(i) * lambdatestdouble);
			}
			func_neu_test = function(xtest);
			std::cout << "Test mit doppelter Schrittweite (lambda = " << lambdatestdouble << "):" << std::endl <<
				"x_test = "; xtest.print();
			std::cout << "f(x_test) = " << func_neu_test << std::endl << std::endl;
			if (func_neu_test > func_neu) {
				x = xtest;
				lambda = lambdatestdouble;
				std::cout << "verdoppelte Schrittweite!" << std::endl << std::endl;
			}
			else {
				x = x_neu;
				std::cout << "behalte alte Schrittweite!" << std::endl << std::endl;
			}
		}
		else if (func_neu <= func) {
			double lambdatesthalf = lambda;
			while (func > func_neu) {
				lambdatesthalf *= 0.5;
				std::cout << "halbiere Schrittweite (lambda = " << lambdatesthalf << "):" << std::endl;
				for (int j = 0; j < x.get_dimension(); j++) {
					x_neu.set_komponente(j, x.get_komponente(j) + grad.get_komponente(j) * lambdatesthalf);
				}
				func_neu = function(x_neu);
				std::cout << "x_neu: "; x_neu.print();
				std::cout << "f(x_neu): = " << func_neu << std::endl;
			}
			lambda = lambdatesthalf;
			x = x_neu;
			std::cout << "\n";
		}
	}
	func = function(x);
	grad = x.gradient(x, function);
	std::cout << "x = "; x.print();
	std::cout << "lambda = " << lambda << std::endl <<
		"f(x) = " << func << std::endl <<
		"grad f(x) = "; grad.print();
		std::cout << "||grad f(x)|| = " << len << std::endl << std::endl;
	return x;
}