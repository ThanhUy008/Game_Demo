#include "Buffer.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
const int dai = 20;
const int rong = 20;
int score,Ax,Ay,xspace,yspace;
bool gameOver;
enum Direction {STOP = 0,LEFT, RIGHT};
Direction Ctrl;
void hidemouse()
{
	HANDLE hmouse = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO contro;
	contro.dwSize = 1; contro.bVisible = 0;
	SetConsoleCursorInfo(hmouse,&contro);
}
void Setup()
{
	ScreenBuffer::SetupBufferScreen(dai,rong);
	gameOver = false ;
	score = 0;
	Ax = 15;
	Ay = 15;
	yspace = 1;
	xspace = 3;
}
void Drawkhung()
{
	for(int y = 0 ; y < dai ; y++)
	{
		for(int x = 0 ; x < rong ; x++)
		{
			if(x==0 || x == rong - 1 || y == 0 || y == dai - 1) ScreenBuffer::drawToBuffer(x,y,'#');
			else if(x == Ax && y == Ay) ScreenBuffer::drawToBuffer(x,y,'F');
			else ScreenBuffer::drawToBuffer(x,y,' ');
		}

	}
}
void Drawline()
{
	for(int y = 0 ; y < dai - 1 ; y++)
	{
		for(int x = 1 ; x < rong - 1 ; x++)
		{
			if(y == yspace)
			{
				if(x >= xspace && x < xspace + 4)
				{
					ScreenBuffer::drawToBuffer(x,y,' ');
				}
			else ScreenBuffer::drawToBuffer(x,y,'*');
			if(x == Ax && y == Ay) ScreenBuffer::drawToBuffer(x,y,'F');
			}
		}
	}

}
void Control()
{
	if(_kbhit())
	{ switch(_getch())
	  {
	     case 'a' : Ctrl = LEFT; break;
	     case 'd' : Ctrl = RIGHT; break;
	     case 'r'  : Ctrl = STOP; break;
	  }
	}
}
void Logic()
{ 
	switch(Ctrl)
	{
	case LEFT : xspace--;
	if(xspace < 1) 
				{
					xspace = rong - 2;
				}
				if(xspace > rong - 1)
				{
					xspace = 1;
				}
				
				break;
 
	case RIGHT :xspace++;
	if(xspace < 1) 
				{
					xspace = rong - 2;
				}
				if(xspace > rong - 1)
				{
					xspace = 1;
				}
				break;
	} 
	yspace++;
	if(yspace > dai) 
	{
		yspace = 1;
	}

    if(yspace == Ay )
	{
		if(Ax >=xspace && Ax < xspace +4 ) score += 10;
		else gameOver = true;
		/* int flag = score; 
		for(int x = 1 ; x < rong - 1 ; x++)
		{
			if(ScreenBuffer::check(x,yspace,' ')) score += 10;
			else gameOver = true;
		}
				if(x >= xspace && x < xspace + 4)
				{
					 
					if(x == Ax) 
						{
							score += 10;
					}
				}
		}
		if(score == flag) gameOver = true;
	} */

}
}
void Draw()
{
	Drawkhung();
	Drawline();
	ScreenBuffer::drawToBuffer(1,1,score + 48);
	ScreenBuffer::drawToConsole();
}
void main()
{
	Setup();
	Draw();
	hidemouse();
	while(!gameOver)
	{
		Control();
		Logic();
		Draw();
		Sleep(100);
	}
	ScreenBuffer::deposeBuffer();
}
