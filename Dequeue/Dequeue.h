#pragma once

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

