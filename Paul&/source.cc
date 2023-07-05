#include <iostream>
#include "Matrix.h"

int main(){
    // verstehe ich jetzt auch nicht mehr um ehrlich zu sein... Funktioniert aber.
    Matrix z_vec(3, 1);
    z_vec.show();
    Matrix s_vec = z_vec.transposition();
    s_vec.show();
    Matrix mat3x3(3,3);
    mat3x3.show();
    double new_line[3] = {1, 2, 3};
    mat3x3[0] = new_line;
    mat3x3[1] = new_line;
    mat3x3[2] = new_line;
    mat3x3.show();
    Matrix transponiert = mat3x3.transposition();
    transponiert.show();

}
