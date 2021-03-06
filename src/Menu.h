#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(sf::RenderWindow &window);
	int selectedItemIndex;

private:
	sf::Event e;
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
