#include <iostream>
#include <memory>
#include <cstring>
#include <cstdlib>
#include "time.h"

using namespace std;

template <class T>
class Deque {
private:
    T* deque;
    int front;
    int total;
    int rear;
    int capacity;
public:
    Deque(int capacity) {
        front = capacity/3;
        rear = capacity/3;
        total = 0;
        deque = new T[capacity];
    }

    int getFront() { return front; }
    int getRear() { return rear; }
    T* getDeque() { return deque; }

    T& get_front();
    T& get_rear();

    void push_front(T const& x);
    void push_rear(T const& x);

    void pop_front();
    void pop_rear();

    bool IsEmpty() { if (total == 0) return true; return false; }
    
    template <class U>
    friend ostream& operator<<(ostream& os, Deque<U>& deque);
    
    template <class U>
    friend istream& operator>>(istream& is, Deque<U>& deque);
    
};

template <class T>
ostream& operator<<(ostream& os, Deque<T>& deque) {
    for (int i=deque.front+1; i<=deque.rear; i++)
        os << deque.deque[i] << " ";
    os << endl;
    return os;
}

template <class T>
istream& operator>>(istream& is, Deque<T>& deque) {
    srand(time(NULL));
    for (int i=0; i<10; i++) {
        if (i%2 == 0) {
            deque.push_front(rand()%10);
        }
        else {
            deque.push_rear(rand()%10);
        }
    }
    return is;
}

template <class T>
void Deque<T>::pop_front() {
    if (!IsEmpty()) {
        deque[++front].~T();
        total -= 1;
        return;
    }
    throw "No element to pop for you.";
}

template <class T>
void Deque<T>::pop_rear() {
    if (!IsEmpty()) {
        deque[rear--].~T();
        total -= 1;
        return;
    }
    throw "No element to pop for you.";
}


template <class T>
void Deque<T>::push_rear(T const& x) {
    if (rear == capacity-1) {
        int new_capacity = 2*capacity;
        T* new_deque = new T[new_capacity];
        memcpy(new_deque+(new_capacity/3), deque+front+1, sizeof(T)*total);
        delete[] deque;
        deque = new_deque;
        front = (new_capacity/3)-1;
        rear = front + total;
        capacity = new_capacity;
    }
    total++;
    deque[++rear] = x;
}

template <class T>
void Deque<T>::push_front(T const& x) {
    if (front == -1) {
        int new_capacity = 2*capacity;
        T* new_deque = new T[new_capacity];
        memcpy(new_deque+(new_capacity/3), deque, sizeof(T)*total);
        delete[] deque;
        deque = new_deque;
        front = (new_capacity/3)-1;
        rear = front + total;
        capacity = new_capacity;
    }
    total++;
    deque[front--] = x;
}

template <class T>
T& Deque<T>::get_rear() {
    if (!IsEmpty()) {
        return deque[rear];
    }
    throw "no element to show you!";
}

template <class T>
T& Deque<T>::get_front() {
    if (!IsEmpty()) {
        return deque[front+1];
    }
    throw "no element to show you!";
}

int main() {
    Deque<int> deque(2);
    deque.push_front(3);
    deque.push_rear(4);
    cout << deque;
    deque.push_front(3);
    deque.push_rear(7);
    deque.push_rear(2);
    deque.push_front(7);
    cout << deque;
    deque.push_rear(1);
    deque.push_front(3);
    deque.push_front(5);
    deque.push_rear(4);
    deque.push_front(6);
    deque.push_front(1);
    cout << deque;
    deque.push_rear(4);
    deque.push_front(3);
    deque.push_rear(3);
    deque.push_front(2);
    deque.push_front(1);
    deque.push_rear(5);
    cout << deque;
    deque.push_rear(4);
    deque.push_rear(9);
    deque.push_front(5);
    deque.push_rear(2);
    deque.push_rear(4);
    cout << deque;
    deque.pop_front();
    deque.pop_rear();
    deque.pop_front();
    deque.pop_rear();
    deque.pop_front();
    deque.pop_rear();
    cout << deque;
    deque.pop_front();
    deque.pop_rear();
    deque.pop_front();
    deque.pop_rear();
    cout << deque;
    deque.pop_front();
    deque.pop_rear();
    deque.pop_front();
    deque.pop_rear();
    cout << deque;
    return 0;
}