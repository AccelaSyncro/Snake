#include "Snake.h"
#include <thread>
enum element {
	EMPTY=0,BODY=1,FOOD=2,WALL=9
};
void Snake::startGame()
{
	charMap[EMPTY] = L'\u3000';
	charMap[BODY] = L'蛇';
	charMap[WALL] = L'墙';
	charMap[FOOD] = L'果';
	//charMap[EMPTY] = L' ';
	//charMap[BODY] = L'o';
	//charMap[WALL] = L'#';
	//charMap[FOOD] = L'x';
	constexpr int FPS = 15;
	drawEdge();
	generateFood();
	const auto frameDuration = std::chrono::milliseconds(2000 / FPS);
	while (!gameOver) {
		auto frameStart = std::chrono::steady_clock::now();
		freshScreen();
		kbInput();
		auto frameEnd = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
		if (elapsed < frameDuration) {
			std::this_thread::sleep_for(frameDuration - elapsed);  // 保持稳定帧率
		}
		if (gameOver) return;
	}
}
Snake::Snake()
{
	srand(time(NULL));
	gameOver = false;
	width = cgwidth;
	height = cgheight;
	this->wb = WinBase(width, height);
	px = width / 2;
	py = height / 2;
	length = 2;
	buffer.clear();
	buffer.push_back(' ');
	for (int i = 0; i < length; i++) {
		buffer.push_back('d');
	}
}
void Snake::freshScreen() {
	drawBody();
	wb.display(gameMap, charMap);
}
void Snake::drawEdge()
{
	for (int x = 0; x <width ; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || x == width - 1|| y == 0 || y ==height - 1) {
				gameMap[x + y * width] = 9;
			}
			else
			{
				gameMap[x + y * width] = 0;
			}
		}
	}
}

void Snake::drawBody()
{
	int vx = px, vy = py;
	for (int i = 1; i <= length; i++) {
		if (vy == 0 || vx == 0 || vy == height-1 || vx == width-1) {
			gameOver = true; 
			return;
		}
		if (gameMap[vy * width + vx] == FOOD) {
			buffer.push_back(buffer[length++]);
			generateFood();
		}
		switch (buffer[i])
		{
		case 'w':
			gameMap[vy-- * width + vx] = BODY;
			break;
		case 'a':
			gameMap[vy* width + vx--] = BODY;
			break;
		case 's':
			gameMap[vy++ * width + vx] = BODY;
			break;
		case 'd':
			gameMap[vy * width + vx++] = BODY;
			break;
		default:
			break;
		}
	}
}

void Snake::goForward()
{
	gameMap[py * width + px] = EMPTY;      //屏幕上删除尾部
	//尾部路径追踪
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
	buffer.erase(buffer.begin()+1);             //蛇身上删除尾部
}

void Snake::kbInput()
{
	if (gameOver) return;
	if (_kbhit()) {
		char ch = _getch();
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			buffer.push_back(ch);
			goForward();
		}else {
			buffer.push_back(buffer[length]);
			goForward();
		}
	}else {
		buffer.push_back(buffer[length]);
		goForward();
	}
}

void Snake::generateFood()
{
	int ry = rand() % (height-1) + 1;
	ry == height - 1 ? ry - 1 : ry;
	int rx = rand() % (width - 1) + 1;
	rx == width - 1 ? rx - 1 : rx;
	gameMap[ry * width + rx] = FOOD;
}


