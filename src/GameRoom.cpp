#include "GameRoom.h"
#include <string>
//include <iostream>
GameRoom::GameRoom(sf::RenderWindow &window)
{
	font.loadFromFile("IMG/simplistic_regular.ttf");
	//dienten(window); //Lay ten nguoi choi vao PName
	// menu[0].setFont(font);
	// menu[0].setFillColor(sf::Color::Red);
	// menu[0].setString("Play");
	// menu[0].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 1));
	//
	// menu[1].setFont(font);
	// menu[1].setFillColor(sf::Color::White);
	// menu[1].setString("Create Room");
	// menu[1].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 2));
	// Index = 0;
}


void GameRoom::dienten(sf::RenderWindow &window)
{
	sf::Text playerText;
	playerText.setFont(font);
	playerText.setFillColor(sf::Color::Red);
	playerText.setPosition(sf::Vector2f(50, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 2));

	sf::Text NterName;
	NterName.setFont(font);
	NterName.setFillColor(sf::Color::Red);
	NterName.setString("Enter your name");
	NterName.setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 1));

	sf::Text playerText2;
	sf::Text NterName2;


	bool men = 0;
	sf::Event e;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			window.close();
			if (e.type == sf::Event::TextEntered)
			{
				if(e.text.unicode==13) {
					if(isGuest){
						if(state==0){

							playerText2.setFont(font);
							playerText2.setFillColor(sf::Color::Red);
							playerText2.setPosition(sf::Vector2f(30, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 4));

							NterName2.setFont(font);
							NterName2.setFillColor(sf::Color::Red);
							NterName2.setString("Enter host's IP");
							NterName2.setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 3));
							state =1;
						}
						else if(state){

							men = 1;break;
						}
					}
					else {
							men = 1;break;
					}
				}
				else if(e.text.unicode==8){
					if (men!=1){
						if(state==0)  {
							if(PName!=""){
								PName.pop_back();
								playerText.setString(PName);
							}
						}
						else {
							if(IPss!=""){
								IPss.pop_back();
								playerText2.setString(IPss);
							}
						}
					}
				}
				else {
					if (men!=1){
						if(state==0)  {
							PName +=static_cast<char>(e.text.unicode);
							playerText.setString(PName);
						}
						else {
							IPss +=static_cast<char>(e.text.unicode);
							playerText2.setString(IPss);
						}
					}
				}
			}
		}
		window.clear();
		window.draw(NterName);
		window.draw(playerText);
		if(state){
			window.draw(NterName2);
			window.draw(playerText2);
		}
		window.display();
		sf::sleep(sf::milliseconds(20));
		if(men == 1){
			break;
		}
	}
}

// void PrinVector(std::vector<int> PList)
// {
//     for(auto const& value: PList) {
//         cout<<value<<std::endl;
//     }
// }

void GameRoom::vaophong(std::vector<sf::Text> PList , sf::RenderWindow &window)
{

	window.clear();
	for(auto const& value: PList) {
        window.draw(value);
    }
	window.display();
	sf::sleep(sf::milliseconds(20));
}

void GameRoom::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
	{
		window.draw(PList[i]);
	}
}
