#include "Matrizen.h"

Matrizen::Matrizen(int value){
    m_value = value;
}
void Matrizen::setValue(int value){
    m_value = value;
}
int Matrizen::getValue(){
    return m_value;
}