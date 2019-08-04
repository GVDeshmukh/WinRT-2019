//Author : Gaurav Deshmukh (Win32 - 2019)

#include <Windows.h>

#define PAINTTIMER 1000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	TCHAR szAppName[] = TEXT("MyApp");
	HWND hwnd;
	MSG msg;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = nullptr;
	wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	//registration of class
	RegisterClassEx(&wndClass);

	//Create window
	hwnd = CreateWindow(szAppName, TEXT("My Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

	//Show window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	RECT rc;
	static RECT tempRc;
	PAINTSTRUCT ps;
	static int paintFlag = 0; // flag to decide the color to be displayed on window.
	HBRUSH hBrush;
	static LONG widthFactor;

	switch (iMsg)
	{
	case WM_CREATE:
		//Set timer in wm_create , which is very first call to timer.
		SetTimer(hwnd, PAINTTIMER, 500, NULL);
		//Increment flag
		paintFlag++;
		break;
		//Manadatory case WM_DESTROY - necessory to close the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//Timer event which is triggered when timer is set to trigger after some interval of time.
	case WM_TIMER:
		//kill timer first, as the timer keeps on counting during WM_TIMER body execution.
		KillTimer(hwnd, NULL);
		//Reset the flag value
		if (9 == paintFlag)
		{
			paintFlag -= paintFlag;
			tempRc.left = 0;
			tempRc.right = 0;
			//Call paint event
			InvalidateRect(hwnd, &rc, TRUE);
		}
		//Increment flag
		paintFlag++;
		//Get client area's changing rectangle
		GetClientRect(hwnd, &rc);
		//Call paint event
		InvalidateRect(hwnd, &rc, FALSE);
		//Set new timer
		SetTimer(hwnd, PAINTTIMER, 500, NULL);
		break;
	case WM_PAINT:
		switch (paintFlag) {
		case 1: //Blue
				//Create brush
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		case 2: //Red
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 3: //Green
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 4: //Cyan
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 5: //Magenta
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 6: //Yellow
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 7: //White
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		case 8: //Orange
			hBrush = CreateSolidBrush(RGB(255, 128, 0));
			break;
		default: //Default is Black
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		}
		//Get client area's changing rectangle
		GetClientRect(hwnd, &rc);
		//adjust the rect width
		widthFactor = (rc.right - rc.left) / 8;

		tempRc.left = tempRc.right;
		tempRc.right = tempRc.right + widthFactor;
		tempRc.top = rc.top;
		tempRc.bottom = rc.bottom;

		//call the specialist
		hdc = BeginPaint(hwnd, &ps);
		//Select object
		SelectObject(hdc, hBrush);
		//Fill client rect area
		FillRect(hdc, &tempRc, hBrush);
		//Delete brush
		DeleteObject(hBrush);
		//Sent back the specialist
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}