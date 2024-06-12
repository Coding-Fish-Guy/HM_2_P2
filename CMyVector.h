#pragma once
#include <vector>
#include <string>

class CMyVektor {
private:
    std::vector<double> vektor;
public:
    void add_dimension(double wert) { vektor.push_back(wert); }
    void erase_dimension() { vektor.pop_back(); }
    void erase() { vektor.clear(); }
    void vektor_anlegen(int dimension) { vektor.resize(dimension); }
    void set_dimension(int dimension, int value);
    int get_dimension() { return vektor.size(); }
    void set_komponente(int stelle, double komponente) { vektor[stelle] = komponente; }
    double get_komponente(double wert) { return vektor[wert]; }
    double vektor_len();
    void insert(int stelle, double wert);
    void print();
    CMyVektor() { vektor.assign(2, 0.0); }
    CMyVektor(int dimension) { vektor.assign(dimension, 0.0); }
    CMyVektor(int dimension, double wert) { vektor.assign(dimension, wert); }
    ~CMyVektor() { vektor.clear(); }
    double& operator[](double x) { return vektor[x]; }
    CMyVektor& operator=(const CMyVektor& orig) { vektor = orig.vektor; return *this; }
    CMyVektor& operator()(const std::vector<double>& vec) { vektor = vec; return *this; }
    CMyVektor operator+=(CMyVektor a);
    CMyVektor operator*=(double lambda);
    CMyVektor gradient(CMyVektor x, double (*function)(CMyVektor x));
    CMyVektor gradientenVerfahren(CMyVektor x, double (*function)(CMyVektor x), double lambda);
};

CMyVektor operator+(CMyVektor a, CMyVektor b);
CMyVektor operator*(double lambda, CMyVektor a);
