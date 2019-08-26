#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD CALLBACK ThreadProcOne(LPVOID);

DWORD CALLBACK ThreadProcTwo(LPVOID);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
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
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	switch (iMsg)
	{	
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, hwnd, 0, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Clicked"), TEXT("Notice"), MB_OK);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD CALLBACK ThreadProcOne(LPVOID lParam)
{
	HDC hdc;
	TCHAR str[255];
	unsigned long int i;
	
	//Get device context
	hdc = GetDC((HWND)lParam);
	// Display counter increase
	for (i = 0; i < 4294967295; ++i)
	{
		wsprintf(str, TEXT("Thread One -> Increasing Order : %lu"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	//Rlease 
	ReleaseDC((HWND)lParam, hdc);
	return 0;
}

DWORD CALLBACK ThreadProcTwo(LPVOID lParam)
{
	HDC hdc;
	TCHAR str[255];
	unsigned long int i;

	//Get device context
	hdc = GetDC((HWND)lParam);
	// Display counter increase
	for (i = 4294967295; i > 0; --i)
	{
		wsprintf(str, TEXT("Thread Two -> Decreasing Order : %lu"), i);
		TextOut(hdc, 5, 30, str, wcslen(str));
	}
	//Rlease 
	ReleaseDC((HWND)lParam, hdc);
	return 0;
}