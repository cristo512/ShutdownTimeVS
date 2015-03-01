#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <sstream>

const unsigned short int fieldAmount = 9;
const unsigned short int unitFrameAmount = 3;

bool work = true;

class Field
{
public:
	static sf::Font* font;
	Field()
	{

		if (font == nullptr)
		{
			font = new sf::Font;
			font->loadFromFile("C:\\Windows\\Fonts\\comic.ttf");
			std::cout << "to bedzie to\n";
		}
		text.setFont(*font);
		text.setColor(sf::Color::Blue);
		shape.setFillColor(sf::Color::White);
	}
	sf::RectangleShape shape;
	sf::Text text;
	int time;
	void setTextPosition()
	{
		text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width - text.getGlobalBounds().width) / 2,
			shape.getPosition().y + (shape.getGlobalBounds().height - text.getGlobalBounds().height) / 2);
	}
	void setString(std::string string)
	{
		text.setString(string);
		setTextPosition();
	}
	void setPosition(float x, float y)
	{
		shape.setPosition(x, y);
		setTextPosition();
	}
	void draw(sf::RenderWindow &wnd)
	{
		wnd.draw(shape);
		wnd.draw(text);
	}
};

sf::Font* Field::font = nullptr;

void setStrings(Field field[])
{
	field[0].setString("10 min");
	field[1].setString("20 min");
	field[2].setString("30 min");
	field[3].setString("1 h");
	field[4].setString("2 h");
	field[5].setString("4 h");
	field[6].setString("5 h");
	field[7].setString("Anuluj");
	field[8].setString("10 h");
}

void checkEvent(sf::Event &event, sf::RenderWindow &window)
{
	if (event.type == sf::Event::Closed)
		work = false;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ShutdownTime", sf::Style::Close);
	sf::Event event;

	Field field[fieldAmount];
	Field unitFrame[unitFrameAmount];
	Field customField;

	setStrings(field);

	for (int i = 0; i < fieldAmount; i++)
	{
		field[i].shape.setSize(sf::Vector2f(120.f, 110.f));
		field[i].setPosition(140 + (i % 3) * (field[i].shape.getSize().x + 15), 180 + (i / 3) * (field[i].shape.getSize().y + 15));
	}

	window.setFramerateLimit(60);

	while (work)
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
			checkEvent(event, window);

		for (int i = 0; i < fieldAmount; i++)
			field[i].draw(window);


		window.display();
	}
	window.close();
	return 0;
}