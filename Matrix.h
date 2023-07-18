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

void gauss_on_En(Matrix &mat);

Matrix inv();

double det();


void test();
bool zsf();
};


// Auserhalb der Matrix Klasse

Matrix operator*(double lambda, Matrix &mat);
Matrix operator*(Matrix &mat, double lambda);

void zeilen_add(Matrix &mat, int i, int j, double lambda);

void zeilen_skalar_mult(Matrix &mat, int a, double lambda);

