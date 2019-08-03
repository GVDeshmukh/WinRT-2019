#include <Windows.h>

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
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[40] = TEXT("Hello World!!!");

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Get client area changing rectangle
		GetClientRect(hwnd, &rc);
		//call the specialist
		hdc = BeginPaint(hwnd, &ps);
		//Set text color
		SetTextColor(hdc, RGB(0, 255, 0));
		//Set text background color
		SetBkColor(hdc,RGB(0, 0, 0)); //Black
		//Draw the actual text
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//Sent back the specialist
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}