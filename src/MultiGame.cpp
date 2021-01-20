#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <sstream>
#include <time.h>
#include "MultiGame.h"
using namespace std;
using namespace sf;

MultiGame::MultiGame()
{
    srand(time(NULL));
    t1.loadFromFile("IMG/Pit.png");
    t2.loadFromFile("IMG/L.png");
    Score = 0;
    s.setTexture(t2); background.setTexture(t1);
    myFont.loadFromFile("IMG/simplistic_regular.ttf");
    reset();

}
void MultiGame::ChayGame(sf::RenderWindow &window)
{
    changescore = 0;
    if (IsGameOver==0)
    {
        timecount = clock.getElapsedTime().asSeconds();
        clock.restart();
    	timer+=timecount;
    	while (window.pollEvent(e))
    	{
    	    if (e.type == Event::Closed)
    		window.close();
    	    if (e.type == Event::KeyPressed)
    		if (e.key.code==Keyboard::Up) Rotate();
    		else if (e.key.code==Keyboard::Left) MoveLeft();
    		else if (e.key.code==Keyboard::Right) MoveRight();
            else if (e.key.code==Keyboard::Down) delay=0.05;
        	if (e.type == Event::KeyReleased && e.key.code==Keyboard::Down)
            delay = 0.4;
    	}
    	if (timer>delay)
    	{
    	    if (canMoveDown())
    		MoveDown();
    	    else
    	    {
        		if(DeathCheck() && IsGameOver==0){
              IsGameOver=1;
              ss = 1;
            }
                else{
        		DeleteRow();
        		reset();
                }
    	    }
    	    timer=0;
    	}
    }
    else{
      while (window.pollEvent(e))
    	{
    	    if (e.type == Event::Closed)
    		window.close();
      }
    }
	window.clear();
	window.draw(background);
	/*---------DRAW TABLE---------*/
	for (int i=0;i<NN;i++)
	    for (int j=0;j<MM;j++)
		if (field[i][j]==1)
		{
		    s.setPosition(i*20+5,j*20+5);
		    window.draw(s);
		}
	stringstream s;
	s << Score;

	sf::sleep(sf::milliseconds(20));
}

