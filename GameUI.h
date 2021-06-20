#ifndef GAME_MAZE
#define GAME_MAZE

#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <conio.h>
#include <time.h>

#define start_x 12
#define start_y 10

#define m_width 28
#define m_height 10


using namespace std;
/*
#define WIDTH 187
#define HEIGHT 50
*/

void gotoxy(int x, int y)
{ // Allows to move inside the terminal using coordinates
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x; // Starts from 0
    dwPos.Y = y; // Starts from 0
    SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor()
{ // Hides the cursor :3
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y)
{ // To clean a certain space in the terminal
    for (int i = a_x; i < b_x; i++)
    {
        for (int j = a_y; j < b_y; j++)
        {
            gotoxy(i, j); cout << " ";
        }
    }
}

void Filled( const char* ch, int a_x, int a_y, int b_x, int b_y) {
    for (int i = a_x; i < b_x; i++) {
        for(int j = a_y; j < b_y; j++) {
            gotoxy(i, j); cout << ch;
        }
    }
}

void DrawWindowFrame(int a_x, int a_y, int b_x, int b_y)
{ // This will draw a rectangular frame defined by two points
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    DrawWhiteSpace(a_x + 1, a_y + 1, b_x, b_y);
    for (int i = a_x + 1; i < b_x; i++)
    {
        gotoxy(i, a_y); cout << "ùù";
        gotoxy(i, b_y); cout << "ùù";
    }
    for (int i = a_y + 1; i < b_y; i++)
    {
        gotoxy(a_x, i); cout << "ùø";
        gotoxy(b_x, i); cout << "ùø";
    }
    gotoxy(a_x, a_y); cout << "ùÝ";
    gotoxy(b_x, a_y); cout << "ùß";
    gotoxy(a_x, b_y); cout << "ùã";
    gotoxy(b_x, b_y); cout << "ùå";
}
void DrawGameLimits(int x, int y)
{ // Draws the game limits, and information that doesn't have to be printed repeatedly
    DrawWindowFrame(0, 0, x, y); // The default size of the Windows terminal is 25 rows x 80 columns
    //gotoxy( 2,1); printf("HP:");
    //gotoxy(16,1); printf("ENERGY:");
    //gotoxy(50,1); printf("SCORE:");
}

void Intro(int x, int y) {
    x = 28, y = 35;
    int _x = 56;
    x = x / 2,5;
    y = y / 2.5;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(x, y++); cout << "¢i¢i¢i¢i¢i¢i¢i     " << " ¢i¢i¢i¢i¢i¢i       " << " ¢i¢i¢i¢i¢i¢i       " << " ¢i¢i¢i¢i¢i¢i¢i      " << " ¢i¢i¢i¢i¢i¢i¢i      " << "¢i¢i¢i¢i¢i¢i¢i" << endl;
    gotoxy(x, y++); cout << "¢i¢i          " << "¢i¢i     ¢i      " << "¢i¢i     ¢i      " << "¢i¢i     ¢i¢i     " << "¢i¢i     ¢i¢i     " << "¢i¢i     " << endl;
    gotoxy(x, y++); cout << "¢i¢i          " << "¢i¢i            " << "¢i¢i            " << "¢i¢i¢i¢i¢i¢i¢i¢i¢i     " << "¢i¢i¢i¢i¢i¢i¢i¢i      " << "¢i¢i     " << endl;
    gotoxy(x, y++); cout << "¢i¢i¢i¢i¢i       " << " ¢i¢i¢i¢i¢i¢i¢i      " << "¢i¢i            " << "¢i¢i     ¢i¢i     " << "¢i¢i            " << "¢i¢i¢i¢i¢i  " << endl;
    gotoxy(x, y++); cout << "¢i¢i          " << "       ¢i¢i     " << "¢i¢i            " << "¢i¢i     ¢i¢i     " << "¢i¢i            " << "¢i¢i     " << endl;
    gotoxy(x, y++); cout << "¢i¢i          " << " ¢i     ¢i¢i     " << "¢i¢i     ¢i      " << "¢i¢i     ¢i¢i     " << "¢i¢i            " << "¢i¢i     " << endl;
    gotoxy(x, y++); cout << "¢i¢i¢i¢i¢i¢i¢i     " << "  ¢i¢i¢i¢i¢i¢i      " << " ¢i¢i¢i¢i¢i¢i       " << "¢i¢i     ¢i¢i     " << "¢i¢i            " << "¢i¢i¢i¢i¢i¢i¢i" << endl;

    y += 5;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(_x / 2, y++); cout << "P r o d u c e    b y    Y u u  -  2 0 2 1";
    y++;
    gotoxy(_x / 2 + 12, y);


    while (true) {
        cout << "Press Enter to start!";

        for (int i = 0; i < 50000; i++) {
            if (_kbhit())
                if (cin.ignore())
                    return;
        }//sleep
        for (int i = 0; i < 21; i++) {
            cout << "\b";
            cout << " ";
            cout << "\b";
        }
        for (int i = 0; i < 50000; i++) {
            if (_kbhit())
                if (cin.ignore()) {
                    return;
                }
        }//sleep
    }
}



#endif
