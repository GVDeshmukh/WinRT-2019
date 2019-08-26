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
	TCHAR str1[150] = TEXT("India is my country and all Indians are my brothers and sisters. I love my country and I am proud of its rich and varied heritage.");
	TCHAR str2[150] = TEXT("I shall always strive to be worthy of it. I shall give respect to my parents, teachers and all elders and treat everyone with courtesy");
	TCHAR str3[225] = TEXT("To my country and my people, I pledge my devotion. In their well being and prosperity alone lies my happiness.");

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Get client area changing rectangle
		GetClientRect(hwnd, &rc);  //not required
		//call the specialist
		hdc = BeginPaint(hwnd, &ps);
		//Set text background color
		SetBkColor(hdc, RGB(0, 0, 0)); //Black
		//Set text color
		SetTextColor(hdc, RGB(255, 128, 0)); //orange
		//draw text in regula way
		TextOut(hdc, ((rc.right - rc.left) / 2), ((rc.bottom - rc.top) / 2), str1, wcsnlen(str1, 149));
		SetTextColor(hdc, RGB(255, 255, 255)); //white
		//draw text in regula way
		TextOut(hdc, ((rc.right - rc.left)/2), ((rc.bottom - rc.top) / 2) + 20, str2, wcsnlen(str2, 149));
		SetTextColor(hdc, RGB(0, 255, 0)); //green
		//draw text in regula way
		TextOut(hdc, ((rc.right - rc.left) / 2), ((rc.bottom - rc.top) / 2) + 40, str3, wcsnlen(str3, 224));
		//Sent back the specialist
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}