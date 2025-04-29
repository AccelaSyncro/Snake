#include "Snake.h"
enum element {
	EMPTY=0,BODY=1,WALL=9
};
void Snake::startGame()
{
	charMap[EMPTY] = L' ';
	charMap[BODY] = L'o';
	charMap[WALL] = L'#';
	constexpr int FPS = 15;
	this->width = cgwidth;
	this->height = cgheight;
	drawEdge();
	const auto frameDuration = std::chrono::milliseconds(1000 / FPS);
	while (!gameOver) {
		auto frameStart = std::chrono::steady_clock::now();
		freshScreen();      // 优化后的刷新函数
		kbInput();
		auto frameEnd = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
		if (elapsed < frameDuration) {
			
			std::this_thread::sleep_for(frameDuration - elapsed);  // 保持稳定帧率
		}
	}
}
Snake::Snake()
{
	gameOver = false;
	this->wb=WinBase();
	width = cgwidth;
	height = cgheight;
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
	for (int i = 0; i <= length; i++) {
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
	gameMap[py * width + px] = EMPTY;      //画面上删除尾部

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
	buffer.erase(buffer.begin() + 1);             //蛇身上删除尾部
}

void Snake::kbInput()
{
	if (_kbhit()) {
		char ch = _getch();
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			buffer.push_back(ch);
			goForward();
		}
	}
	else {
		buffer.push_back(buffer[length]);
		goForward();
	}
}


