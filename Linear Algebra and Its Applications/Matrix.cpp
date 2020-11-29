#include "Matrix.h"
#include <string>
using namespace std;

int Matrix::GetRankNum()
{
    if(Rank_Num!=-1)
        return Rank_Num;
    Matrix temp(*this);

}

Matrix Matrix::LU(Matrix mat)
{
    double **anser;
    double *temp;
    temp = new double[mat.Ylen];
    anser = new double *[mat.Ylen];
    for (int i = 0; i < mat.Ylen; i++)
        anser[i] = new double[mat.Xlen];
}

Matrix& Matrix::operator+=(const Matrix &mat)
{
    Matrix anser(Xlen > mat.Xlen ? Xlen : mat.Xlen, Ylen > mat.Ylen ? Ylen : mat.Ylen);

    for (int i = 0; i < Xlen; i++)
        for (int j = 0; j < Ylen; j++)
            anser.array[i][j] = array[i][j];

    for (int i = 0; i < mat.Xlen; i++)
        for (int j = 0; j < mat.Ylen; j++)
            anser.array[i][j] += mat.array[i][j];

    return anser;
}

Matrix &Matrix::operator-=(const Matrix &mat)
{
    Matrix anser(Xlen > mat.Xlen ? Xlen : mat.Xlen, Ylen > mat.Ylen ? Ylen : mat.Ylen);

    for (int i = 0; i < Xlen; i++)
        for (int j = 0; j < Ylen; j++)
            anser.array[i][j] = array[i][j];

    for (int i = 0; i < mat.Xlen; i++)
        for (int j = 0; j < mat.Ylen; j++)
            anser.array[i][j] -= mat.array[i][j];

    return anser;
}

Matrix Matrix::Row_Echelon()
{
    
}