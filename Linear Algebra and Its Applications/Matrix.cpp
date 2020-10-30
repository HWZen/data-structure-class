#include "Matrix.h"

Matrix::Matrix(int xnum, int ynum)
{
    Xlen = xnum;
    Ylen = ynum;
    array = new double *[ynum];
    for (int i = 0; i < ynum; i++)
        array[ynum] = new double[xnum];
}

Matrix::Matrix(int xnum, int ynum, double **ARRAY)
{
    Xlen = xnum;
    Ylen = ynum;
    array = new double *[ynum];
    for (int i = 0; i < ynum; i++)
    {
        array[i] = new double[xnum];
        for (int j = 0; j < xnum; j++)
            array[i][j] = ARRAY[i][j];
    }
}

Matrix LU(Matrix mat)
{
    double **anser;
    double *temp;
    temp = new double[mat.Ylen];
    anser = new double *[mat.Ylen];
    for (int i = 0; i < mat.Ylen; i++)
        anser[i] = new double[mat.Xlen];
}