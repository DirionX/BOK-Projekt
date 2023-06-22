#pragma once 

// Hier kommen nur Deklarationen hin.

class Matrix {
private:
// Spalten
const int COLS;
// Reihen
const int ROWS;
// 2-Dimensionales Array (I guess das funktioniert so)
float** matrix;   

public:
// Constructor
Matrix(int n, int m);
// Ausgabe der Matrix in Array-Form
float** getMatrix();
// Gibt die Matrix Lesbar in die Konsole aus
void show();
// Matrix sezten (erst mal direkt in der Zukunft vielleicht lieber über ein Textdokument einlesen)
void set(float** mat);
};