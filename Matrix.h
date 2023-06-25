#pragma once

// Hier kommen nur Deklarationen hin.

class Matrix {
private:
// 2-Dimensionales Array (I guess das funktioniert so)
double** matrix;

public:
// Spalten
const int COLS;
// Reihen
const int ROWS;
// Constructor
Matrix(int n, int m);
// Quadratischer Matrix Konstruktor
Matrix(int n);

void set_M(double** mat);

//Dekonstruktor
~Matrix();

// Überladen von [] um auf Inhalt zugreifen zu können und zu überarbeiten
double*& operator[](int i);

// plus overload
Matrix operator+(const Matrix& a);

void show();
// Matrix sezten (erst mal direkt in der Zukunft vielleicht lieber über ein Textdokument einlesen)
void set(float** mat);
};
