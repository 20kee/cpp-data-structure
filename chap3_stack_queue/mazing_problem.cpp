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


int maze[100][100];
int mark[100][100];

struct item {
    int x, y, dir;
};

ostream& operator<<(ostream& os, item& it) {
    os << it.x << ", " << it.y << ", " << it.dir << endl;
    return os;
}

void path(int m, int p) {
    Stack<item> items(m*p);
    item start;
    int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    start.x = 1;
    start.y = 1;
    start.dir = 0;
    mark[1][1] = 1;
    items.push(start);

    while (!items.IsEmpty()) {
        item v = items.pop();
        cout << v;
        while (v.dir < 8) {
            int g = v.x + dx[v.dir];
            int h = v.y + dy[v.dir];
            if (g == m && h == p) {
                cout << endl;
                cout << items;
                return;
            }

            if (!mark[g][h] && !maze[g][h]) {
                mark[g][h] = 1;
                items.push(v);
                v.x = g; v.y = h; v.dir = 0; 
            }
            else v.dir++;
        }
    }

    return;
}

int main() {
    int input[12][15] = {
        {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
        {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
        {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}
    };

    for (int n=0; n<14; n++){
        for (int m=0; m<17; m++) {
            if (!n || n==13 || !m || m==16) {
                maze[n][m] = 1;
            } else {
                maze[n][m] = input[n-1][m-1];
            }

            mark[n][m] = 0;
        }
    }
    
    path(12, 15);
    

}