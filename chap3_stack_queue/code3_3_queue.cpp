#include <iostream>
#include <memory>
#include <cstring>
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
	template <class U>
	friend ostream& operator<<(ostream& os, Queue<U>&);
	
	template <class U>
	friend istream& operator>>(istream& os, Queue<U>&);
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};
template <class T>
ostream& operator<<(ostream& os, Queue<T>& s) {
	
	return os;
}
template <class T>
istream& operator>>(istream& is, Queue<T>& s) {
	return is;
}
template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity)
{
	queue = new T[capacity];
	front = rear = -1;
}

template <class T>
inline bool  Queue<T>::IsEmpty() { return front == rear; }

template <class T>
inline T& Queue<T>::Front()
{
	if (IsEmpty()) throw "Queue is empty. No front element";
	return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
	if (IsEmpty()) throw "Queue is empty. No rear element";
	return queue[rear];
}

// doubling queue capacity
template <class T>
void Queue<T>::Push(T const& x)
{
	if (rear % capacity == front % capacity)
	{
		T* newQueue = new T[2 * capacity];
		// allocate an array with twice the capacity
		int start = (front + 1) % capacity;
		if (start < 1)
			//copy(queue + start, queue + start + capacity - 1, newQueue);
			memcpy(newQueue, queue, sizeof(T)*capacity);
		else
		{
			//copy(queue + start, queue + capacity, newQueue);
			//copy(queue, queue + rear + 1, newQueue + capacity - start);
			memcpy(newQueue, queue + start, sizeof(T)*(capacity-start));
			memcpy(newQueue + capacity - start, queue, sizeof(T)*(rear + 1));
		}
		// switch to new Queue
		front = -1;
		rear = capacity-1;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}

	rear = (rear + 1) % capacity;
	queue[rear] = x;
}

template <class T>
void Queue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty. Cannot delelte.";
	front = (front + 1) % capacity;
	queue[front].~T();
}

int main()
{
	Queue<int> s(3);
	s.Push(2);
	s.Push(1);
	s.Push(4);
	s.Push(10); //
	s.Push(5);
	s.Push(7);
	s.Push(2);
	s.Push(12);
	s.Push(5);
	if (s.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}

	while (!s.IsEmpty()) {
		cout << s.Front() << endl;
		s.Pop();
	}
	//cout << s << endl;//
	// system("pause");
	return 0;
}
