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
private:
    int rows, cols;
    static int* data;
    static int free;
    int start, finish;
    int terms;
public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        start = free;
        finish = start + rows*cols;
        terms = rows*cols;
        free = finish;
    }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    int get_start() const { return start; }

    int get_data();
    int show_data() const;
    int sort_data();
    Matrix& addMatrix(const Matrix&);
    int MultiplyMatrix(const Matrix&, const Matrix&);
};

int Matrix::free = 0;
int* Matrix::data = new int[100];

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

    Matrix matrixD = matrixA.addMatrix(matrixA1);
    matrixD.show_data();

    matrixB.get_data();
    matrixB.show_data();

    matrixC.MultiplyMatrix(matrixA, matrixB);
    matrixC.show_data();

    matrixC.sort_data();
    matrixC.show_data();

    return 0;
}

int Matrix::get_data()
{
    int r = get_rows();
    int c = get_cols();

    for (int i=0; i<r; i++)
        for (int j=0; j<c; j++)
            data[start+i*c+j] = rand() % 10;
        
    return 0;
}

int Matrix::show_data() const
{
    int r = this->get_rows();
    int c = this->get_cols();

    for (int i=0; i<r; i++)
    {
        for (int j=0; j<c; j++)
            cout << data[start+i*c+j] << " ";
        cout << endl;
    }

    cout << endl;
    return 0;
}

int Matrix::sort_data()
{
    for (int i=start; i<finish-1; i++)
    {
        for (int j=start; j<finish-1; j++)
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

Matrix& Matrix::addMatrix(const Matrix& op)
{
    static Matrix tm(rows, cols);
    if (rows == op.get_rows() && cols == op.get_cols())
    {
        for (int i=0; i<rows; i++)
            for (int j=0; j<cols; j++)
                tm.data[tm.get_start()+i*cols+j] = data[start+i*cols+j] + op.data[op.get_start()+i*op.get_cols()+j];

        return tm;
    }

    cout << "Failed to Add (Diff Size)" << endl;
}

int Matrix::MultiplyMatrix(const Matrix& m1, const Matrix& m2)
{
    int r1 = m1.get_rows();
    int c1 = m1.get_cols();
    int r2 = m2.get_rows();
    int c2 = m2.get_cols();
    int s1 = m1.get_start();
    int s2 = m2.get_start();

    rows = r1;
    cols = c2;
    if (c1 == r2)
    {
        for (int i=0; i<r1; i++)
        {
            for (int j=0; j<c2; j++)
            {   
                data[start+i*cols+j] = 0;
                for (int k=0; k<c1; k++)
                {
                    data[start+i*cols+j] += m1.data[s1+i*c1+k]*m2.data[s2+c2*k+j];
                }
            }
        }
        return 0;
    }
    cout << "Failed to multiply two matrix." << endl;

    return 1;
}