#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

/*
	Wrapper class for SFML's window creation, event handling, and rendering - aka game engine
*/
class Game
{
private:
	void initVariables();
	void initWindow();
	void initObjects();
	void loadTextures();

	// Window and window properties
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	sf::Vector2u window_size{ 800, 600 };
	float window_fps_limit = 60.f;

	// Game logic
	float bpm = 120.f;
	float noteSpawnTimerMax = 30.f;
	float noteSpawnTimer = noteSpawnTimerMax;

	bool pressed;
	bool was_pressed = false;

	// Game objects
	sf::Vector2f note_size{ 5.f, 45.f };
	sf::Vector2f note_spawn_position{ static_cast<float>(this->window_size.x), static_cast<float>(this->window_size.y) - 100.f };
	sf::RectangleShape judge_line;

	std::vector<sf::RectangleShape> notes;
	sf::RectangleShape note;

public:
	// Constructor / Destructor
	Game();
	~Game();

	// Getters / Setters
	bool getRunStatus() const;
	sf::Vector2u getWindowSize() const;

	// Functions
	void pollEvents();
	void spawnNote();
	void update();
	void updateNotes();
	void renderJudgeLine();
	void renderNotes();
	void render();

	void throwError(const std::string& message, std::optional<std::string> path = std::nullopt) const;

};