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

void drawWelcomeInterface();
void dequeueSimulation();
void drawPushBack(string data);
void drawPushFront(string data);
void drawPopFront(string prevFrontNode);
void drawPopBack(int x1, int y1, int x2, int y2, string prevRearNode);
void drawObjectsInDequeue(RECT pos);

DEQUEUE* dq = new DEQUEUE();

int main()
{
    dq->init(); // khởi tạo dequeue
    initgraph(); // khởi tạo graphic
    drawWelcomeInterface(); // giao diện bắt đầu
    _getch();
    system("cls");

    drawDequeueFrame();
    dequeueSimulation();

    return 0;
}

// Vẽ giao diện bắt đầu
void drawWelcomeInterface()
{
    drawText(430, 80, "DEQUEUE SIMULATION", 255, 0, 0);
    drawDequeueFrame();

    // Vẽ 2 node ở trong dequeue
    for (int i = 100; i <= 200; i += 100)
    {

        rectangle(firstNodePos.left + i, firstNodePos.top, firstNodePos.right + i, firstNodePos.bottom);
    }

    // Vẽ node phía trước để popfront hoặc pushfront
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

    // Vẽ node phía sau để popback hoặc pushback
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

// Vẽ các node trong dequeue bắt đầu từ vị trí pos
void drawObjectsInDequeue(RECT pos)
{
    system("cls");
    drawDequeueFrame(); // vẽ khung dequeue
    // Nếu dequeue rỗng thì kết thúc sau khi vẽ khung, không cần vẽ node bên trong
    if (dq->isEmpty()) {
        return;
    }

    // duyệt các node trong dequeue và vẽ ra bắt đầu từ vị trí được truyền vào
    NODE* tmp = dq->front;
    for (int i = 0; i < dq->size() * 100; i += 100)
    {
        block(pos.left + i, pos.top, pos.right + i, pos.bottom, tmp->data.c_str());
        tmp = tmp->next;
    }
}


// Vẽ mô phỏng xóa đầu - giống hàm delete của queue
void drawPopFront(string prevFrontNode)
{
    // node được xóa bắt đầu di chuyển từ vị trí của node đầu tiên
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    for (int i = 0; i < 170; i += 10)
    {
        system("cls");
        // Nếu node đã di chuyển ra khỏi queue thì vẽ các node còn lại bắt đầu từ vị trí đầu tiên
        if (i > 100) {
            block(x1 - i, y1, x2 - i, y2, prevFrontNode.c_str());
            drawObjectsInDequeue(firstNodePos);
        }
        // Nếu node đang di chuyển trong queue thì vẽ các node còn lại bắt đầu từ vị trí thứ hai
        else
        {
            block(x1 - i, y1, x2 - i, y2, prevFrontNode.c_str());
            drawObjectsInDequeue(secondNodePos);
        }
        Sleep(sleepTime);
    }
    // Vẽ lại dequeue 1 lần nữa sau khi vòng lặp kết thúc
    drawObjectsInDequeue(firstNodePos);
}

// Vẽ mô phỏng xóa sau
void drawPopBack(int x1, int y1, int x2, int y2, string prevRearNode)
{
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 += i;
        x2 += i;
        // Vẽ đến node backPos thì dừng
        if (x1 > backPos.left)
            break;
        block(x1, y1, x2, y2, prevRearNode.c_str());
        drawObjectsInDequeue(firstNodePos);
        Sleep(sleepTime);
    }
    // Vẽ lại dequeue 1 lần nữa sau khi vòng lặp kết thúc
    drawObjectsInDequeue(firstNodePos);
}

// Vẽ mô phỏng thêm sau 
void drawPushBack(string data)
{
    // Node được thêm vào bắt đầu di chuyển từ vị trí của backPos
    int x1 = backPos.left, y1 = backPos.top, x2 = backPos.right, y2 = backPos.bottom;
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 -= i;
        x2 -= i;
        // Điều kiện dừng
       // 820 - 20 cho chẵn số
       // maxCap - q.size là bước di chuyển
       // - 50 là độ rộng của node đó
        if (x1 < (820 - 100 * (maxCap - dq->size()) - 20 - 50))
            break;
        block(x1, y1, x2, y2, data.c_str());
        drawObjectsInDequeue(firstNodePos);
        Sleep(sleepTime);
    }
    // Insert node mới vào và vẽ lại dequeue 1 lần nữa
    dq->insert(data, 0);
    drawObjectsInDequeue(firstNodePos);
}

// Vẽ mô phỏng thêm trước
void drawPushFront(string data)
{
   // node được thêm bắt đầu di chuyển từ vị trí của frontPos
    int x1 = frontPos.left, y1 = frontPos.top, x2 = frontPos.right, y2 = frontPos.bottom;
    for (int i = 0; i < 170; i += 10)
    {
        system("cls");
        // Nếu node đã vào dequeue thì vẽ các node còn lại bắt đầu từ vị trí thứ hai
        if (i > 50) {
            block(x1 + i, y1, x2 + i, y2, data.c_str());
            drawObjectsInDequeue(secondNodePos);
        }
        // Nếu node đang di chuyển vào dequeue thì vẽ các node còn lại bắt đầu từ vị trí thứ nhất
        else
        {
            block(x1 + i, y1, x2 + i, y2, data.c_str());
            drawObjectsInDequeue(firstNodePos);
        }
        Sleep(sleepTime);
    }
    // Insert node mới và vẽ lại queue 1 lần nữa
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
            string prevRearNode = dq->rear->data; // dữ liệu của node cuối trong dequeue cũ
            // vị trí của node cuối trong dequeue = vị trí của node đầu + 100*sizedequeue
            int x1 = firstNodePos.left + 100*dq->size();
            int y1 = firstNodePos.top;
            int x2 = firstNodePos.right + 100 * dq->size();
            int y2 = firstNodePos.bottom;
            dq->deleteElement(0); // xóa cuối
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
            string prevFrontNode = dq->front->data; // dữ liệu của node đầu trong dequeue cũ
            dq->deleteElement(1); // xóa đầu
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

