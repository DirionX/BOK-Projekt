#include <iostream>
#include "Matrix.h"

int main(){
    float mat[3][3] = {{1,2,3},{1,2,3},{1,2,3}};
    float** p = new float*[3];
    // verstehe ich jetzt auch nicht mehr um ehrlich zu sein... Funktioniert aber.
    for (int i = 0; i < 3; i++) {
        p[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            p[i][j] = mat[i][j];
    }
    }   
    Matrix mat3x3(3,3);
    mat3x3.set(p);
    mat3x3.show();
}
