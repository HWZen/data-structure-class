#pragma once
#include <iostream>

class Matrix
{
private:
    double **array;
    int Xlen;// 行数
    int Ylen;// 列数
    int Rank_Num;// 秩

public:
    Matrix();
    Matrix(const Matrix &mat);
    Matrix(int Xnum, int Ynum);
    Matrix(int Xnum, int Ynum, double **ARRAY);
    Matrix &operator+=(const Matrix &); //矩阵的+=操作
    Matrix &operator-=(const Matrix &); //-=

    Matrix Row_Echelon(); // 梯形矩阵

    int GetRankNum(); // 获取秩

    Matrix LU(Matrix mat); // LU分解
    ~Matrix();
};
Matrix::Matrix()
{
    array = NULL;
    Xlen = Ylen = 0;
    Rank_Num = -1;
}

Matrix::Matrix(int xnum, int ynum)
{
    Xlen = xnum;
    Ylen = ynum;
    Rank_Num = -1;
    array = new double *[ynum];
    for (int i = 0; i < ynum; i++)
        array[ynum] = new double[xnum];
}

Matrix::Matrix(int xnum, int ynum, double **ARRAY)
{
    Xlen = xnum;
    Ylen = ynum;
    Rank_Num = -1;
    array = new double *[ynum];
    for (int i = 0; i < ynum; i++)
    {
        array[i] = new double[xnum];
        for (int j = 0; j < xnum; j++)
            array[i][j] = ARRAY[i][j];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < Ylen; i++)
        delete[] array[i];
    delete array;
}

Matrix::Matrix(const Matrix &mat)
{
    Matrix(mat.Xlen, mat.Ylen);

    for (int i = 0; i < Xlen; i++)
        for (int j = 0; j < Ylen; j++)
            array[i][j] = mat.array[i][j];
}