#pragma once
#include <string>
#include <memory> //für unique pointer

// Hier kommen nur Deklarationen hin.

class Matrix {
private:
// 2-Dimensionales Array (I guess das funktioniert so)
double** matrix;

public:
// Spalten
const int M;
// Reihen
const int N;
// Constructor
Matrix(int m, int n);
// Quadratischer Matrix Konstruktor
Matrix(int n);
// NUll-Matrix
Matrix();
//Dekonstruktor
~Matrix();

// Überladen von Operatoren
double*& operator[](int i);

Matrix& operator=(const Matrix &mat);

Matrix operator+(Matrix &mat);

Matrix operator*(Matrix &mat);

//Methoden
bool equal_size(const Matrix &mat);

void show();

Matrix transposition();

Matrix gauss();

Matrix gauss(Matrix & mat);

Matrix inv();

double det();

Matrix punkt_spiegel();

bool zsf();
};


// Auserhalb der Matrix Klasse

Matrix operator*(double lambda, Matrix &mat);

Matrix operator*(Matrix &mat, double lambda);

void zeilen_add(Matrix &mat, int i, int j, double lambda);

void zeilen_skalar_mult(Matrix &mat, int a, double lambda);

// INPUT/OUTPUT SHIT

void matrixToFile(std::string f, Matrix mat);

std::unique_ptr<Matrix> readFile(std::string f, int line_i);

bool nDoublesInString(std::string str, int n);

bool checkFormat(std::string file, int line_i);

bool twoPositiveIntCheck(std::string str);

void calculate(std::string output, std::string input);

double runden(double d, int digits);
