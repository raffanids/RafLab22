#include <windows.h>
#include <string>
#include <sstream>
#include <cfloat>
#include <stdio.h> 

using namespace std;

HWND hwndNum1, hwndNum2, hwndAdd, hwndSub, hwndMul, hwndDiv;

double PerformCalculation(double num1, double num2, char operation) {
    switch(operation) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if(num2 != 0)
                return num1 / num2;
            else
                return 0; 
        default:
            return 0; 
    }
}

void ShowResult(double result) {
    ostringstream oss; 
    if(result != DBL_MAX)
        oss << "Result: " << result;
    else
        oss << "Error: Division by zero";

    char buffer[100];
    sprintf(buffer, "%.4f", result);
    string resultStr = buffer;

    MessageBox(NULL, resultStr.c_str(), "Result", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            char buffer[100];
            CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE, 10, 10, 200, 25, hwnd, NULL, NULL, NULL);
            hwndNum1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 40, 100, 25, hwnd, NULL, NULL, NULL);
			hwndNum2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 100, 100, 25, hwnd, NULL, NULL, NULL);
            hwndAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | WS_BORDER, 65, 70, 50, 25, hwnd, NULL, NULL, NULL);
			hwndSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | WS_BORDER, 125, 70, 50, 25, hwnd, NULL, NULL, NULL);
			hwndMul = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | WS_BORDER, 65, 130, 50, 25, hwnd, NULL, NULL, NULL);
			hwndDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | WS_BORDER, 125, 130, 50, 25, hwnd, NULL, NULL, NULL);


            HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
            SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
            break;
        }
        case WM_COMMAND: {
            if((HWND)lParam == hwndAdd || (HWND)lParam == hwndSub || (HWND)lParam == hwndMul || (HWND)lParam == hwndDiv) {
                double num1, num2;
                char operation;
                string strNum1, strNum2;

                int len = GetWindowTextLength(hwndNum1) + 1;
                char* buffer = new char[len];
                GetWindowText(hwndNum1, buffer, len);
                strNum1 = buffer;
                delete[] buffer;

                len = GetWindowTextLength(hwndNum2) + 1;
                buffer = new char[len];
                GetWindowText(hwndNum2, buffer, len);
                strNum2 = buffer;
                delete[] buffer;

                istringstream(strNum1) >> num1;
                istringstream(strNum2) >> num2;

                if((HWND)lParam == hwndAdd)
                    operation = '+';
                else if((HWND)lParam == hwndSub)
                    operation = '-';
                else if((HWND)lParam == hwndMul)
                    operation = '*';
                else if((HWND)lParam == hwndDiv)
                    operation = '/';

                double result = PerformCalculation(num1, num2, operation);
                ShowResult(result);
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize         = sizeof(WNDCLASSEX);
    wc.lpfnWndProc    = WndProc;
    wc.hInstance      = hInstance;
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName  = "WindowClass";
    wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
    CW_USEDEFAULT, 
    CW_USEDEFAULT, 
    250, 
    200, 
    NULL, NULL, hInstance, NULL);


    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
return msg.wParam;
}