#include "Menu.h"
#include "SFML/Graphics.hpp"
using namespace sf;
Menu::Menu(sf::RenderWindow &window)
{
	if (!font.loadFromFile("IMG/simplistic_regular.ttf"))
	{
		// handle error
	}
	float width = window.getSize().x; float height = window.getSize().y;
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Create Room");
	menu[1].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Joint Room");
	menu[2].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	selectedItemIndex = 0;
    bool men = 0;
    while (window.isOpen())
    {
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

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
