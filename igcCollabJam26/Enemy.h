#pragma once

#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy
{
private:
	int hp;
	sf::Vector2f position;


public:
	Enemy();
	~Enemy();
};