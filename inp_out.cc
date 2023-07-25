#include "Matrix.h"
#include <iostream>
#include <string>
#include <fstream> // für Textfiles
#include <sstream> // für string-kontrolle
#include <vector> // um die Input Matrizen zu speichern
#include <memory> // für smartpointer in readFile funktion

// Printed eine Matrix in ein File (mit n,m Dimesionen in erster Zeile)

void matrixToFile(std::string f, Matrix mat){
    std::ofstream outputf;
    outputf.open(f);
    if(outputf.is_open()){
        outputf << mat.M << " " << mat.N << std::endl;
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

/* Liest eine Matrix aus dem File an der Zeile line_i aus. Format muss so aussehen:
    m n
    a a a
    a a a
    a a a
    wobei n,m die dim der matrix, und a zahlen.
    (hat ohne unique Pointer nicht funktioniert...)
*/

std::unique_ptr<Matrix> readFile(std::string f, int line_i){
    std::ifstream inputf;
    inputf.open(f);
    double inputS;
    if(inputf.is_open()){
        if(!checkFormat(f, line_i)){
            return std::unique_ptr<Matrix>(new Matrix());
        }
        std::string ignore;
        // Das File wird erst ab der ersten "line_i-ten" gelesen, der rest ignoriert
        for (int i = 0; i < line_i - 1; i++){
            std::getline(inputf, ignore);
        }
        // Dimensionen werden eingelesen
        inputf >> inputS;
        const int M = inputS;
        inputf >> inputS;
        const int N = inputS;
        std::unique_ptr<Matrix> mat(new Matrix(M, N));
        int i = 0;
        int j = 0;
        // Matrix wird eingelesen
        while (inputf >> inputS){
            if (j == N){
                i++;
                j = 0;
            }
            if(i == M){
                break;
            }
            (*mat)[i][j] = inputS;
            j++;
        }
        inputf.close();
        return mat;
    }else{
        std::cout << "Can't open file..." << std::endl;
        abort();
    }
}

// nimmt ein string und checkt ob n-viele Doubles mit Leerzeichen dazwischen enthalten sind.

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

//Checkt ob das Martrix format im Text file ab der Zeile "line_i" stimmt, um von readFile eingelesen werden zu können

bool checkFormat(std::string file, int line_i){
    std::ifstream inputStr;
    inputStr.open(file);
    if (!inputStr.is_open()){
        abort();
    }
    std::string ignore;
    for (int i = 0; i < line_i - 1; i++){
        std::getline(inputStr, ignore);
    }
    int m;
    int n;
    std::string line;
    std::getline(inputStr, line);
    if(!twoPositiveIntCheck(line)){
        return false;
    }
    std::istringstream lineS(line);
    lineS >> m;
    lineS >> n;
    int i = 0;
    while(!inputStr.eof() && i < m){
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
    inputStr.close();
}

// überprüft Format von erster Zeile der Matrix, also von der dim. Eingabe.

bool twoPositiveIntCheck(std::string str){
    std::istringstream iss(str);
    int num;
    int i = 0;
    while(iss >> num){
        i++;
        if (num <= 0){
            return false;
        }
        if(i == 2){
            char rest;
            if (iss >> rest){
                return false;
            }else{
                return true;
            }
        }
    }
}

// Funktion wo alles passiert

void calculate(std::string output, std::string input){
    // hat ohne unique pointer nicht funktioniert
    std::vector<std::unique_ptr<Matrix>> matrizen;
    std::vector<std::string> operations;
    int line_i = 1;
    std::ifstream inputf;
    inputf.open(input);
    std::string line;
    if (!inputf.is_open()){
        std::cout << "File didn't open" << std::endl;
        abort();
    }
    // Text File wird einglesen und Matrizen/Operationen in Vector gespeichert
    while (!inputf.eof()){
        std::getline(inputf, line);
        if(checkFormat(input, line_i)){
            matrizen.push_back(std::unique_ptr<Matrix>(readFile(input, line_i)));
        }else if(line == "+"){
            operations.push_back(line);
        }else if(line == "*"){
            operations.push_back(line);
        }else if(line == "gauss"){
            operations.push_back(line);
        }else if(line == "transp"){
            operations.push_back(line);
        }else if(line == "inv"){
            operations.push_back(line);
        }else if(line == "det"){
            operations.push_back(line);
        }
        line_i++;
    }
    // Operationen werden auf die gespeicherten Matritzen ausgeführt
    for (int i = 0; i < operations.size(); i++){
        if (operations[i] == "+"){
            int m = matrizen[i]->M;
            int n = matrizen[i]->N;
            Matrix mat(m, n);
            if (i == 0){
                mat = (*matrizen[i]) + (*matrizen[i+1]);
                matrixToFile(output, mat);
                // .show falls letzte Operation
                if (operations.size() == 1){
                    mat.show();
                }
            }else{
                mat = (*readFile(output, 1)) + (*matrizen[i+1]);
                matrixToFile(output, mat);
                if (operations.size() == (i + 1)){
                    mat.show();
                }
            }
        } if (operations[i] == "*"){
            if (i == 0){
                int n = matrizen[i + 1]->N;
                int m = matrizen[i]->M;
                Matrix mat(m, n);
                mat = (*matrizen[i]) * (*matrizen[i+1]);
                matrixToFile(output, mat);
                if (operations.size() == (i + 1)){
                    mat.show();
                }
            }else{
                int n = matrizen[i + 1]->N;
                int m = readFile(output, 1)->M;
                Matrix mat(m, n);
                mat = (*readFile(output, 1)) * (*matrizen[i+1]);
                matrixToFile(output, mat);
                if (operations.size() == (i + 1)){
                    mat.show();
                }
            }
        } if (operations[i] == "gauss"){
            int m = matrizen[i]->M;
            int n = matrizen[i]->N;
            Matrix mat(m, n);
            mat = matrizen[i]->gauss();
            mat.show();
            matrixToFile(output, mat);
        } if(operations[i] == "transp"){
            int m = matrizen[i]->M;
            int n = matrizen[i]->N;
            Matrix mat(m, n);
            mat = matrizen[i]->transposition();
            mat.show();
            matrixToFile(output, mat);
        } if(operations[i] == "inv"){
            int m = matrizen[i]->M;
            int n = matrizen[i]->N;
            Matrix mat(m, n);
            mat = matrizen[i]->inv();
            mat.show();
            matrixToFile(output, mat);
        } if(operations[i] == "det"){
            double dete;
            dete = matrizen[i]->det();
            std::cout << dete << std::endl;
            std::ofstream outputf;
            outputf.open(output);
            outputf << dete;
            outputf.close();
        }
    }
    inputf.close();
}

