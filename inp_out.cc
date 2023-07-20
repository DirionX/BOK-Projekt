#include "Matrix.h"
#include <iostream>
#include <string>
#include <fstream> // für Textfiles
#include <sstream> // für string-kontrolle

// Printed eine Matrix in ein File

void matrixToFile(std::string f, Matrix mat){
    std::ofstream outputf;
    outputf.open(f);
    if(outputf.is_open()){
        for (int i = 0; i<mat.M; i++){
            for (int j = 0; j<mat.N; j++){
                if (j == mat.N - 1){
                    outputf << mat[i][j] << " ";
                }else{
                    outputf << mat[i][j] << " ";
                }
            }
            outputf << std::endl;
        }
    }else{
        std::cout << "Can't open file..." << std::endl;
    }
    outputf.close();
}

/* Liest eine Matrix aus dem File aus. Format muss so aussehen:
    m n
    a a a
    a a a
    a a a
    wobei n,m die dim der matrix, und a zahlen.
*/
Matrix readFile(std::string f){
    std::ifstream inputf;
    inputf.open(f);
    double inputS; 
    if(inputf.is_open()){
        if(!checkFormat(f)){
            return Matrix();
        }
        inputf >> inputS;
        const int M = inputS;
        inputf >> inputS;
        const int N = inputS;
        Matrix* mat = new Matrix(M, N);
        int i = 0;
        int j = 0;
        while (inputf){
            if (j == (M)){
                i++;
                j = 0;
            }
            if(i == M){
                break;
            }
            inputf >> inputS;
            (*mat)[i][j] = inputS;
            j++;
        }
        inputf.close();
        return *mat;
    }else{
        std::cout << "Can't open file..." << std::endl;
        abort();
    }
}

// nimmt ein string und checkt ob n-viele doubles mit leerzeichen dazwischen enthalten sind.

bool nDoublesInString(std::string str, int n){
    std::istringstream iss(str);
    double num;
    int i = 0;
    while(iss >> num){
        i++;
        if(i == n){
            char rest;
            if (iss >> rest){
                return false;
            }else{
                return true;
        }
    }
    }
}

//Checkt ob das Martrix format im Text file stimmt, um von readFile eingelesen werden zu können

bool checkFormat(std::string file){
    std::ifstream inputNum;
    std::ifstream inputStr;
    inputNum.open(file);
    inputStr.open(file);
    if (!inputNum.is_open() || !inputStr.is_open()){
        abort();
    }
    int m;
    int n;
    std::string line;
    inputNum >> m;
    inputNum >> n;
    std::getline(inputStr, line);
    if ((m <= 0) || (n <= 0) || (line.length() != (1 + std::to_string(n).length() + std::to_string(m).length()))){
        return false;
    }
    int i = 0;
    while(!inputStr.eof() || line == ""){
        i++;
        std::getline(inputStr, line);
        if (!(nDoublesInString(line, n))){
            return false;
        }
    }
    if(i != m){
        return false;
    }
    return true;
    inputNum.close();
    inputStr.close();
}
