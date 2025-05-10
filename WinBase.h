#pragma once
#include <windows.h>
#include <cwchar>
class WinBase
{
private:
	//unsigned char* gameMap;
	size_t gameWidth;
	size_t gameHeight;
	wchar_t* screen;
	size_t screenWidth;
	size_t screenHeight;
	HANDLE  hConsole;//µ±Ç°¾ä±ú
public:
	WinBase(const size_t& gameWidth = 80, const size_t& gameHeight = 30, const size_t& screenWidth = 100, const size_t& screenHeight = 100);
	~WinBase();
	void clearScreen();
	void display(const unsigned char* gameMap,const wchar_t*charMap);
};

