#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>

using std::runtime_error;


template <typename E>
class Matrix{
private:
    int rows;
    int columns;
    E **matrix;

public:
    Matrix(int rows, int columns){
        if(rows <= 0 || columns <= 0){
            throw runtime_error("Number of rows and columns must be greater than zero.");
        }
        this->rows = rows;
        this->columns = columns;
        matrix = new E *[rows];

        for(int i = 0; i < rows; i++){
            matrix[i] = new E [columns];
        }
    }

    ~Matrix(){

    }

    E getValue(int row, int column){
        if(row < 0 || row >= rows){
            throw runtime_error("Invalid row");
        }
        if(column < 0 || column >= columns){
            throw runtime_error("Invalid column");
        }

        return matrix[row][column];
    }

    void setValue(int row, int column, E value){
        if(row < 0 || row >= rows){
            throw runtime_error("Invalid row");
        }
        if(column < 0 || column >= columns){
            throw runtime_error("Invalid column");
        }
        matrix[row][column] = value;
    }

    int getRows(){
        return rows;
    }

    int getColumns(){
        return columns;
    }


};

#endif // MATRIX_H

