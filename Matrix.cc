#include "Matrix.h"
#include <iostream>
#include <math.h>


// Definitionen für die Matrix Klasse

// Construktor Definition, ist etwas fancy und verwirrend aber funktioniert hoffentlich.
Matrix::Matrix(int m, int n) : M(m), N(n){
    // n sind Spalten; m sind Reihen (glaub ich zumindest)
    matrix = new double*[M];
    for (int i = 0; i < M; i++){
        matrix[i] = new double[N];
        for (int j = 0; j < N; j ++) {
            double eintrag = 0;
            matrix[i][j] = eintrag;
        }
    }
}

// Konstruktor für quadratische Matrizen

Matrix::Matrix(int n):  M(n), N(n){
    matrix = new double*[M];
    for (int i = 0; i < n; i++){
        matrix[i] = new double[N];
        for (int j = 0; j < n; j ++) {
            double eintrag = 0;
            if (i == j) {
                eintrag = 1;
            }
            matrix[i][j] = eintrag;
        }
    }
}

// Nullmatrix

Matrix::Matrix(): M(0), N(0) {
    matrix = nullptr;
}

//Dekonstruktor

Matrix::~Matrix() {
    for (int i = 0; i < M; i ++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

//Überladen von Operatoren

//Operator [] um auf Zeile der Matrix zuzugreifen

double*& Matrix::operator[](int i) {
    /*Liefert eine Referenz auf den Pointer, sd mit mat[i] überschrieben werden kann */
    if (i < M && 0 <= i) {
        return matrix[i];
    }
    else {
        std::cout << "Error Index out of bounds";
    }
}

// Operator =, um Matrizen kopieren zu können

Matrix & Matrix::operator=(const Matrix &mat){
    if (!equal_size(mat)){
        std::cout << "Operation = not possible, sizes dont match" << std::endl;
        abort();
    }
    for (int i = 0; i < this->N; i++){
        for(int j = 0; j < this->M; j++){
            this->matrix[j][i] = mat.matrix[j][i];
        }
    }
    return *this;
}

// Matrizenaddition, implementiert durch den + Operator

Matrix Matrix::operator+( Matrix& mat){
    // Überprüfen ob die Größen passen
    if (!equal_size(mat)) {
        std::cout << "Operation + not possible, sizes dont match" << std::endl;
        return mat;
    }
    else {
        // Wir brauchen kein delete? (scheint auch so zu funktionieren)
        Matrix* sum = new Matrix(this->M, this->N);
        for (int i = 0; i < this->M; i++) {
            for (int j = 0; j < this->N; j++) {
                (*sum)[i][j] = (*this)[i][j] + mat.matrix[i][j];
            }
        }
        return *sum;
    }
}

Matrix Matrix::operator*(Matrix &mat){
    // Überprüfen ob die Größen passen
    if (this->N != mat.M) {
        std::cout << "Operation * not possible, sizes dont match" << std::endl;
        return Matrix();
    }
    Matrix* produkt = new Matrix(this->M, mat.N);
    // Zeile mal Spalte
    for (int i = 0; i < this->M; i++){
        for (int j = 0; j < mat.N; j++){
            double eintrag = 0;
            for (int k = 0; k < this->N; k++) {
                eintrag += this->matrix[i][k] * mat[k][j];
            }
            (*produkt)[i][j] = eintrag;
        }
    }
    return *produkt;
}

//Methoden

//  Überprüfen ob Größen übereinstimmen

bool Matrix::equal_size(const Matrix &mat){
    if (this->M != mat.M || this->N != mat.N){
        return false;
    }else{
        return true;
    }
}

// Ausgabe ins Terminal

void Matrix::show(){
    //Mega ätzend zu printen...
    for (int i = 0; i<M; i++){
        std::cout << "[";
        for (int j = 0; j<N; j++){
            if (j == N - 1){
                std::cout << matrix[i][j];
            }else{
                std::cout << matrix[i][j] << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}

// Matrix transposition

Matrix Matrix::transposition() {
    Matrix transp(this->N, this->M);
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            transp[i][j] = (*this)[j][i];
        }
    }
    return transp;
}

// Gauss-Algorithmus für eine Matrix beliebiger Größe

Matrix Matrix::gauss() {
    Matrix gauss(this->M, this->N);
    gauss = *this;

    int active_not_zero = -1;
    int zeile = 0;

    for (int i = 0; i < this->N; i++) {
        active_not_zero = -1;
        for (int j = zeile; j < this->M; j++) {
            if (gauss[j][i] != 0) {
                active_not_zero = j;
                break;
            }
        }
        if (active_not_zero == -1) {
            continue;
        }
        if (active_not_zero != i) {
            zeilen_add(gauss, active_not_zero, zeile, 1);
        }
        for (int j = zeile + 1; j < this->M; j++) {
            if (gauss[j][i] != 0){
                double factor = -(gauss[j][i] / gauss[zeile][i]);
                zeilen_add(gauss, zeile, j, factor);
            }

        }
        zeile++;
    }
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            gauss[i][j] = runden(gauss[i][j], 5);
        }
    }

    return gauss;
}

Matrix Matrix::gauss(Matrix & mat) {
    Matrix gauss(this->M, this->N);
    gauss = *this;

    int active_not_zero = -1;
    int zeile = 0;

    for (int i = 0; i < this->N; i++) {
        active_not_zero = -1;
        for (int j = zeile; j < this->M; j++) {
            if (gauss[j][i] != 0) {
                active_not_zero = j;
                break;
            }
        }
        if (active_not_zero == -1) {
            continue;
        }
        if (active_not_zero != i) {
            zeilen_add(gauss, active_not_zero, zeile, 1);
            zeilen_add(mat, active_not_zero, zeile, 1);
        }
        for (int j = zeile + 1; j < this->M; j++) {
            if (gauss[j][i] != 0){
                double factor = -(gauss[j][i] / gauss[zeile][i]);
                zeilen_add(gauss, zeile, j, factor);
                zeilen_add(mat, zeile, j, factor);
            }

        }
        zeile++;
    }
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            gauss[i][j] = runden(gauss[i][j], 5);
        }
    }

    return gauss;
}

