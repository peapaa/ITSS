#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <string>
using namespace std;
using namespace sf;

class RoomList
{
	public:
		RoomList(sf::RenderWindow &window);
		int Index;
		std::vector<std::string> rooms ;

	private:
		//IpAddress ip = IpAddress::getLocalAddress();
		int NumberOfRooms = 0;
		bool is_port_open(IpAddress ip, int port);
		void ScanIP();
		void SetRooms(float height);
		void draw(sf::RenderWindow &window);
		void MoveUp();
		void MoveDown();
		sf::Font font;
		sf::Text roomList[7];
};
