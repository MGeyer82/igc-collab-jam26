#pragma once

#include <iostream>
#include <deque>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Textures.h"
#include "Music.h"
#include "SFX.h"

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
	void initLayout();
	void initSprites();
	void resizeWindow();

	void loadTextures();
	void loadMusic();
	void loadSFX();

	// Window properties
	// -- Time Properties --
	sf::Clock clock;
	float deltaTime;

	// -- Modes and Dimensions --
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	sf::Vector2f game_size{ 1280.f, 720.f };
	float window_fps_limit = 60.f;

	float border_edge_size;
	sf::Vector2f rhythm_bar_size;
	sf::Vector2f rhythm_bar_pos;
	sf::Vector2f judge_line_pos;

	// -- Sprites --
	std::vector<sf::Sprite> game_sprites;

	// -- Music --
	std::unordered_map<BGM, sf::Music> bgm;

	// -- SFX --
	std::unordered_map<menuSFX, sf::SoundBuffer> menu_sfx;
	std::unordered_map<hitSFX, sf::SoundBuffer> hit_sfx;
	std::unordered_map<swingSFX, sf::SoundBuffer> swing_sfx;

	// Game logic
	float bpm = 135.f;
	float secondsPerBeat = 60.f / bpm;
	float noteSpawnTimer = secondsPerBeat;

	float beatsToTravel = 4.f;
	float travelTime = beatsToTravel * secondsPerBeat;

	bool pressed;
	bool was_pressed = false;
	bool is_paused = false;

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

	sf::Vector2f note_spawn_pos;

	struct Player {
		int hp = 0;
		sf::Vector2f position;
		std::unordered_map<PlayerTextures, sf::Texture> textures;
		//sf::Sprite sprite{ textures[0] };
	};

	struct Enemy {
		int hp = 0;
		sf::Vector2f position;
		std::unordered_map<EnemyTextures, sf::Texture> textures;
		//sf::Sprite sprite{ textures[0] };
	};

	// judgement line - used for scoring
	sf::RectangleShape judge_line;

	// note properties
	sf::Vector2f note_size{ 5.f, 90.f };
	sf::Vector2f note_spawn_position{ static_cast<float>(game_size.x), static_cast<float>(game_size.y) - 100.f };

	// note vectors and objects
	std::deque<Note> notes;
	std::deque<Note> fadingNotes;
	Note note;

	// enemy objects
	Enemy enemy;

	// player/sword objects
	Player player;

	// Scenery / Layout textures
	std::unordered_map<LayoutTextures, sf::Texture> layoutTextures;

	// Getters / Setters
	bool getRunStatus() const;
	sf::Vector2u getWindowSize() const;

	// Functions
	void pollEvents();
	void spawnNote();
	void fadeNote(Note& note);
	void gradeNote(Note& note);

	void update();
	void updateNotes();
	void updateScenes();
	void updateEnemies();

	void renderJudgeLine();
	void renderNotes();
	void renderLayout();
	void renderPauseMenu();
	void render();

	void throwLoadError(const std::string& message, std::optional<std::string> path = std::nullopt) const;

};