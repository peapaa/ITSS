#pragma once
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;
const int M = 20;
const int N = 10;

class Game
{
    public:
    	Game();
        void ChayGame(sf::RenderWindow &window);
    	int Score;
        bool changescore;
    private:
        bool field[N][M] = {0};
        struct Point    {int x,y;} Piece[4];
        struct          {float x,y;} Center;
        Texture t1,t2;
        Sprite s, background;
        Font myFont;
        Text score;
        Text scoreCurrent;    
        float timer=0,delay=0.4;
        Event e;
        float timecount ;
        Clock clock;

        void reset();
        bool check(int x, int y);
        bool canMoveDown();
        void MoveDown();
        bool CanMoveLeft();
        void MoveLeft();
        bool CanMoveRight();
        void MoveRight();
        bool CanRotate();
        void Rotate();
        void MoveRows(int i);
        int CountScore(int Point);
        void DeleteRow();
        void DeathCheck();
};
