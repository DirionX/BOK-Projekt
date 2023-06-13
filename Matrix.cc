#include "Matrix.h"

Matrix::Matrix(int value){
    m_value = value;
}
void Matrix::setValue(int value){
    m_value = value;
}
int Matrix::getValue(){
    return m_value;
}