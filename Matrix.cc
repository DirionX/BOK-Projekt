#include "Matrix.h"
#include <iostream>

// Definitionen für die Matrix Klasse

// Construktor Definition, ist etwas fancy und verwirrend aber funktioniert hoffentlich.
Matrix::Matrix(int n, int m) : N(n), M(m){
    // n sind Spalten; m sind Reihen (glaub ich zumindest)
    matrix = new double*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new double[m];
        for (int j = 0; j < m; j ++) {
            double eintrag = 0;
            if (i == j) {
                eintrag = 0;
            }
            matrix[i][j] = eintrag;
        }
    }
}
Matrix::Matrix(int n): N(n), M(n) {
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
        exit(0);
    }
}

void Matrix::show(){
    //Mega ätzend zu printen...
    for (int i = 0; i<N; i++){
        std::cout << "[";
        for (int j = 0; j<M; j++){
            if (j == M - 1){
                std::cout << matrix[i][j];
            }else{
                std::cout << matrix[i][j] << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}
