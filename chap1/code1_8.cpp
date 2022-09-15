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

class Matrix;

class Term
{
private:
    float coef;
    int exp;
public:
    friend Matrix;
    Term() : coef(0.0f), exp(0) {}
    Term(int data) : exp(data) {}
    int get_exp() const { return exp; }
    void set_exp(int exp) { this->exp = exp; }
};

class Matrix
{
private:
    int rows, cols;
    static Term *TermElement;
    static int free;
    int start, finish;
    int terms;

public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        start = free;
        finish = start + rows * cols;
        free = finish;
    }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    int get_start() const { return start; }

    int get_data();
    int show_data() const;
    int sort_data();
    Matrix &addMatrix(const Matrix &) const;
    int MultiplyMatrix(const Matrix &, const Matrix &);
};

int Matrix::free = 0;
Term *Matrix::TermElement = new Term[100];

int main(void)
{
    Matrix matrixA(3, 4);
    Matrix matrixB(3, 4);
    Matrix matrixC(3, 4);
    // F[5,6] = D[3,4] + E[5,6] 구현하기 실습
    srand(time(NULL));
    cout << endl
         << "matrix A:" << endl;
    matrixA.get_data();
    matrixA.show_data();
    cout << endl
         << "matrix B:" << endl;
    matrixB.get_data();
    matrixB.show_data();
    cout << endl
         << "matrix C = A + B:" << endl;
    matrixC = matrixA.addMatrix(matrixB);
    matrixC.show_data();

    system("pause");

    return 0;
}

int Matrix::get_data()
{
    int r = get_rows();
    int c = get_cols();

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            TermElement[start + i * c + j].set_exp(rand()%10);

    return 0;
}

int Matrix::show_data() const
{
    int r = this->get_rows();
    int c = this->get_cols();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << TermElement[start + i * c + j].get_exp() << " ";
        cout << endl;
    }

    cout << endl;
    return 0;
}

int Matrix::sort_data()
{
    for (int i = start; i < finish - 1; i++)
    {
        for (int j = start; j < finish - 1; j++)
        {
            if (TermElement[j].get_exp() > TermElement[j + 1].get_exp())
            {
                int temp = TermElement[j].get_exp();
                TermElement[j].set_exp(TermElement[j + 1].get_exp());
                TermElement[j + 1].set_exp(temp);
            }
        }
    }

    return 0;
}

Matrix &Matrix::addMatrix(const Matrix &op) const
{
    static Matrix tm(rows, cols);
    if (rows == op.get_rows() && cols == op.get_cols())
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                TermElement[tm.get_start() + i * cols + j].set_exp(TermElement[start + i * cols + j].get_exp() + TermElement[op.get_start() + i * op.get_cols() + j].get_exp());

        return tm;
    }

    cout << "Failed to Add (Diff Size)" << endl;
}

int Matrix::MultiplyMatrix(const Matrix &m1, const Matrix &m2)
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
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                TermElement[start + i * cols + j].set_exp(0);
                for (int k = 0; k < c1; k++)
                {
                    TermElement[start + i * cols + j].set_exp(TermElement[start + i * cols + j].get_exp() + TermElement[s1 + i * c1 + k].get_exp() * TermElement[s2 + c2 * k + j].get_exp());
        
                }
            }
        }
        return 0;
    }
    cout << "Failed to multiply two matrix." << endl;

    return 1;
}