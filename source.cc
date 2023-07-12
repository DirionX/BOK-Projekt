#include <iostream>
#include "Matrix(2).h"

int main(){
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

}
