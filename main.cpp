#include "Maze.h"
#include "GameUI.h"
#include <iostream>
#include <chrono>
#include "resizing.h"



using namespace std;
#define screen_WIDTH 98
#define screen_HEIGHT 40

bool meetWall(Maze m, int x ,int y) {
	//gotoxy(start_x + m_width*2 + 10, start_y+4); cout << m.getMaze(x, y);
	if(x >= start_x && y <= start_y + m_height*2 ) {
		if(m.getMaze(x, y) == '#')
			return true;
		else return false;
	}
	return false;
}

void show_coord(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(start_x + m_width*2 + 10, start_y+1);
	cout << "POSITION:" << "(" << x << ", " << y << ")";
}
void ShowTime(int total_t) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "TIME:";
	cout << (total_t/60)/10 << (total_t/60)%10 <<"'";
	cout << (total_t%60)/10<< (total_t%60)%10 <<"\"";
}

void ShowScore(int score) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

	cout << "SCORE";
	cout << ":" << score;

}



int main() {


	//system("color 04");
	//FULL SCREEN
	//system("mode con COLS=700");
	//ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	SetConsoleWindowSize(screen_WIDTH + 2, screen_HEIGHT+1);
	//goxy(188, 51);//maximun size of cmd
	HideCursor();

	Intro:
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	DrawWindowFrame(0, 0, screen_WIDTH, screen_HEIGHT);
	Intro((screen_WIDTH - 2) / 2, (screen_HEIGHT+9) / 2);
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	DrawGameLimits(screen_WIDTH, screen_HEIGHT);
    Maze m;
	m.DrawMaze();
	//gotoxy(start_x + m_width*2 + 10, start_y+3); cout << m.getMaze(start_x, start_y+m_height*2);
	gotoxy(start_x-6, start_y + m_height*2 - 1);
	cout << "-START";
	string player = "@";
	int posX = start_x-8, posY = start_y + m_height*2 - 1;
	gotoxy(posX, posY); cout << player;

	clock_t start_t, end_t;
	int score = 0, TOTAL = 0;
	gotoxy(start_x + m_width*2 + 10, start_y+3);
	ShowScore(score);


	// game loop
	start_t = clock();
	end_t = clock();

	while (1) {
		start:
		TOTAL = (end_t - start_t) / CLOCKS_PER_SEC;
		gotoxy(start_x + m_width*2 + 10, start_y+2);
		ShowTime(TOTAL);

		show_coord(posX, posY);
		gotoxy(start_x + m_width*2 + 10, start_y+3);
		ShowScore(score);


		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if(meetWall(m, posX-1, posY))
				goto start;
				else if(posX >= start_x && posY <= start_y+m_height*2-1) {
					if(m.getMaze(posX-1, posY) == '*'){
						m.ajusted(' ' ,posX-1, posY);
						++score;
					}
				}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(posX, posY); cout << "*";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(--posX, posY); cout << player;
			Sleep(100);

		}
		if (GetAsyncKeyState(VK_RIGHT) & 0X8000) {
			if(meetWall(m, posX+1, posY))
				goto start;
			else if(posX >= start_x && posY <= start_y+m_height*2-1) {
				if(m.getMaze(posX+1, posY) == '*'){
					m.ajusted(' ' ,posX+1, posY);
					++score;
				}
			}


			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(posX, posY); cout << "*";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(++posX, posY); cout << player;
			Sleep(100);

		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if(meetWall(m, posX, posY-1))
				goto start;
				else if(posX >= start_x && posY <= start_y+m_height*2-1) {
					if(m.getMaze(posX, posY-1) == '*'){
						m.ajusted(' ' ,posX, posY-1);
						++score;
					}
				}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(posX, posY); cout << "*";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(posX, --posY); cout << player;
			Sleep(100);

		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if(meetWall(m, posX, posY+1))
				goto start;
				else if(posX >= start_x && posY <= start_y+m_height*2-1) {
					if(m.getMaze(posX, posY+1) == '*'){
						m.ajusted(' ' ,posX, posY+1);
						++score;
					}
				}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(posX, posY); cout << "*";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(posX, ++posY); cout << player;
			Sleep(100);

		}
		end_t = clock();
		if(posX == start_x+m_width*2 && posY == start_y+1)
			break;
	}


	system("cls");

	DrawWindowFrame(screen_WIDTH/4, screen_HEIGHT/4+6, screen_WIDTH/4+50, screen_HEIGHT/4+15);

	gotoxy(screen_WIDTH/2-5, screen_HEIGHT/2); ShowScore(score);
	gotoxy(screen_WIDTH/2-5, screen_HEIGHT/2+1); ShowTime(TOTAL);

	while(1) {
		if (_kbhit()) {
			if(cin.ignore())
				goto Intro;
		}
	}





	return 0;
}
