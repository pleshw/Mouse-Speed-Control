#ifndef PLESHW_MOUSE_CONTROLLER
#define PLESHW_MOUSE_CONTROLLER

#include <iostream>
#include <memory>
#include <windows.h>
#include <winuser.h>
#pragma comment(lib, "user32.lib")



namespace pleshw
{
	std::unique_ptr<int> MouseSpeed(new int(0));

	namespace Palette
	{
		static  HBRUSH Purple   = CreateSolidBrush(RGB(48, 17, 52));
		static  HBRUSH Green    = CreateSolidBrush(RGB(44, 158, 51));
		static  HBRUSH Allow    = CreateSolidBrush(RGB(22, 188, 100));
		static  HBRUSH Deny     = CreateSolidBrush(RGB(155, 49, 49));
	}

	

	bool updateMouseSpeed(void)
	{
		return SystemParametersInfo(SPI_GETMOUSESPEED, 0, MouseSpeed.get(), 0);
	}

	// Increase mouse speed
	void increaseMouseSpeed(void)
	{
		if( *MouseSpeed <= 20 )
			//  Changing the mouse speed .
			SystemParametersInfo(
				SPI_SETMOUSESPEED,
				0,
				(LPVOID)((*MouseSpeed) + 1),
				SPIF_UPDATEINIFILE ||
				SPIF_SENDCHANGE ||
				SPIF_SENDWININICHANGE
			);
	}
	// Decrease mouse speed
	void decreaseMouseSpeed(void)
	{
		if (*MouseSpeed > 1)
			//  Changing the mouse speed .
			SystemParametersInfo(
				SPI_SETMOUSESPEED,
				0,
				(LPVOID)((*MouseSpeed) - 1),
				SPIF_UPDATEINIFILE ||
				SPIF_SENDCHANGE ||
				SPIF_SENDWININICHANGE
			);
	}

	// Get a window parameter if it's arrow up or down increase or decrease mouse speed.
	void ArrowHandler(WPARAM p)
	{
		updateMouseSpeed();
		wchar_t newMsg[82];
		switch (p)
		{
			case VK_UP:
				increaseMouseSpeed();
				updateMouseSpeed();
				break;
			case VK_DOWN:
				decreaseMouseSpeed();
				updateMouseSpeed();
				break;
		}
		swprintf_s(newMsg, L"\n ACTUAL MOUSE SPEED: %d \n", *MouseSpeed);
		OutputDebugString(newMsg);
	}

	void WheelHandler(WPARAM p)
	{
		updateMouseSpeed();
		wchar_t newMsg[82];

		// case up scroll
		if (GET_WHEEL_DELTA_WPARAM(p) > 0) increaseMouseSpeed();
		// case down scroll
		if (GET_WHEEL_DELTA_WPARAM(p) < 0) decreaseMouseSpeed();

		updateMouseSpeed();

		swprintf_s(newMsg, L"\n ACTUAL MOUSE SPEED: %d \n", *MouseSpeed);
		OutputDebugString(newMsg);


		
	}
}


#endif