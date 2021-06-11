#include <windows.h>
#include "Graphic.h"
#include "Circle.h"
#include "Polygon.h"
#include "Collider.h"

Graphic* graphic;
Collider* collider = new Collider();
Circle* circle = new Circle(100, 100., 20);
Circle* circle2 = new Circle(300, 300., 20);
Circle* circle3 = new Circle(50, 50., 20); 
Poly* poly1 = new Poly(200, 200, 3); 
Poly* poly2 = new Poly(400, 400, 5);

void logic() {
    // Update
    circle->logic();
    circle2->logic();
    circle3->logic();
    poly1->logic();
    poly2->logic();

    // collison? -> reaction!
    if (collider->collideEllipse(circle, circle2)) {
        circle->speedX = -(circle->speedX);
        circle->speedY = -(circle->speedY);
        circle2->speedX = -(circle2->speedX);
        circle2->speedY = -(circle2->speedY);
    }

    // collison? -> reaction!
    if (collider->collideEllipse(circle, circle3)) {
        circle->speedX = -(circle->speedX);
        circle->speedY = -(circle->speedY);
        circle3->speedX = -(circle3->speedX);
        circle3->speedY = -(circle3->speedY);
    }

    // collison? -> reaction!
    if (collider->collideEllipse(circle2, circle3)) {
        circle2->speedX = -(circle2->speedX);
        circle2->speedY = -(circle2->speedY);
        circle3->speedX = -(circle3->speedX);
        circle3->speedY = -(circle3->speedY);
    }



    // Render
    graphic->BeginDraw();
    graphic->ClearScreen();
    graphic->setBrush(D2D1::ColorF::Black);
    circle->draw(graphic->renderTarget, graphic->brush);
    graphic->setBrush(D2D1::ColorF::Green);
    circle2->draw(graphic->renderTarget, graphic->brush);
    graphic->setBrush(D2D1::ColorF::Violet);
    circle3->draw(graphic->renderTarget, graphic->brush);

    graphic->setBrush(D2D1::ColorF::ForestGreen);

    if (collider->collidePolygon(poly1, poly2)) {
        graphic->setBrush(D2D1::ColorF::Red);
    }

    poly1->draw(graphic->renderTarget, graphic->brush);
    poly2->draw(graphic->renderTarget, graphic->brush);
    graphic->EndDraw();
}

// Callback-Function for WIN32_Window
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT: break;

    case WM_KEYDOWN: break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Entypoint for WIN32 Desktop-App -> Defines window and starts Event-Loop with Messages
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{

    WNDCLASSEX winClass;

    winClass.lpszClassName = L"Direct2D";
    winClass.cbSize = sizeof(WNDCLASSEX);
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc = WndProc;
    winClass.hInstance = hInstance;
    winClass.hIcon = NULL;
    winClass.hIconSm = NULL;
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground = NULL;
    winClass.lpszMenuName = NULL;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;

    if (!RegisterClassEx(&winClass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"), L"error", MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowEx(NULL,
        L"Direct2D", // window class name
        L"D2D1 Demo - Collison", // window caption
        WS_OVERLAPPEDWINDOW, // window style
        CW_USEDEFAULT, // initial x position
        CW_USEDEFAULT, // initial y position
        600, // initial x size
        600, // initial y size
        NULL, // parent window handle
        NULL, // window menu handle
        hInstance, // program instance handle
        NULL); // creation parameters

    if (!hwnd) return -1; 

    graphic = new Graphic();
    if (!graphic->init(hwnd)) {
        delete graphic;
        return -2;
    }

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    msg.message = WM_NULL;

    // ProgLoop - Logic here - Update/Render
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            DispatchMessage(&msg);
        }
        else {
            logic();  
        }
            
    }

    return 0;
}

