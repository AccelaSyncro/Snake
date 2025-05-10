#include "WinBase.h"
#include <iostream>
#include "Game.h"

WinBase::WinBase(const size_t& gameWidth, const size_t& gameHeight, const size_t& screenWidth,const size_t& screenHeight)
	:gameWidth(gameWidth),gameHeight(gameHeight),screenWidth(screenWidth),screenHeight(screenHeight)
{
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//DWORD mode = 0;
	//GetConsoleMode(hOut, &mode);
	//SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	//this->gameMap =  new unsigned char[gameWidth * gameHeight];
	this->screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';
	this->hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo); // ��ȡ��ǰ�������
	cursorInfo.bVisible = FALSE;                // ���ع��
	SetConsoleCursorInfo(hConsole, &cursorInfo); // Ӧ������
}

WinBase::~WinBase()
{
	delete this->screen;
}


void WinBase::display(const unsigned char* gameMap, const wchar_t* charMap) {
	//int screenWidth = 100, screenHeight = 100;
	// 4. ���ÿ���̨���ڴ�С
	
	//COORD bufferSize = { (SHORT)(screenWidth), (SHORT)(screenHeigth) };
	//SetConsoleScreenBufferSize(hConsole, bufferSize);

	//SMALL_RECT windowSize = { 0, 0, (SHORT)screenWidth - 1, (SHORT)screenHeigth - 1 };
	//SetConsoleWindowInfo(hConsole, TRUE, &windowSize);


	 //5. ��Ⱦ��Ϸ��ͼ����Ļ������
	for (int x = 0; x < gameWidth; x++) {
		for (int y = 0; y < gameHeight; y++) {
			screen[x + y * screenWidth] = charMap[gameMap[x + y * gameWidth]];
			//screen[x + y * screenWidth]= (gameMap[x + y * gameWidth] == 9) ? L'#' : L' ';
		}
	}
	DWORD dwBytesWritten = 0;
	//WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	// 6. ���������̨
	for (int y = 0; y < gameHeight; y++) {
		WriteConsoleOutputCharacterW(
			hConsole,
			&screen[y * screenWidth],
			gameWidth,
			{ 0, (SHORT)y },
			&dwBytesWritten);
	}
}
void WinBase::clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return;

	// ��ȡ����̨��������Ϣ
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// ������Ҫ�����ַ���
	DWORD bufferSize = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD charsWritten;

	// �ÿ��ַ��ո����������Ļ
	COORD home = { 0, 0 };
	FillConsoleOutputCharacterW(
		hConsole,      // ����̨���
		L' ',          // ���ַ��ո�
		bufferSize,    // �������
		home,          // ��ʼλ��
		&charsWritten  // ʵ����������ɺ��ԣ�
	);

	// ���ù�굽���Ͻ�
	SetConsoleCursorPosition(hConsole, home);

}
