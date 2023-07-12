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




Matrix transposition();
Matrix operator+(Matrix &mat);
Matrix& operator=(const Matrix &mat);
Matrix operator*(Matrix &mat);


void show();
// Matrix sezten (erst mal direkt in der Zukunft vielleicht lieber über ein Textdokument einlesen)
void set(float** mat);
void test();
bool equal_size(const Matrix &mat);
};


