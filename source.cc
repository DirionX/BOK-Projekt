#include <iostream>
#include "Matrizen.h"

int main(){
    Matrizen m1x1(0);
    std::cout << "Matrix: " << m1x1.getValue() << std::endl;
    std::cout << "Set Matrix to 4" << std::endl;
    m1x1.setValue(4);
    std::cout << "Matrix: " << m1x1.getValue() << std::endl;
}