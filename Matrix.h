#pragma once
#include <string>
class Matrix
{
    int rows, columns;
    std::string* matrix;

public:
    Matrix(int rows, int columns) : rows(rows), columns(columns) {
        // This approach uses a single array since "new" cannot create 
        // multidimensional arrays.
        // It also spares the performance cost of an array of arrays.
        matrix = new std::string[columns * rows];
    }

    ~Matrix() {
        // Release the memory after destroying the Matrix-object
        delete[] matrix;
    }

    /*Access the element at position [r]ow and [c]olumn.*/
    std::string getElement(int r, int c) {
        // matrix[c][r] is rewritten as matrix[column + columns * rows] 
        // -> matrix <=> Single memory block
        return matrix[c + columns * r];
    }

    /*Set the element at position [r]ow and [c]olumn with given [val]ue.*/
    void setElement(int r, int c, std::string val) {
        matrix[c + columns * r] = val; 
    }
};

