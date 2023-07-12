#pragma once

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
//Dekonstruktor
~Matrix();

// Überladen von [] um auf Inhalt zugreifen zu können und zu überarbeiten
double*& operator[](int i);


Matrix Gauss(Matrix &mat);

Matrix operator*(Matrix &mat);


Matrix transposition();
Matrix operator+(Matrix &mat);
Matrix& operator=(const Matrix &mat);


void show();
// Matrix sezten (erst mal direkt in der Zukunft vielleicht lieber über ein Textdokument einlesen)
void test();
bool equal_size(const Matrix &mat);
};


Matrix operator*(double lambda, Matrix &mat);
Matrix operator*(Matrix &mat, double lambda);

