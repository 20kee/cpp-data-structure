#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include "time.h"

using namespace std;
template <class T>
class Polynomial;

template <class T>
class Term
{
    friend Polynomial<T>;

private:
    T coef;
    int exp;
};

template <class T>
class Polynomial {
public:
    Polynomial();
    // construct the polynomial p(x) = 0;
    Polynomial Add(Polynomial b);
    Polynomial Subtract(Polynomial a, Polynomial b);
    Polynomial Multiply(Polynomial a, Polynomial b);
    Polynomial operator+(Polynomial &);
    Polynomial operator-(Polynomial &);
    Polynomial operator*(Polynomial &);
    float Eval(float f);
    // return the sum of the polynomials *this and b
    // Polynomial Mult(Polynomial b);
    // return the product of the polynomials *this and b
    // float Eval(float f);
    // evaluate the polynomial *this at f and return the result
    void NewTerm(const float theCoeff, const int theExp);
    int Display();
    int GetData();
    template <class U>
    friend ostream &operator<<(ostream &, Polynomial<U> &);
    template <class U>
    friend istream &operator>>(istream &, Polynomial<U> &);

private:
    static Term<T> *termArray;
    static int capacity;
    static int free;
    int start, finish;
    int terms;
};

template <class T>
float Polynomial<T>::Eval(float f)
{
    float result = 0.0f;
    for (int i=(*this).start; i<=(*this).finish; i++)
    {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

template <class T>
Polynomial<T> Polynomial<T>::operator+(Polynomial<T>& poly)
{
    return (*this).Add(poly);
}

template <class T>
Polynomial<T> Polynomial<T>::operator-(Polynomial<T>& poly)
{
    Polynomial c;
    return c.Subtract(*this, poly);
}

template <class T>
Polynomial<T> Polynomial<T>::operator*(Polynomial<T>& poly)
{
    Polynomial c;
    return c.Multiply(*this, poly);
}

template <class T>
Polynomial<T> Polynomial<T>::Multiply(Polynomial<T> a, Polynomial<T> b)
{
    Polynomial c;
    Polynomial tmp;
    tmp.start = free;
    int aPos = a.start, bPos = b.start;
    for (int i=aPos; i <= a.finish; i++) {
        for (int j=bPos; j <= b.finish; j++) {
            float new_coef = a.termArray[i].coef * b.termArray[j].coef;
            int new_exp = a.termArray[i].exp + b.termArray[j].exp;
            tmp.NewTerm(new_coef, new_exp);
        }
    }
    tmp.finish = free-1;
    c.start = free;
    int max_exp = tmp.termArray[tmp.start].exp + 1;
    for (int j=tmp.start; j<=tmp.finish; j++)
    {
        int new_max_exp = -1;
        for (int i=tmp.start; i<=tmp.finish; i++)
        {
            if (tmp.termArray[i].exp > new_max_exp && tmp.termArray[i].exp < max_exp)
            {
                new_max_exp = tmp.termArray[i].exp;
            }
        }

        if (new_max_exp == -1) break;

        float new_coef = 0.0f;
        for (int i=tmp.start; i<=tmp.finish; i++)
        {
            if (tmp.termArray[i].exp == new_max_exp) {
                new_coef += tmp.termArray[i].coef;
            }
        }
        if (new_coef)
            c.NewTerm(new_coef, new_max_exp);
        max_exp = new_max_exp;
    }
    c.finish = free-1;
    *this = c;
    return c;
}


template<class T>
Polynomial<T> Polynomial<T>::Subtract(Polynomial<T> a, Polynomial<T> b)
{
    Polynomial c;
    int aPos = a.start, bPos = b.start;
    c.start = free;
    while ((aPos <= a.finish) && (bPos <= b.finish))
        if ((a.termArray[aPos].exp == b.termArray[bPos].exp))
        {
            float t = a.termArray[aPos].coef - b.termArray[bPos].coef;
            if (t)
                c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if ((a.termArray[aPos].exp < b.termArray[bPos].exp))
        {
            if (b.termArray[bPos].coef)
                c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else
        {
            if (a.termArray[aPos].coef)
            c.NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
            aPos++;
        }

    for (; aPos < a.finish; aPos++)
        c.NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
    for (; bPos < b.finish; bPos++)
        c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
    c.finish = free - 1;
    *this = c;
    return c;
}

template <class T>
istream& operator>>(istream& is, Polynomial<T>& poly)
{
    poly.GetData();
    return is;
}

template <class T>
ostream& operator<<(ostream& os, Polynomial<T>& poly)
{
    poly.Display();
    return os;
}


template <class T>
Polynomial<T>::Polynomial()
{
    start = -1;
    finish = -1;
    terms = 0;
}

template <class T>
int Polynomial<T>::Display()
{
    int aPos = start;
    for (; aPos <= finish; aPos++)
    {
        cout << termArray[aPos].coef << "x^" << termArray[aPos].exp;
        if ((aPos - finish) != 0)
            cout << " + ";
    }
    cout << "\n";
    return 0;
}


template <class T>
void Polynomial<T>::NewTerm(const float theCoeff, const int theExp)
{
    if (terms == capacity)
    {
        capacity *= 2;
        Term<T> *temp = new Term<T>[capacity];
        memcpy(temp, termArray, sizeof(int) * free);
        delete[] termArray;

        termArray = temp;
    }

    termArray[free].coef = theCoeff;

    termArray[free++].exp = theExp;
}


template <class T>
int Polynomial<T>::GetData()
{
    int i, degree;
    float coef;
    int expo;
    cout << "Enter Degree Of Polynomial:";
    cin >> degree;
    start = free;
    // coef??? ????????? ???????????? ???????????? ???????????? ???????????? ?????? ???????????? ????????????.
    for (i = degree; i >= 0; i--)
    {
        coef = ((rand()%10)+1) / ((rand() % 10)+1); 
        cout << "Enter exponent of x^" << i << ":" << i << endl;
        if (coef)
            NewTerm(coef, i);
    }
    finish = free - 1;
    terms = finish - start + 1;
    return 0;
}

template <class T>
Polynomial<T> Polynomial<T>::Add(Polynomial<T> b)
{
    Polynomial c;
    int aPos = start, bPos = b.start;
    c.start = free;
    while ((aPos <= finish) && (bPos <= b.finish))
        if ((termArray[aPos].exp == b.termArray[bPos].exp))
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t)
                c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if ((termArray[aPos].exp < b.termArray[bPos].exp))
        {   
            if (b.termArray[bPos].coef)
                c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else
        {
            if (termArray[aPos].coef)
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }

    for (; aPos < finish; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.finish; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    c.finish = free - 1;

    return c;
}

template <class T>
int Polynomial<T>::capacity = 100;

template <class T>
Term<T> *Polynomial<T>::termArray = new Term<T>[100];

template <class T>
int Polynomial<T>::free = 0;

int main(void)
{
    srand(time(NULL));
    int choice;

    Polynomial<float> P1, P2, P3, P4;
    cout << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x)=5x^3+0x^2+3x^1+0x^0\n";
    cout << "Enter Polynomial1:-" << endl;
    // P1.GetData();
    cin >> P1;
    cout << "Enter Polynomial2:-" << endl;
    // P2.GetData();
    cin >> P2;
    cout << "Enter Polynomial3:-" << endl;
    // P3.GetData();
    cin >> P3;
    while (1)
    {
        cout << "\n****** Menu Selection ******" << endl;
        cout << "1: Addition\n2: Substraction\n3: Multiplication\n0: Exit" << endl;
        cout << "Enter your choice:";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "\n--------------- Addition ---------------\n";
                cout << "Polynomial1:" << P1;
                // P1.Display();
                cout << "Polynomial2:" << P2;
                // P2.Display();

                P3 = P1.Add(P2);
                cout << "Polynomial3:" << P3;
                // P3.Display();

                P4 = P1 + P2 + P3;
                // P4.Display();
                cout << "Polynomial4:" << P4;
                cout << "----------------------------------------\n";
                break;
            case 2:
                cout << "\n------------- Substraction -------------\n";
                cout << "Polynomial1:" << P1;
                // P1.Display();
                cout << "Polynomial2:" << P2;
                // P2.Display();
                P3.Subtract(P1, P2); // ?????? ?????? ?????? ??????
                cout << "Polynomial3:" << P3;
                P4 = P1 - P2;
                cout << "Polynomial4:" << P4;
                cout << "----------------------------------------\n";
                break;
            case 3:
                cout << "\n----------- Multiplication -------------\n";
                cout << "Polynomial1:" << P1;
                // P1.Display();
                cout << "Polynomial2:" << P2;
                // P2.Display( );

                P3.Multiply(P1, P2);
                cout << "Polynomial3:" << P3;
                
                P4 = P1 * P2;
                cout << "Polynomial4:" << P4;
                cout << "----------------------------------------\n";
                break;
            case 4: // P2.Eval(5); ?????? ?????? ?????? ??????
                cout << P4;
                cout << P2.Eval(5);
                break;
            case 0:
                cout << "Good Bye...!!!" << endl;
                exit(0);
        }
    }

    // system("pause");

    return 0;
}