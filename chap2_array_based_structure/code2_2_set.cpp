#include <iostream>
#include <memory>
#include <cstring>
using namespace std;
#define MaxSize 100

template <class T>
class Set
{
private:
    T data[MaxSize];
    int capacity;
    int top;
public:
    Set(int SetCapacity = 10);
    bool IsFull();
    int Size() const; // HowMany( )에 해당됨
    bool IsEmpty() const;
    virtual T &Pop();
    virtual void Push(const T &);

    template <class T2>
    friend ostream& operator <<(ostream &,const Set<T2>&);

};

template <class T>
ostream& operator<<(ostream& os,const Set<T>& set)
{
    if (set.top >= 0) {
        os << set.data[0];
        for (int i=1; i<=set.top; i++) {
            os << " " << (set.data)[i];
        }
    }
    cout << endl;
    return os;
    
}

// Visual Studio2019에서 Set.h, Set.cpp로 분리하지 않아야 함
template <class T>
Set<T>::Set(int SetCapacity) : capacity(SetCapacity)
{
    if (capacity < 1)
        throw "Capacity must be > 0";
    top = -1;
}


template <class T>
int Set<T>::Size() const
{
    return top + 1;
}

template <class T>
bool Set<T>::IsEmpty() const
{
    return top < 0;
}

template <class T>
void Set<T>::Push(const T &x)
{
    for (int i=0; i<=top; i++) 
        if (data[i] == x) return;


    if (top == capacity - 1)
        return;

    data[++top] = x;
}

template <class T>

T &Set<T>::Pop()
{
    static T retValue;
    if (IsEmpty())
        throw "Set is empty, cannot delete";
    int deletePos = top / 2;
    retValue = data[deletePos];
    // 실습 사항: no ordering상태로 pop되게 수정
    // copy(data + deletePos + 1, data + top + 1, data + deletePos);
    memcpy(data + deletePos, data + deletePos + 1, sizeof(int) * (top - deletePos));
    top--;
    return retValue;
}

template <class T>
inline bool Set<T>::IsFull()
{
    if (top == MaxSize - 1)
        return true;
    else
        return false;
}

int main() {
	Set<int> b(4);
	int n;
	//Set<float> fo(10);에 대하여도 구현할 것
	//화면에서 임의 숫자를 입력받아 Push( ) 호출하도록 수정
	b.Push(3);
	b.Push(5);
	b.Push(1);
	b.Push(3);
	b.Push(7);
    cout << b;
	if (b.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}
	while (!b.IsEmpty()) {
		n = b.Pop();
		cout << "b.Pop() = " << n << endl;
	}
	return 0;

}