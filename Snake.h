#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;
class Snake
{
private:
	int px;
	int py;
	int width;
	int height;
	int length;
public:
	Snake();
	void freshScreen();
	void kbInput();
	void startGame();
};

static vector<char> buffer(100);