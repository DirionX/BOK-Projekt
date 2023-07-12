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
    matrix = new double*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new double[n];
        for (int j = 0; j < n; j ++) {
            double eintrag = 0;
            if (i == j) {
                eintrag = 1;
            }
            matrix[i][j] = eintrag;
        }
    }
}


Matrix::~Matrix() {
    for (int i = 0; i < N; i ++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


double*& Matrix::operator[](int i) {
    /*Liefert eine Referenz auf den Pointer, sd mit mat[i] überschrieben werden kann */
    if (i < M && 0 <= i) {
        return matrix[i];
    }
    else {
        std::cout << "Error Index out of bounds";
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
void Matrix::test(){
    std::cout << this->M << std::endl;

}
Matrix& Matrix::operator=(const Matrix &mat){
    if (!equal_size(mat)){
        std::cout << "Operation = not possible, sizes dont match" << std::endl;
        abort();
    }
    this->matrix = mat.matrix;
    return *this;
}
Matrix Matrix::operator+(Matrix &mat) {
    if (!equal_size(mat)) {
        std::cout << "Operation + not possible, sizes dont match" << std::endl;
        abort();
    }
    else {
        Matrix sum(this->M, this->N);
        for (int i = 0; i < this->M; i++) {
            for (int j = 0; j < this->N; j++) {
                sum[i][j] = (*this)[i][j] + mat[i][j];
            }
        }
        return sum;
    }
}

bool Matrix::equal_size(const Matrix &mat){
    if (this->M != mat.M || this->N != mat.N){
        return false;
    }else{
        return true;
    }
}

