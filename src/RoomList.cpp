#include "RoomList.h"

RoomList::RoomList(sf::RenderWindow &window)
{
	float width = window.getSize().x; float height = window.getSize().y;
	if (!font.loadFromFile("IMG/simplistic_regular.ttf"))
	{
		// handle error
	}

	Index = 0;
	bool men = 0;
	Clock clock;
	Event e;
	while (window.isOpen())
	{
		if(clock.getElapsedTime().asSeconds()>1)
		{
			clock.restart();
			ScanIP();
			SetRooms(height);
		}
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			window.close();
			if (e.type == Event::KeyPressed)
			if (e.key.code==Keyboard::Up) MoveUp();
			else if (e.key.code==Keyboard::Down) MoveDown();
			else if (e.key.code==Keyboard::Enter) men =1;
		}
		window.clear();
		draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
		if(men == 1) break;
	}
}

bool RoomList::is_port_open(IpAddress ip, int port)
{

    bool a=(sf::TcpSocket().connect(ip, port) == sf::Socket::Done);

		return a;
}

void RoomList::ScanIP()
{
	int j=0;
	// for (int i1=1; i1<=255; i1++){
	// 	for (int i2=1; i2<=255; i2++){
	// 		string sss = "192.168."+std::to_string(i1)+"."+std::to_string(i2);
	// 		cout<<sss<<endl;
	// 		if (is_port_open(sf::IpAddress(sss), 8000) && j<7)
	// 		{
	// 			cout<<sss<<endl;
	// 			rooms.push_back(sss);
	// 			j++;
	// 		}
	// 	}
	// }
	//rooms.push_back("192.168.43.59");j++;
	NumberOfRooms = j;
}
void RoomList::SetRooms(float height)
{
	int j=0;
	for(int i=0; i<NumberOfRooms;i++)
	if (rooms[i]!="")
	{
		roomList[j].setFont(font);
		roomList[j].setFillColor(sf::Color::Red);
		roomList[j].setString("room  "+ rooms[i]);
		roomList[j].setCharacterSize(15);
		roomList[j].setPosition(sf::Vector2f(50, height / (7 + 1) * j));
		j++;
	}
}
void RoomList::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < NumberOfRooms; i++)
	{
		window.draw(roomList[i]);
	}
}

void RoomList::MoveUp()
{
	if (Index > 0)
	{
		roomList[Index].setFillColor(sf::Color::White);
		Index--;
		roomList[Index].setFillColor(sf::Color::Red);
	}
}

void RoomList::MoveDown()
{
	if (Index < (NumberOfRooms-1))
	{
		roomList[Index].setFillColor(sf::Color::White);
		Index++;
		roomList[Index].setFillColor(sf::Color::Red);
	}
}
