#include <iostream>
#include <windows.h>
#include <time.h>
#include <memory.h>
#include "GameUI.h"
using namespace std;
/*
#define start_x 38
#define start_y 9

#define m_width 56
#define m_height 10
*/
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

class Maze{
private:

    char m_maze[200][200];
    int visited[200][200];
    void dfs(int x, int y, int px, int py) {
        if(x < 0 || y < 0 || x >= m_width || y >= m_height)
            return;
        if(visited[x][y])
            return;
        visited[x][y] = 1;
        if(px >= 0) {
            m_maze[((x*2+1)+(px*2+1))/2][((y*2+1)+(py*2+1))/2] = '*';
        }
        m_maze[x*2+1][y*2+1] = '*';
        if(x == m_width-1 && y == m_height-1)
            return;

        int dir = 0, _time = 0;
        bool flag[4] = {1, 1, 1, 1};
        while(_time < 4) {
            dir = rand()%4;

            dir = rand()% 4;
            if(flag[dir] == 1) {
                ++_time;
                flag[dir] = 0;
            }else continue;

            dfs(x+dx[dir], y+dy[dir], x, y);
        }
    }


public:
    Maze() {
        //m_maze = new char[]
        memset(m_maze, '#', sizeof(m_maze));
        memset(visited, 0, sizeof(visited));
    }
    void DrawMaze() {
        //Filled("#", 9, 5, m_width + 9, m_height + 5);
        //while(getchar()) {
            srand(time(NULL));
            dfs(0, 0, -1, -1);
            m_maze[m_width*2][1] = ' ';
            m_maze[0][m_height*2 - 1] = ' ';



            int k = 0;
            for(int j = 0; j <= m_height*2; j++, k++) {
                gotoxy(start_x, start_y+k);
                for(int i = 0; i <= m_width*2; i++){
                    if(m_maze[i][j] == '*')
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                    else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    cout << m_maze[i][j];
                }

            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            gotoxy(start_x+m_width*2, start_y+1); cout << " -GOAL";
            //memset(m_maze, '#', sizeof(m_maze));
            //memset(visited, 0, sizeof(visited));
        }
        void ajusted(char ch ,int x, int y) {
            x-=start_x;
            y-=start_y;
            m_maze[x][y] = ch;
        }
        char getMaze(int x, int y) {
            x = x - start_x;
            y = y - start_y;
            //cout << x << " " << y;
            //return 0;
            return m_maze[x][y];
        }
    //}
};
