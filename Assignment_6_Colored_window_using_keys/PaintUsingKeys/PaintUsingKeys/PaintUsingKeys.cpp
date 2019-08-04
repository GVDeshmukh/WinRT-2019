//Author : Gaurav Deshmukh (Win32 - 2019)

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
	RECT rc;
	PAINTSTRUCT ps;
	static int paintFlag = 0; // flag to decide the color to be displayed on window.
	HBRUSH hBrush;

	switch (iMsg)
	{
		//Manadatory case WM_DESTROY - necessory to close the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//Case to identify the character key pressed
	case WM_CHAR:
		switch (wParam) {
			//Blue
		case 'B'://0x42
		case 'b'://0x62
			paintFlag = 1; //Update flag value
			GetClientRect(hwnd, &rc); //Get client area's changing rectangle
			InvalidateRect(hwnd, &rc, TRUE); //Call paint event
			break;
			//Red
		case 'R'://0x52
		case 'r'://0x72
			paintFlag = 2;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			//Green
			break;
		case 'G'://0x47
		case 'g'://0x67
			paintFlag = 3;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			//Black
		case 'K'://0x4B
		case 'k'://0x6B
			paintFlag = 4;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			//Cyan
		case 'C'://0x43
		case 'c'://0x63
			paintFlag = 5;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			//Magenta
		case 'M'://0x4D
		case 'm'://0x6D
			paintFlag = 6;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			//Yellow
		case 'Y'://0x59
		case 'y'://0x79
			paintFlag = 7;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			//White
		case 'W'://0x57
		case 'w'://0x77
			paintFlag = 8;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			//Orange
			break;
		case 'O'://0x4F
		case 'o'://0x6F
			paintFlag = 9;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
			// Default is Black
		default:
			paintFlag = 4;
			GetClientRect(hwnd, &rc);
			InvalidateRect(hwnd, &rc, TRUE);
			break;
		}
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
		case 4: //Black
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		case 5: //Cyan
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 6: //Magenta
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 7: //Yellow
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 8: //White
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		case 9: //Orange
			hBrush = CreateSolidBrush(RGB(255, 128, 0));
			break;
		default: //Default is Black
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		}
		//Get client area's changing rectangle
		GetClientRect(hwnd, &rc);
		//call the specialist
		hdc = BeginPaint(hwnd, &ps);
		//Select object
		SelectObject(hdc, hBrush);
		//Fill client rect area
		FillRect(hdc, &rc, hBrush);
		//Delete brush
		DeleteObject(hBrush);
		//Sent back the specialist
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}