#include "Snake.h"

Snake::Snake()
{
	width = 80;
	height = 20;
	px = width / 2;
	py = height / 2;
	length = 2;
	buffer.clear();
	buffer.push_back(' ');
	for (int i = 0; i < length; i++) {
		buffer.push_back('d');
	}
}

void Snake::freshScreen()
{
	system("cls");
	drawBody();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%c", gameSpace[i][j]);
		}
		printf("\n");
	}
}

void Snake::drawEdge()
{
	for (int i = 0; i < width; i++) {
		gameSpace[0][i] = '*';
		gameSpace[height - 1][i] = '*';
	}
	for (int j = 0; j < height; j++) {
		gameSpace[j][0] = '*';
		gameSpace[j][width - 1] = '*';
	}
}

void Snake::drawBody()
{
	int vx = px, vy = py;
	for (int i = 0; i <= length; i++) {
		switch (buffer[i])
		{
		case ' ':
			break;
		case 'w':
			gameSpace[vy--][vx] = 'o';
			break;
		case 'a':
			gameSpace[vy][vx--] = 'o';
			break;
		case 's':
			gameSpace[vy++][vx] = 'o';
			break;
		case 'd':
			gameSpace[vy][vx++] = 'o';
			break;
		default:
			break;
		}
	}
}

void Snake::goForward()
{
	gameSpace[py][px] = ' ';
	switch (buffer[1])
	{
	case 'w':
		--py;
		break;
	case 'a':
		--px;
		break;
	case 's':
		++py;
		break;
	case 'd':
		++px;
		break;
	default:
		break;
	}
	buffer.erase(buffer.begin() + 1);
}

void Snake::kbInput()
{
	if (_kbhit()) {
		char ch = _getch();
		buffer.push_back(ch);
		goForward();
	}
	else {
		buffer.push_back(buffer[length]);
		goForward();
	}
}

void Snake::startGame()
{
	drawEdge();
	while (true) {
		freshScreen();
		kbInput();
		Sleep(200);
	}
}
