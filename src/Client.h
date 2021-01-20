
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#define MAX_NUMBER_OF_PLAYERS 5
using namespace std;
using namespace sf;

class Client
{
	public:
		Client(string roomIP);
    void SendPoint(string mess);
		bool ReceiName(sf::RenderWindow &window);
		void Waiting(sf::RenderWindow &window);
		void InitiatePoint();
		void ReceiveScore();
		void calculatePoint();

		vector<sf::Text> PList;
		vector<sf::Text> PPoint;
		vector<int> thu_tu;
		bool DoneWaiting = 0;
		bool ReceivedName = 0;
		bool IsGameOver = 0;
		bool isReady = 0;
	private:
		sf::Font font;
		int index = 0;
		sf::Event e;
        IpAddress ip ;//= IpAddress::getLocalAddress();
        TcpSocket socket;
        Packet packet;

		void takeOut(std::string mess);
		void deletePlayer(int j);


};
