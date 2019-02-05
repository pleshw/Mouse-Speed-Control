#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <winuser.h>
#include <string>
#include <sstream>
#include "pleshw.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void changeBackground(HWND hwnd, HBRUSH color);


HBRUSH bgColor = pleshw::Palette::Purple;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{


	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	
	// Setup window properties
	HWND appWindow = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Put the mouse on.",    // Window text
		(WS_SYSMENU),            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, 260, 10,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	// If the window could not be created.
	if (appWindow == NULL) return 0;
	
	// Trye register f10 hotkey
	BOOL openWindowHotkey = RegisterHotKey(
		appWindow,
		0,
		0,
		VK_F10
	);

	if (openWindowHotkey)
	{
		wchar_t newMsg[42];
		swprintf_s(newMsg, L"\n f10 registered as Open Hotkey. \n");
		OutputDebugString(newMsg);
	}

	ShowWindow(appWindow, SW_SHOWNORMAL);

	// Run the message loop.
	MSG msg = { };
	
	while (GetMessage(&msg, NULL, 0, 0))
	{	
		if (msg.message == WM_HOTKEY)
		{
			if (ShowWindow(appWindow, nCmdShow))
				ShowWindow(appWindow, SW_HIDE);
			else 
				ShowWindow(appWindow, SW_SHOWNORMAL);
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


// INPUT LOGIC GOES HERE. This callback handle the MSGs from the window.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;


		case WM_PAINT:
			changeBackground( hwnd, bgColor );
			return 0;

		case WM_KEYDOWN:
			pleshw::ArrowHandler(wParam);
			SetWindowTextA(
				hwnd,
				( "MouseSpeed: " + std::to_string(*pleshw::MouseSpeed)).c_str()
			);
			break;


		case WM_MOUSEWHEEL:
			pleshw::WheelHandler(wParam);
			SetWindowTextA(
				hwnd,
				("MouseSpeed: " + std::to_string(*pleshw::MouseSpeed)).c_str()
			);
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void changeBackground( HWND hwnd, HBRUSH color )
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	FillRect(hdc, &ps.rcPaint, color);
	EndPaint(hwnd, &ps);
}