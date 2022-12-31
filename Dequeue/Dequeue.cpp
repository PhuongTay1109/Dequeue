#include "graphics.h"
#include "Dequeue.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void drawDequeueFrame();
void drawWelcomeInterface();
void dequeueSimulation();
void drawPushBack(string data);
void drawPushFront(string data);
void drawPopFront(string prevFrontNode);
void drawPopBack(int x1, int y1, int x2, int y2, string prevRearNode);
void drawObjectsInDequeue(RECT pos);

DEQUEUE* dq = new DEQUEUE();
RECT firstNodePos = { 350, 225, 400, 275 }; 
RECT secondNodePos = { 450, 225, 500, 275 }; 
RECT frontPos = { 180, 225, 230, 275 };
RECT backPos = { 820, 225, 870, 275 };
int sleepTime = 100;
int maxCap = 4;

int main()
{
    dq->init();
    initgraph();
    drawWelcomeInterface(); 
    _getch();
    system("cls");

    drawDequeueFrame();
    dequeueSimulation();

    return 0;
}

void drawDequeueFrame()
{
    setcolor(15);
    line(300, 200, 750, 200);
    line(300, 300, 750, 300);
} 

void drawWelcomeInterface()
{
    drawText(430, 80, "DEQUEUE SIMULATION", 255, 0, 0);
    drawDequeueFrame();

    for (int i = 100; i <= 200; i += 100)
    {

        rectangle(firstNodePos.left + i, firstNodePos.top, firstNodePos.right + i, firstNodePos.bottom);
    }

    drawText(240, 210, "POPFRONT", 255, 255, 0);
    setcolor(12);
    line(230, 240, 350, 240);
    setcolor(12);
    line(230, 240, 240, 230);
    setcolor(12);
    line(230, 240, 240, 250);
    setcolor(12);
    drawText(235, 268, "PUSHFRONT", 255, 255, 0);
    setcolor(12);
    line(230, 265, 350, 265);
    setcolor(12);
    line(350, 265, 340, 255);
    setcolor(12);
    line(350, 265, 340, 275);
    rectangle(frontPos);

    drawText(720, 210, "PUSHBACK", 255, 255, 0);
    setcolor(12);
    line(700, 240, 820, 240);
    setcolor(12);
    line(700, 240, 710, 230);
    setcolor(12);
    line(700, 240, 710, 250);
    setcolor(12);
    drawText(720, 268, "POPBACK", 255, 255, 0);
    setcolor(12);
    line(700, 265, 820, 265);
    setcolor(12);
    line(820, 265, 810, 255);
    setcolor(12);
    line(820, 265, 810, 275);
    rectangle(backPos);

    drawText(320, 400, "This program simulates the dequeue having capacity of 4 objects.", 255, 255, 255);
    drawText(420, 430, "Press any key to start.", 255, 255, 255);
}

void drawObjectsInDequeue(RECT pos)
{
    system("cls");
    drawDequeueFrame();
    if (dq->isEmpty()) {
        return;
    }
    NODE* tmp = dq->front;
    for (int i = 0; i < dq->size() * 100; i += 100)
    {
        block(pos.left + i, pos.top, pos.right + i, pos.bottom, tmp->data.c_str());
        tmp = tmp->next;
    }
}

void drawPopFront(string prevFrontNode)
{
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    for (int i = 0; i < 170; i += 10)
    {
        system("cls");
        if (i > 100) {
            block(x1 - i, y1, x2 - i, y2, prevFrontNode.c_str());
            drawObjectsInDequeue(firstNodePos);
        }
        else
        {
            block(x1 - i, y1, x2 - i, y2, prevFrontNode.c_str());
            drawObjectsInDequeue(secondNodePos);
        }
        Sleep(sleepTime);
    }
    drawObjectsInDequeue(firstNodePos);
}

void drawPopBack(int x1, int y1, int x2, int y2, string prevRearNode)
{
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 += i;
        x2 += i;
        if (x1 > backPos.left)
            break;
        block(x1, y1, x2, y2, prevRearNode.c_str());
        drawObjectsInDequeue(firstNodePos);
        Sleep(sleepTime);
    }
    drawObjectsInDequeue(firstNodePos);
}

void drawPushBack(string data)
{
    int x1 = backPos.left, y1 = backPos.top, x2 = backPos.right, y2 = backPos.bottom;
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 -= i;
        x2 -= i;
        if (x1 < (820 - 100 * (maxCap - dq->size()) - 20 - 50))
            break;
        block(x1, y1, x2, y2, data.c_str());
        drawObjectsInDequeue(firstNodePos);
        Sleep(sleepTime);
    }
    dq->insert(data, 0);
    drawObjectsInDequeue(firstNodePos);
}

void drawPushFront(string data)
{
    int x1 = frontPos.left, y1 = frontPos.top, x2 = frontPos.right, y2 = frontPos.bottom;
    for (int i = 0; i < 170; i += 10)
    {
        system("cls");
        if (i > 50) {
            block(x1 + i, y1, x2 + i, y2, data.c_str());
            drawObjectsInDequeue(secondNodePos);
        }
        else
        {
            block(x1 + i, y1, x2 + i, y2, data.c_str());
            drawObjectsInDequeue(firstNodePos);
        }
        Sleep(sleepTime);
    }
    dq->insert(data, 1);
    drawObjectsInDequeue(firstNodePos);
}

void dequeueSimulation()
{
    cout << "Press '1' to Push_back." << endl;
    cout << "Press '2' to Push_front." << endl;
    cout << "Press '3' to Pop_back." << endl;
    cout << "Press '4' to Pop_front." << endl;
    cout << "Press any other key to esc." << endl;
    int opt;
    string data;
    cin >> opt;
    if (opt == 1)
    {
        if (dq->size() >= 4)
        {
            cout << "Dequeue is full. You can only choose Delete." << endl;;
            dequeueSimulation();
        }
        else
        {
            cout << "Enter data: ";
            cin >> data;
            drawPushBack(data);
            dequeueSimulation();
        }
    }
    else if (opt == 2)
    {
        if (dq->size() >= 4)
        {
            cout << "Dequeue is full. You can only choose Delete." << endl;;
            dequeueSimulation();
        }
        else
        {
            cout << "Enter data: ";
            cin >> data;
            drawPushFront(data);
            dequeueSimulation();
        }
    }
    else if (opt == 3)
    {
        if (!dq->isEmpty())
        {
            string prevRearNode = dq->rear->data; 
            int x1 = firstNodePos.left + 100*dq->size();
            int y1 = firstNodePos.top;
            int x2 = firstNodePos.right + 100 * dq->size();
            int y2 = firstNodePos.bottom;
            dq->deleteElement(0);
            drawPopBack(x1, y1, x2, y2, prevRearNode);
            dequeueSimulation();
        }
        else
        {
            cout << "Dequeue is empty. You must insert data first." << endl;
            dequeueSimulation();
        }
    }
    else if (opt == 4)
    {
        if (!dq->isEmpty())
        {
            string prevFrontNode = dq->front->data; 
            dq->deleteElement(1); 
            drawPopFront(prevFrontNode);
            dequeueSimulation();
        }
        else
        {
            cout << "Dequeue is empty. You must insert data first." << endl;
            dequeueSimulation();
        }
    }
    else
    {
        system("cls");
    }
}