void MultiGame::reset()
{
    int PieceType =  1 + (rand() % 7);
    switch (PieceType) {
	case 1: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 4;  Piece[2].y = 2;
		Piece[3].x = 4;  Piece[3].y = 3;
		Center.x = 4.5;  Center.y = 1.5;
		break;
	case 2: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 5;  Piece[3].y = 2;
		Center.x = 5;  Center.y = 1;
		break;
	case 3: Piece[0].x = 5;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 1;
		Piece[2].x = 4;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 5;  Center.y = 1;
		break;
	case 4: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 4;	Center.y = 1;
		break;
	case 5: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 0;
		Piece[3].x = 5;  Piece[3].y = 1;
		Center.x = 4.5;	Center.y = 0.5;
		break;
	case 6: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 0;
		Piece[2].x = 4;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 4;	Center.y = 1;
		break;
	case 7: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 0;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 5;  Piece[3].y = 2;
		Center.x = 5;	Center.y = 1;
		break;
    }
    for (int i=0;i<4;i++)
	field[Piece[i].x][Piece[i].y] = 1;
}
bool MultiGame::check(int x, int y)
{
    for (int i=0; i<4; i++)
    {
	if ((Piece[i].x == x) && (Piece[i].y == y))
	    return 0;
    }
    return 1;
}
bool MultiGame::canMoveDown()
{

    for (int i=0;i<4;i++)
	if (((field[Piece[i].x][Piece[i].y+1]==1) && check(Piece[i].x,Piece[i].y+1))
		|| (Piece[i].y == MM-1))
	    return 0;
    return 1;
}
void MultiGame::MoveDown()
{
    for (int i=0;i<4;i++)
    {
	field[Piece[i].x][Piece[i].y] = 0;
	Piece[i].y++;
    }
    for (int i=0;i<4;i++)
	field[Piece[i].x][Piece[i].y] = 1;
    Center.y++;
}
bool MultiGame::CanMoveLeft()
{
    for (int i=0;i<4;i++)
	if (((field[Piece[i].x-1][Piece[i].y]==1) && check(Piece[i].x-1,Piece[i].y))
		|| (Piece[i].x == 0))
	    return 0;
    return 1;
}
void MultiGame::MoveLeft()
{
    if(CanMoveLeft())
    {
	for (int i=0;i<4;i++)
	{
	    field[Piece[i].x][Piece[i].y] = 0;
	    Piece[i].x--;
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
	Center.x--;
    }
}
bool MultiGame::CanMoveRight()
{
    for (int i=0;i<4;i++)
	if (((field[Piece[i].x+1][Piece[i].y]==1) && check(Piece[i].x+1,Piece[i].y))
		|| (Piece[i].x == NN-1))
	    return 0;
    return 1;
}
void MultiGame::MoveRight()
{
    if(CanMoveRight())
    {
	for (int i=0;i<4;i++)
	{
	    field[Piece[i].x][Piece[i].y] = 0;
	    Piece[i].x++;
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
	Center.x++;
    }
}
bool MultiGame::CanRotate()
{
    float posx, posy;
    for (int i=0; i<4; i++)
    {
    	posx = Piece[i].x - Center.x;
    	posy = Piece[i].y - Center.y;
    	int a = (int)(Center.x - posy);
    	int b = (int)(Center.y + posx);
    	if ((field[a][b]==1 && check(a,b)) || !(a>=0 && b>=0 && a<NN && b<MM))
    	    return 0;
    }
    return 1;
}
void MultiGame::Rotate()
{
    float posx, posy;
    if(CanRotate())
    {
	for (int i=0; i<4; i++)
	{
	    posx = Piece[i].x - Center.x;
	    posy = Piece[i].y - Center.y;
	    field[Piece[i].x][Piece[i].y] = 0;

	    Piece[i].x = (int)(Center.x - posy);
	    Piece[i].y = (int)(Center.y + posx);
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
    }
}
void MultiGame::MoveRows(int i)
{
    for(int j=i; j>0; j--)
	for(int q=0; q<NN; q++)
	    field[q][j] = field[q][j-1];
    for (int q=0; q<NN; q++)
	field[1][0] = 0;
}
int MultiGame::CountScore(int Point)
{
    switch (Point)
    {
	case 1 : return 40;
	case 2 : return 100;
	case 3 : return 300;
	case 4 : return 1200;
	default : return 0;
    }
}
void MultiGame::DeleteRow()
{
    bool a; int Point = 0;
    for (int i=0; i<MM; i++)
    {
    	a = true;
    	for (int j=0 ; j<NN; j++)
    	    a = a && field[j][i];
    	if (a)
    	{
    	    MoveRows(i); Point++;
    	}
    }
    if (Point > 0) changescore = 1;
    Score += CountScore(Point);
}
bool MultiGame::DeathCheck()
{
    for (int i=0; i<4; i++)
	if (Piece[i].y==0 && Piece[i].x==4)
	{
	    cout<<"Final score: "<<Score<<endl;
	    return 1;
	}
    return 0;
}
void MultiGame::PrintVector(sf::RenderWindow &window, std::vector<sf::Text> PList,
     std::vector<sf::Text> PPoint)
{
    for(auto const& value: PList) {
        window.draw(value);
    }
    for(auto const& value: PPoint) {
        window.draw(value);
    }
}
void MultiGame::AnoundWinner(sf::RenderWindow &window,std::vector<sf::Text> PList,
    std::vector<sf::Text> PPoint){
      while (window.pollEvent(e))
    	{
    	    if (e.type == Event::Closed)
    		window.close();
      }
      window.clear();
      for(auto const& value: PList) {
          window.draw(value);
      }
      for(auto const& value: PPoint) {
          window.draw(value);
      }
      window.display();
}
