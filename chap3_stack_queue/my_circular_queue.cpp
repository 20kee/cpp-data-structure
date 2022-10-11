#include <iostream>
#include <memory>
#include <cstring>
#include "time.h"
using namespace std;

template <class T>
class Queue
{
public:
	Queue(int queueCapacity = 10);
	bool IsEmpty();
	T& Front();
	T& Rear();
	void Push(T const& x);
	void Pop();
    int getCapacity() { return capacity; }
    int getFront() { return front; }
    int getRear() { return rear; }
    T*& getQueue() { return queue; }
	template <class U>
	friend ostream& operator<<(ostream& os, Queue<U>&);
	
	template <class U>
	friend istream& operator>>(istream& os, Queue<U>&);
private:
	T* queue;
	int front;
	int rear;
    int total;
	int capacity;
};

template <class T>
ostream& operator<<(ostream& os, Queue<T>& queue) {
    int start = queue.getFront();
    while (start != queue.getRear()) {
        cout << queue.getQueue()[(start+1)%queue.getCapacity()] << " ";
        start = (start+1) % queue.getCapacity();
    }
    cout << endl;
    return os;
}


template <class T>
void Queue<T>::Pop() {
    if (!IsEmpty()) {
        front = (front+1) % capacity;
        queue[front].~T();
        total -= 1;
        return;
    }
    throw "No element to pop!";
}
template <class T>
void Queue<T>::Push(T const& x) {
    if (total == capacity) {
        int new_capacity = capacity*2;
        T* new_queue = new T[new_capacity];
        int start = (front+1) % capacity;
        memcpy(new_queue, queue+start, sizeof(T)*(capacity-start));
        memcpy(new_queue + capacity-start, queue, sizeof(T)*start);
        delete[] queue;
        queue = new_queue;
        front = -1;
        rear = capacity-1;
        capacity = new_capacity;
    }
    total ++;
    rear = (rear+1) % capacity;
    queue[rear] = x;
}

template <class T>
T& Queue<T>::Rear() {
    if (!IsEmpty()) {
        return queue[rear];
    }
    throw "No element to refer";
}

template <class T>
bool Queue<T>::IsEmpty() {
    if (total == 0) return true;
    return false;
}

template <class T>
T& Queue<T>::Front() {
    if (!IsEmpty()) {
        return queue[(front+1)%capacity];
    }
    throw "No element to refer";
}

template <class T>
Queue<T>::Queue(int queueCapacity) {
    front = -1;
    rear = -1;
    total = 0;
    capacity = queueCapacity;
    queue = new T[capacity];
}

int main()
{
	Queue<int> s(3);
	s.Push(2);
	s.Push(1);
	s.Push(4);
	s.Push(10);
	s.Push(5);
    cout << s;
    s.Pop();
	s.Push(7);
    s.Pop();
    s.Push(2);
    s.Pop();
    cout << s;
	s.Push(12);
    s.Pop();
	s.Push(5);
    s.Pop();
    s.Pop();
    s.Pop();
    cout << s;
    
	if (s.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}

	cout << s;
	return 0;
}
