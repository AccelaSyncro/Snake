#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "WinBase.h"
#include "Game.h"
using namespace std;
constexpr const int cgheight = 30;
constexpr const int cgwidth = 80;
static unsigned char gameMap[cgheight * cgwidth] = { 0 };
static wchar_t charMap[10] = {0};
class Snake : public Game
{
private:
	int px;
	int py;
	int width;
	int height;
	int length;
	WinBase wb;
public:
	Snake();
	void freshScreen();
	void drawEdge();
	void drawBody();
	void goForward();
	void kbInput();
	void generateFood();
	virtual void startGame() override;
};

static vector<char> buffer(100);