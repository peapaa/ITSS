#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <vector>
#include <memory>
#include <ctime>
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_PLAYERS 5

class Server
{
	public:
		int PORT;
		Server(sf::RenderWindow &window,std::string PName);
		void Waiting(sf::RenderWindow &window);
		bool DoneWaiting = 0;
		bool CheckGameOver();
		int isReady = 0;

		vector<sf::Text> PList;
		vector<sf::Text> PPoint;
		vector<bool> PGameOver;
		vector<int> thu_tu;

		void InitiatePoint();
		void BroadcastOK();
		void RecScore();
		void BroadcastScore(string buf, int j);
		void changeColors(int i);
		void calculatePoint();
	private:
		void BroadcastNewPlayer(string newPlayer);
		void BroadcastList(int i);
		void draw(sf::RenderWindow &window);
		void takeIn(std::string mess);

		Socket::Status status;
		Packet packet;
		int index=0;
		vector <unique_ptr<TcpSocket>> socket;
		string str;
		TcpListener listener;
		Event e;
		sf::Font font;

};
