#include<iostream>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<cstdlib>
#include<ctime>

using namespace std;

int a = (rand() % 10)+1;
int tailX[100], tailY[100];
int ntail=0;
bool gameover;
const int width = 20;
const int length = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { stop = 0,LEFT,RIGHT,UP,DOWN };
eDirection dir;

void setup()
{
	gameover = false;
	dir = stop;
	x = width;
	y = length / 2;
	fruitX = rand() % (2*width);
	fruitY = rand() % length;
	score = 0;
}

void draw()
{
	system("cls");
	for (int i = 0;i <= width+1;i++) cout << "# ";
	cout << endl;

	for (int i = 0;i <= length;i++)
	{
		for (int j = 0;j <= 2*width+1;j++)
		{
			if (j == 0 || j == 2*width+1) cout << "#";
			if (j == x && i == y) cout << "C";
			else if (j == fruitX && i == fruitY) cout << a;
			else
			{
				bool p = false;
				for (int k = 0;k < ntail;k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						p = true;
					}
				}
				if (!p) cout << " ";
			}


		}
		cout << endl;

	}

	for (int i = 0;i <= width + 1;i++)
	{
		if (i == width + 1) cout << "#";
		else cout << "# ";
	}
	cout << endl;
	cout << endl;
	cout << "SCORE\t:" << score << endl;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case's':
			dir = UP;
			break;
		case'w':
			dir = DOWN;
			break;
		case 'p':
			system("pause");
		}
	}
	if (x<0||y<0 ||x > 2 * width || y > length) gameover = true;
}

void logic()
{

	int prevx=tailX[0], prevy=tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2x, prev2y;
	for (int i = 1;i < ntail;i++)
	{
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevx;
		tailY[i] = prevy ;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y--;
		break;
	case UP:
		y++;
		break;
	}
	for (int i = 0;i < ntail;i++)
	{
		if (x == tailX[i] && y == tailY[i]) gameover = true;
	}

	if (x == fruitX && y == fruitY) {
		score += a;
		ntail += 1;
		fruitX = rand() % (2 * width);
		fruitY = rand() % length;

		srand(time(0));
		a = (rand() % 10)+1;
	}


}

int main()
{
	setup();
	while (!gameover)
	{

	if(score<30)
        system("color 34");
    else if(score<60)
        system("color 56");
    else system("color 67");
		draw();
		input();
		logic();
		Sleep(0);
	}
	system("cls");
	cout << "SCORE\t:" << score << endl;
}
