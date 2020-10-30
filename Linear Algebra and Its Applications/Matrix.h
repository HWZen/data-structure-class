#pragma once
#include <iostream>

class Matrix
{
private:
    double **array;
    int Xlen;
    int Ylen;
    friend Matrix LU(Matrix mat);

public:
    Matrix();
    Matrix(const Matrix &mat);
    Matrix(int Xnum, int Ynum);
    Matrix(int Xnum, int Ynum, double **ARRAY);
    ~Matrix();
};
Matrix::Matrix()
{
    array = NULL;
    Xlen = Ylen = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < Ylen; i++)
        delete[] array[i];
    delete array;
}
