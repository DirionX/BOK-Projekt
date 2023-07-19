#include "Matrix.h"
#include <iostream>

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

Matrix::Matrix(): M(0), N(0) {
    matrix = nullptr;
}


Matrix::~Matrix() {
    for (int i = 0; i < N; i ++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Ueberladen von Konstruktoren

double*& Matrix::operator[](int i) {
    /*Liefert eine Referenz auf den Pointer, sd mit mat[i] überschrieben werden kann */
    if (i < M && 0 <= i) {
        return matrix[i];
    }
    else {
        std::cout << "Error Index out of bounds";
    }
}

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

Matrix Matrix::operator+( Matrix& mat){
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
    if (this->N != mat.M) {
        std::cout << "Operation * not possible, sizes dont match" << std::endl;
        return Matrix();
    }
    Matrix* produkt = new Matrix(this->M, this->N);
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

bool Matrix::equal_size(const Matrix &mat){
    if (this->M != mat.M || this->N != mat.N){
        return false;
    }else{
        return true;
    }
}

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

Matrix Matrix::transposition() {
    Matrix transp(this->N, this->M);
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            transp[i][j] = (*this)[j][i];
        }
    }
    return transp;
}

Matrix Matrix::gauss() {
    Matrix gauss(this->M, this->N);
    gauss = *this;
    for (int i = 0; i < this->N - 1; i++) {
        int not_zero = -1;
        for (int j = i; j < this->M; j++) {
            if (gauss[j][i] != 0) {
                not_zero = j;
                break;
            }
        }
        if (not_zero == -1){
            continue;
        }
        if (not_zero != i) {
            zeilen_add(gauss, not_zero, i, 1);
        }
        for (int j = i + 1; j < this->M; j++) {
            if (gauss[j][i] != 0){
                double factor = -(gauss[j][i] / gauss[i][i]);
                zeilen_add(gauss, i, j, factor);
            }

        }
    }
    return gauss;
}

void Matrix::gauss_on_En(Matrix &mat) {
    Matrix gauss(this->M, this->N);
    gauss = *this;
    for (int i = 0; i < this->N - 1; i++) {
        int not_zero = -1;
        for (int j = i; j < this->M; j++) {
            if (gauss[j][i] != 0) {
                not_zero = j;
                break;
            }
        }
        if (not_zero == -1){
            continue;
        }
        if (not_zero != i) {
            zeilen_add(gauss, not_zero, i, 1);
            zeilen_add(mat, not_zero, i, 1);
        }
        for (int j = i + 1; j < this->M; j++) {
            if (gauss[j][i] != 0){
                double factor = -(gauss[j][i] / gauss[i][i]);
                zeilen_add(gauss, i, j, factor);
                zeilen_add(mat, i, j, factor);
            }

        }
    }
}

Matrix Matrix::inv() {
    if (this->M != this->N) {
        return Matrix();
    }
    if (this->det() <= 0) {
        std::cout << "Die Matrix ist nicht invertierbar" << std::endl;
        return Matrix();
    }
    else {
        Matrix inv(this->M, this->N);
        for (int i = 0; i < this->M; i++) {
            inv[i][i] = 1;
        }
        this->gauss_on_En(inv);
        inv = inv.transposition();
        Matrix transp(this->N, this->M);
        transp = this->transposition();
        transp.gauss_on_En(inv);
        for (int i = 0; i < this->M; i++) {
            double factor = 1 / transp[i][i];
            for (int j = 0; j < this->N; j++) {
                inv[i][j] *= factor;
            }
        }
        return inv;
    }
}

double Matrix::det() {
    if (this->M != this->N) {
        return -1;
    }
    Matrix gauss(this->M, this->N);
    gauss = this->gauss();
    double det = 1;
    for (int i = 0; i < this->M; i++) {
        det *= gauss[i][i];
    }
    return det;
}


void Matrix::test(){
    std::cout << this->M << std::endl;

}


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

Matrix operator*(double lambda, Matrix &mat) {
    Matrix product(mat.M, mat.N);
    for (int i = 0; i < mat.M; i++) {
        for (int j = 0; j < mat.N; j++) {
            product[i][j] = mat[i][j] * lambda;
        }
    }
    return product;
}

Matrix operator*(Matrix &mat, double lambda) {
    Matrix product(mat.M, mat.N);
    for (int i = 0; i < mat.M; i++) {
        for (int j = 0; j < mat.N; j++) {
            product[i][j] = mat[i][j] * lambda;
        }
    }
    return product;
}

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

