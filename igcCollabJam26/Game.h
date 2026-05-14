#pragma once

#include <iostream>
#include <deque>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
	Wrapper class for SFML's window creation, event handling, and rendering - aka game engine
*/
class Enemy;

class Game
{
private:
	void initVariables();
	void initWindow();
	void initObjects();
	void loadTextures();
	void loadMusic();

	// Window properties
	// -- Time Properties --
	sf::Clock clock;
	float deltaTime;

	// -- Modes and Dimensions --
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	sf::Vector2u window_size{ 1280, 720 };
	float window_fps_limit = 60.f;

	// -- Music --
	sf::Music music;

	// Game logic
	float bpm = 135.f;
	float secondsPerBeat = 60.f / bpm;
	float noteSpawnTimer = secondsPerBeat;

	float beatsToTravel = 4.f;
	float travelTime = beatsToTravel * secondsPerBeat;

	bool pressed;
	bool was_pressed = false;

public:
	// Constructor / Destructor
	Game();
	~Game();

	// Objects
	struct Note {
		sf::RectangleShape shape;
		bool isHit = false;
		bool faded = false;
		float fadeTimer = 0.f;
	};

	struct Sword {

	};

	struct Enemy {

	};

	sf::RectangleShape judge_line;

	sf::Vector2f note_size{ 5.f, 45.f };
	sf::Vector2f note_spawn_position{ static_cast<float>(window_size.x), static_cast<float>(window_size.y) - 100.f };

	std::deque<Note> notes;
	std::deque<Note> fadingNotes;
	Note note;

	Enemy* enemy;

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
	void fadeNote(Note& note);
	void gradeNote(Note& note);
	void render();

	void throwLoadError(const std::string& message, std::optional<std::string> path = std::nullopt) const;

};