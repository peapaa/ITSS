#pragma once
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;
const int MM = 20;
const int NN = 10;

class MultiGame
{
    public:
    	MultiGame();

        void ChayGame(sf::RenderWindow &window);
        void PrintVector(sf::RenderWindow &window,std::vector<sf::Text> PList,
            std::vector<sf::Text> PPoint);
        void AnoundWinner(sf::RenderWindow &window,std::vector<sf::Text> PList,
            std::vector<sf::Text> PPoint);

        void calculatePoint(std::vector<sf::Text> PList, std::vector<sf::Text> PPoint);

    	int Score;

      bool ss= false;
        bool changescore;
        bool IsGameOver=0;
    private:
        bool field[NN][MM] = {0};
        struct Point    {int x,y;} Piece[4];
        struct          {float x,y;} Center;
        Texture t1,t2;
        Sprite s, background;
        Font myFont;
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
        bool DeathCheck();

};
