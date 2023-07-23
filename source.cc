#include <iostream>
#include "Matrix.h"


int main(){
    Matrix mat(3, 3);
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    double det_mat = mat.det();
    std::cout << "Determintate Mat: " << det_mat << std::endl;
    std::cout << " " << std::endl;
    Matrix test(3, 3);
    test = mat.inv();
    test.show();



}


