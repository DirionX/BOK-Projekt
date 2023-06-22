#include "Matrix.h"
#include <iostream>

// Definitionen für die Matrix Klasse

// Construktor Definition, ist etwas fancy und verwirrend aber funktioniert hoffentlich. 
Matrix::Matrix(int n, int m) : COLS(n), ROWS(m){
    // n sind Spalten; m sind Reihen (glaub ich zumindest)
    matrix = new float*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new float[m];
    }
}
void Matrix::set(float** mat){
    // Achtung die Größe ist für jedes Objekt fest
    matrix = mat;
}
float** Matrix::getMatrix(){
    return matrix;
}
void Matrix::show(){
    //Mega ätzend zu printen...
    for (int i = 0; i<COLS; i++){
        std::cout << "[";
        for (int j = 0; j<ROWS; j++){
            if (j == ROWS - 1){
                std::cout << matrix[i][j];
            }else{
                std::cout << matrix[i][j] << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}