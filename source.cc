#include <iostream>
#include "Matrix.h"


int main(){
    Matrix mat(3, 3);
    mat[0][0] = 5;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[1][0] = 0;
    mat[1][1] = 5;
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 5;
    mat.show();

    Matrix test = mat.inv();
    test.show();
    double a = mat.det();
    double b = test.det();
    std::cout << "Det(mat) = " << a << std::endl;
    std::cout << "Det(test) = " << b << std::endl;


    /*
    Matrix vec(3,1);
    vec[0][0] = 1;
    vec[1][0] = 2;
    vec[2][0] = 3;
    //z_vec.show();
    //Matrix s_vec = z_vec.transposition();
    //s_vec.show();
    Matrix mat3x3(3,3);
    Matrix mat3x3_1(3,3);
    //mat3x3.show();
    double new_line[3] = {1, 2, 3};
    mat3x3[0] = new_line;
    mat3x3[1] = new_line;
    mat3x3[2] = new_line;
    //mat3x3.show();
    //Matrix transponiert = mat3x3.transposition();
    //transponiert.show();
    Matrix product(3,3);
    mat3x3.show();
    product = ( 4 * mat3x3);
    product.show();
    */

}


