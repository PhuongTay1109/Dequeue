#pragma once

RECT firstNodePos = { 350, 225, 400, 275 }; // vị trí của node đầu tiên trong dequeue
RECT secondNodePos = { 450, 225, 500, 275 }; // vị trí của node thứ hai trong dequeue
RECT frontPos = { 180, 225, 230, 275 }; // vị trí node dừng lại khi thực hiện popfront/ vị trí node bắt đầu di chuyển khi thực hiện pushfront
RECT backPos = { 820, 225, 870, 275 }; // vị trí node dừng lại khi thực hiện popback/ vị trí node bắt đầu di chuyển khi thực hiện pushback
int sleepTime = 100;
int maxCap = 4; // số node tối đa của dequeue

// dựng dequeue
struct NODE {
    string data;
    NODE* next;
    NODE* prev;
};

struct DEQUEUE {
    NODE* front; 
    NODE* rear;

    void init() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return rear == nullptr;
    }

    NODE* makeNode(string x) {
        NODE* newNode = new NODE();
        newNode->data = x;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    // left = true: push front
    // left = false: push back
    void insert(string x, bool left) {
        NODE* newNode = makeNode(x);
        if (this->isEmpty()) {
            front = rear = newNode;
            return;
        }
        // Push front 
        if (left) {
            newNode->next = front;
            if (front != nullptr)
                front->prev = newNode;
            front = newNode;
        }
        // Push back 
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }
    
    // left = true: pop front
    // left = false: pop back
    void deleteElement(bool left) {
        if (this->isEmpty())
            return;
        // Pop front
        if (left) {
            NODE* tmp = front;
            front = front->next;
            if (front == nullptr)
                rear = nullptr;
            else
                front->prev = nullptr;
            delete tmp;
        }
        // Pop back
        else {
            NODE* tmp = rear;
            rear = rear->prev;
            if (rear == nullptr)
                front = nullptr;
            else
                rear->next = nullptr;
            delete (tmp);
        }
    }

    int size()
    {
        NODE* tmp = front;
        int cnt = 0;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }
};

void drawDequeueFrame()
{
    setcolor(15);
    line(300, 200, 750, 200);
    line(300, 300, 750, 300);
}
