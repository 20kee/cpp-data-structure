#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <iostream>
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5 
#define CROWS 3
#define CCOLS 5

using namespace std;
class Matrix {
    int rows, cols;
    int* data;
public:
    Matrix(int r, int c)
    {
        rows = r;
        cols = c;
        data = new int[r*c];
    }

    ~Matrix() { free(data); }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    int at_i(int r, int c) const { return data[r*cols+c]; }
    int* get_ptr() const { return data; }

    int get_data();
    int show_data() const;
    int sort_data();
    Matrix& addmatrix(Matrix&);
    int MultiplyMatrix(Matrix&, Matrix&);
   
};

int main()
{
    Matrix matrixA(AROWS, ACOLS);
    Matrix matrixA1(AROWS, ACOLS);
    Matrix matrixB(BROWS, BCOLS);
    Matrix matrixC(CROWS, CCOLS);

    srand(time(NULL));

    matrixA.get_data();
    matrixA.show_data();

    matrixA1.get_data();
    matrixA1.show_data();

    Matrix matrixD = matrixA.addmatrix(matrixA1);

    matrixD.show_data();

    matrixB.get_data();
    matrixB.show_data();

    matrixC.MultiplyMatrix(matrixA, matrixB);
    matrixC.show_data();

    matrixA.sort_data();
    matrixA.show_data();

    matrixB.sort_data();
    matrixB.show_data();

    matrixA.addmatrix(matrixB);
    matrixA.show_data();
    return 0;
}


int Matrix::get_data()
{
    int r = get_rows();
    int c = get_cols();

    for (int i=0; i<r; i++)
        for (int j=0; j<c; j++)
            data[i*c+j] = rand() % 10;
        
    return 0;
}

int Matrix::show_data() const
{
    int r = get_rows();
    int c = get_cols();

    for (int i=0; i<r; i++)
    {
        for (int j=0; j<c; j++)
            cout << data[i*c+j] << " ";
        
        cout << endl;
    }

    cout << endl;
    return 0;
}

int Matrix::sort_data()
{
    int N = get_rows() * get_cols();

    for (int i=0; i<N-1; i++)
    {
        for (int j=0; j<N-1-i; j++)
        {
            if (data[j] > data[j+1])
            {
                int temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }

    return 0;
}

Matrix& Matrix::addmatrix(Matrix& op)
{
    static Matrix tm(rows, cols);

    if (rows == op.get_rows() && cols == op.get_cols())
    {
        for (int i=0; i<rows; i++)
            for (int j=0; j<cols; j++)
                tm.get_ptr()[i*cols+j] = this->at_i(i,j) + op.at_i(i, j);
        return tm;
    }

    cout << "Failed to Add (Diff Size)" << endl;
    
}


int Matrix::MultiplyMatrix(Matrix& m1, Matrix& m2)
{
    int r1 = m1.get_rows();
    int c1 = m1.get_cols();
    int r2 = m2.get_rows();
    int c2 = m2.get_cols();
    rows = r1;
    cols = c2;
    data = (int*)realloc(data, (r1*c2)*sizeof(int));

    if (c1 == r2)
    {
        for (int i=0; i<r1; i++)
        {
            for (int j=0; j<c2; j++)
            {   
                data[i*cols+j] = 0;
                for (int k=0; k<c1; k++)
                {
                    data[i*cols+j] += m1.data[i*c1+k]*m2.data[c2*k+j];
                }
            }
        }

        return 0;
    }

    return 1;
}
