#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	TCHAR szAppName[] = TEXT("MyApp");
	HWND hwnd;
	MSG msg;

	MessageBox(nullptr, TEXT("Inside WinMain"), TEXT("Message"), MB_OK | MB_ICONEXCLAMATION);

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
	switch (iMsg)
	{
		TCHAR str[30];

	case WM_CREATE:
		wsprintf(str, TEXT("Create Called"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK | MB_ICONEXCLAMATION);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_RETURN:
			MessageBox(hwnd, TEXT("Enter Pressed"), TEXT("Message"), MB_OK | MB_ICONEXCLAMATION);
			break;
		}
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}