// Bestimmung der Inversen Matrix für quadratische Matrizen mit Determintante ungleich 0

Matrix Matrix::inv() {
    if (this->M != this->N) {
        return Matrix();
    }
    if (this->det() == 0) {
        std::cout << "Die Matrix ist nicht invertierbar" << std::endl;
        return Matrix();
    }
    else {
        Matrix inv(this->M, this->N);
        for (int i = 0; i < this->M; i++) {
            inv[i][i] = 1;
        }
        Matrix mat(this->N, this->M);
        mat = this->gauss(inv);
        inv = inv.punkt_spiegel();
        mat = mat.punkt_spiegel();
        mat.gauss(inv);
        for (int i = 0; i < this->M; i++) {
            double factor = 1 / mat[i][i];
            for (int j = 0; j < this->N; j++) {
                inv[i][j] *= factor;
                inv[i][j] = runden(inv[i][j], 5);
            }
        }
        return inv.punkt_spiegel();
    }
}

//Bestimmung der Determinanten über den Gauss-Algorithmus

double Matrix::det() {
    if (this->M != this->N) {
        return 0;
    }
    Matrix gauss(this->M, this->N);
    gauss = this->gauss();
    double det = 1;
    for (int i = 0; i < this->M; i++) {
        det *= gauss[i][i];
    }
    return det;
}

//Hilfsfunktion, um beim invertieren von einer oberen Dreiecksgestallt
// in Diagonalgestallt zu kommmen

Matrix Matrix::punkt_spiegel() {
    if (M != N){
        return Matrix();
    }
    Matrix spiegel(M, N);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            spiegel[M - 1- i][N - 1 - j] = matrix[i][j];
        }
    }
    return spiegel;
}

// Funktion, die überprüft ob Matrix in Zeilenstufenform ist

bool Matrix::zsf(){
    int not_zero_i = -1;
    int new_zero_i = -1;
    for (int i = 0; i < this->M; i++) {
        for (int j = 0; j < this->N; j++){
            if (matrix[i][j] != 0){
                if(j <= not_zero_i){
                    return false;
                }else{
                    not_zero_i = j;
                    break;
                }
            }else{
                new_zero_i = j;
            }
            if (new_zero_i > not_zero_i){
                not_zero_i = new_zero_i;
            }
        }
    }
    return true;
}


// Auserhalb der Matrix Klasse

// Skalarmultiplikationn

Matrix operator*(double lambda, Matrix &mat) {
    Matrix* produkt = new Matrix(mat.N, mat.M);
    for (int i = 0; i < mat.M; i++) {
        for (int j = 0; j < mat.N; j++) {
            (*produkt)[i][j] = mat[i][j] * lambda;
        }
    }
    return *produkt;
}

Matrix operator*(Matrix &mat, double lambda) {
    return lambda * mat;
}

//  Elementare Zeilenumformungen

void zeilen_add(Matrix &mat, int a, int b, double lambda) {
    if (a < 0 || b < 0) {
        return;
    }
    if ( a >= mat.M || b >= mat.M) {
        return;
    }
    for (int i = 0; i < mat.N; i++) {
        mat[b][i] = mat[b][i] + lambda * mat[a][i];
    }
}

void zeilen_skalar_mult(Matrix &mat, int a, double lambda) {
    if (a < 0 || a >= mat.M) {
        return;
    }
    for (int i = 0; i < mat.N; i++) {
        mat[a][i] = lambda * mat[a][i];
    }
}

// Hilfsfunktion zur Darstellung der Ergebnisse

double runden(double d, int digits) {
    double r1 = d * std::pow(10, digits);
    int r2 = int(r1);
    r1 = (1.0 * r2 / std::pow(10, digits));
    return r1;
}

