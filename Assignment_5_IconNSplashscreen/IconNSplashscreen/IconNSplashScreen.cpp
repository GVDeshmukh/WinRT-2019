#include <Windows.h>
#include "Splash.h"

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
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = nullptr;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

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
	HDC hdc1, hdc2;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP structBitMap;

	switch (iMsg)
	{
	case WM_CREATE:
		static HBITMAP hBitMap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(MYBITMAP));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Call Specialist
		hdc1 = BeginPaint(hwnd, &ps);
		//Get client rectangle area
		GetClientRect(hwnd, &rc);
		//Create memory device context
		hdc2 = CreateCompatibleDC(nullptr);

		SelectObject(hdc2, hBitMap);

		GetObject(hBitMap, sizeof(BITMAP), &structBitMap);

		StretchBlt(hdc1, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hdc2, 0, 0, structBitMap.bmWidth, structBitMap.bmHeight, SRCCOPY);
	
		DeleteObject(hdc2);

		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}