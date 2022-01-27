#include "unit.h"

void unit::engineering() {

	sf::CircleShape engineering(10.f);
	engineering.setTexture; //importTexture
	engineering.setPosition(sf::Vector2f()); //inputVector player

	while (window.isOpen()) //event
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(engineering);
		window.display();
	}
	//move range 1 //direction 8 //vision 1

}
void unit::soldier() {
	int ba = rand() % 5;
	atk f soldier = atk f building = atk = 15 + ba;
	hp = maxhp = 25;
	points = 4;

	sf::CircleShape soldier(10.f);
	soldier.setTexture; //importTexture
	soldier.setPosition(sf::Vector2f());//inputVector player

	while (window.isOpen()) //event
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(soldier);
		window.display();
	}
	//move range 2 //direction 4 //atk range 1 //vision 1

}
void unit::archer() {
	int ba = rand() % 2;
	atk f soldier = atk f building = atk = 10 + ba;
	hp = maxhp = 15;
	points = 5;

	sf::CircleShape archer(10.f);
	archer.setTexture; //importTexture
	archer.setPosition(sf::Vector2f()); //inputVector player

	while (window.isOpen()) //event
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(archer);
		window.display();
	}
	//move range 1 //direction 6 //atk range 3 //vision 1
}
void unit::artillery() {
	int ba1 = rand() % 2;
	int ba2 = rand() % 5;
	atk = 10;
	atk f soldier = ba1 + 2;
	atk f building = ba2 + 10;
	hp = maxhp = 25;
	points = 6;

	sf::CircleShape artillery(10.f);
	artillery.setTexture; //importTexture
	artillery.setPosition(sf::Vector2f());//inputVector player

	while (window.isOpen()) //event
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(artillery);
		window.display();
	}
	//move range 1 //direction 4 //atk range 2 //vision 1
}
void unit::scouts() {
	int ba = rand() % 1;
	atk f soldier = atk f building = atk = 5 + ba;
	hp = maxhp = 12;
	points = 6;

	sf::CircleShape scouts(10.f);
	scouts.setTexture; //importTexture
	scouts.setPosition(sf::Vector2f());//inputVector player

	while (window.isOpen()) //event
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(scouts);
		window.display();
	}
	//move range 1 //direction 8 //atk range 3 //vision 2
}