#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>

using namespace std;

template <class T>
class Stack {
private:
    T* stack;
    int capacity;
    int top;
public:
    Stack(int capacity) {
        this->capacity = capacity;
        stack = new T[capacity];
        top = -1;
    }
    ~Stack() { delete[] stack; }

    bool IsEmpty() { if (top==-1) return true; return false;}
    void push(T const& x);
    T& pop();

    template <class U>
    friend ostream& operator<<(ostream&, Stack<U>& stack);

    template <class U>
    friend istream& operator>>(istream&, Stack<U>& stack);
};

template <class T>
ostream& operator<<(ostream& os, Stack<T>& stack) {
    for (int i=0; i<=stack.top; i++)
        os << stack.stack[i] << " ";
    os << endl;
    return os;
}

template <class T>
T& Stack<T>::pop() {
    if (top >= 0) {
        top--;
        return stack[top+1];
    }
    throw "No element to pop";
}

template <class T>
void Stack<T>::push(T const& x) {
    if (top == capacity-1) {
        T* new_stack = new T[capacity*2];
        memcpy(new_stack, stack, sizeof(T)*capacity);
        capacity = 2*capacity;
        delete[] stack;
        stack = new_stack;
    }
    stack[++top] = x;
}