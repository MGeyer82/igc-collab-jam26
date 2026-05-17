#include "Game.h"
#include "Textures.h"
#include "Music.h"
#include "SFX.h"
#include "Layout.h"

/**
*	Game class constructor / destructor
*/
Game::Game()
{
	loadTextures();
	loadMusic();
	loadSFX();

	initVariables();
	initProps();
	initSprites();
	initWindow();
	resizeWindow();
	initLayout();
	initObjects();
}

Game::~Game()
{
	delete window;
}

/**
*	Private functions
*/
void Game::loadTextures()
{
	//std::cout << std::filesystem::current_path() << '\n';

	// Player textures
	for (auto& [index, path] : player_paths)
	{
		if (!player.textures[index].loadFromFile(path))
		{
			throwLoadError("Error loading texture from file: ", path);
		}
	}

	// Enemy textures
	for (auto& [index, path] : enemy_paths)
	{
		if (!enemy.textures[index].loadFromFile(path))
		{
			throwLoadError("Error loading texture from file: ", path);
		}
	}

	// Layout textures
	for (auto& [index, path] : layout_paths)
	{
		if (!layoutTextures[index].loadFromFile(path))
		{
			throwLoadError("Error loading texture from file: ", path);
		}
	}

	// UI textures
	for (auto& [index, path] : ui_paths)
	{
		if (!uiTextures[index].loadFromFile(path))
		{
			throwLoadError("Error loading texture from file: ", path);
		}
	}
}

void Game::loadMusic()
{
	for (auto& [index, path] : music_paths)
	{
		if (!bgm[index].openFromFile(path))
		{
			throwLoadError("Error loading music from file: ", path);
		}
	}

	notesToSpawn[0] = 124;
	notesToSpawn[1] = 256;
	notesToSpawn[2] = 199;
}

void Game::loadSFX()
{
	// menu SFX
	for (auto& [index, path] : menu_paths)
	{
		if (!menu_sfx[index].loadFromFile(path))
		{
			throwLoadError("Error loading sfx from file: ", path);
		}
	}

	// swing SFX
	for (auto& [index, path] : swing_paths)
	{
		if (!swing_sfx[index].loadFromFile(path))
		{
			throwLoadError("Error loading sfx from file: ", path);
		}
	}

	// hit SFX
	for (auto& [index, path] : hit_paths)
	{
		if (!hit_sfx[index].loadFromFile(path))
		{
			throwLoadError("Error loading sfx from file: ", path);
		}
	}
}

void Game::resizeWindow()
{
	sf::Vector2u window_size = getWindowSize();

	float windowRatio = static_cast<float>(window_size.x) / window_size.y;

	float viewRatio = static_cast<float>(game_size.x) / game_size.y;

	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	bool horizontalSpacing = windowRatio > viewRatio;

	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	sf::View view(sf::FloatRect(
		{ 0.f, 0.f },
		{ game_size.x, game_size.y }
	));

	view.setViewport(sf::FloatRect(
		{ posX, posY },
		{ sizeX, sizeY }
	));

	window->setView(view);
}

void Game::initVariables()
{
	// initialize variables
	window = nullptr;
}

void Game::initWindow()
{
	// initialize window
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Cursed Cadence", sf::State::Fullscreen);

	window->setFramerateLimit(60);
}

void Game::initLayout()
{
	sf::RectangleShape idleBox;
	sf::RectangleShape hitBox;

	sf::RectangleShape enemyBox;
	sf::RectangleShape rhythmBox;
	sf::RectangleShape worldBox;
	sf::RectangleShape borderBox;

	// idle box
	idleBox.setSize({ 135.f, 255.f });

	// swing box
	hitBox.setSize({ 255.f, 135.f });
	hitBox.setPosition({ 100.f, 250.f });

	// rhythm section box
	rhythmBox.setSize({ 1235.f, 175.f });

	// enemy box
	enemyBox.setSize({ 140.f, 200.f });

	// border box
	borderBox.setSize({ 1280.f, 720.f });

	// world box
	worldBox.setSize({ 1230.f, 720.f - 225.f });
}

void Game::initObjects()
{
	// init judgement line
	judge_line.setSize(note_size);
	judge_line.setFillColor(sf::Color::White);
	judge_line.setPosition(judge_line_pos);

}

void Game::initSprites()
{
	// TODO: hard coded coordinates - BAD!
	sf::Sprite rhythm_sprite(layoutTextures.at(LayoutTextures::RHYTHM_BAR));
	rhythm_sprite.setPosition(rhythm_bar_pos);
	//rhythm_sprite.setScale({ 1.f, 0.75f });

	sf::Sprite player_sprite(player.textures.at(PlayerTextures::IDLE));
	player_sprite.setPosition({ 160.f, 100.f });
	player_sprite.setScale({ 0.8f, 1.f });

	sf::Sprite enemy_sprite(enemy.textures.at(EnemyTextures::MOVE_DOWN));
	enemy_sprite.setPosition({ 750.f, 150.f });

	sf::Sprite world_sprite(layoutTextures.at(LayoutTextures::CASTLE_1));
	world_sprite.setPosition({ 25.f, 25.f });
	world_sprite.setScale({ 0.95f, 0.95f });


	game_sprites.push_back(world_sprite);
	game_sprites.push_back(player_sprite);
	game_sprites.push_back(enemy_sprite);
	game_sprites.push_back(rhythm_sprite);
	//game_sprites.push_back(border_sprite);
}

/**
*	Getters / Setters
*/
bool Game::getRunStatus() const
{
	return window->isOpen();
}

sf::Vector2u Game::getWindowSize() const
{
	return window->getSize();
}

/**
*	Public functions
*/
void Game::pollEvents()
{
	// poll events
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window->close();
			break;
		}

		if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPress->code)
			{
				case sf::Keyboard::Key::Escape:
					// open pause menu
					bgm[BGM::STAGE_3].pause();
					is_paused = true;
					break;

				case sf::Keyboard::Key::Q:
					window->close();
					break;
			
				case sf::Keyboard::Key::Enter:
					if (bgm[BGM::STAGE_3].getStatus() != sf::Music::Status::Playing)
					{
						bgm[BGM::STAGE_3].play();
						clock.restart(); // Start the clock when the music starts playing
					}
					break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (is_paused)
			{
				bgm[BGM::STAGE_3].play();
				is_paused = false;
			}
		}

		// Space key press handling - note hit detection
		pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);;

		// TODO: Figure out why the error detection isn't working here for when no notes are present...
		if (pressed && !was_pressed)
		{

			if (notes.empty())
			{
				return;
			}

			// Add note to fadingNotes then remove from notes vector to begin fade animation
			fadingNotes.push_back(notes.front());
			notes.pop_front();

		}

		was_pressed = pressed;
	}
}

void Game::spawnNote()
{
	note.shape.setPosition(note_spawn_pos);
	note.shape.setFillColor(sf::Color::Red);
	note.shape.setSize(note_size);

	// enemy spawn
	game_sprites[2].setPosition(enemy_spawn_pos);

	notes.push_back(note);
	//enemies.push_back(enemies);
}

void Game::gradeNote(Note& note)
{
	// Calculate the distance between the note and the judge line
	float distance = std::abs(note.shape.getPosition().x - judge_line.getPosition().x);

	// Define thresholds for grading (these values can be adjusted based on gameplay feel)
	const float perfectThreshold = 10.f;
	const float goodThreshold = 30.f;
	const float badThreshold = 50.f;

	// Grade the note based on the distance
	if (distance <= perfectThreshold)
	{
		std::cout << "Perfect!" << std::endl;
	}
	else if (distance <= goodThreshold)
	{
		std::cout << "Good!" << std::endl;
	}
	else if (distance <= badThreshold)
	{
		std::cout << "Bad!" << std::endl;
	}
	else
	{
		std::cout << "Miss!" << std::endl;
	}
	note.isHit = true; // Mark the note as hit
}

void Game::fadeNote(Note& note)
{
	// Begin the fade animation for the note
		
	// enlarge notes while adjusting transparency to indicate note hit
	if (note.fadeTimer < 15.f)
	{
		note.fadeTimer += 1.f;
		float fadeProgress = note.fadeTimer / 15.f; // Normalize fade timer to [0, 1] range

		fadingNotes.front().shape.setOrigin({ note_size.x / 2.f, note_size.y / 2.f });
		fadingNotes.front().shape.setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(255 * (1.f - fadeProgress))));
		fadingNotes.front().shape.setScale(sf::Vector2f(note.fadeTimer * 0.5f, note.fadeTimer * 0.25f));


	}
	else // Once the fade animation is complete, mark the note as faded
	{
		note.faded = true;
	}

	// Once the note has fully faded, remove it from the vector
	if (note.faded)
	{
		// then pop the note from the vector...
		if (!fadingNotes.empty())
			fadingNotes.pop_front();
	}
}

void Game::spawnEnemy()
{

}

void Game::updateNotes()
{
	float distance = (note_spawn_pos.x - judge_line.getPosition().x);
	float noteSpeed = distance / travelTime;

	// if the note spawn timer has reached its max, spawn a new note and reset the timer	
	noteSpawnTimer += deltaTime;

	while (noteSpawnTimer >= secondsPerBeat && notesToSpawn[(int)BGM::STAGE_3] != 0)
	{
		spawnNote();
		//spawnEnemy();
		noteSpawnTimer -= secondsPerBeat;
		notesToSpawn[(int)BGM::STAGE_3]--;
	}

	// move the notes along the screen and remove any that pass the left boundary of the window (missed notes)
	for (auto& note : this->notes)
	{
		note.shape.move({ -noteSpeed * deltaTime, 0.f });

		if (note.shape.getPosition().x < 0.f)
		{
			//std::cout << "Missed Note!" << std::endl;
			notes.erase(notes.begin());
		}
	}

	// handle fading notes
	for (auto& f_note : fadingNotes)
	{
		fadeNote(f_note);
	}
}

void Game::updateScenes()
{

}

void Game::updateEnemies()
{
	float distance = (note_spawn_pos.x - judge_line.getPosition().x);
	float enemySpeed = distance / travelTime;

	// move the enemies along the screen and remove any that pass the left boundary of the window (missed notes)
	for (auto& note : this->notes)
	{
		enemy.shape.move({ -enemySpeed * deltaTime, 0.f });

		if (enemy.shape.getPosition().x < 0.f)
		{
			//std::cout << "Missed Note!" << std::endl;
			enemies.erase(enemies.begin());
		}
	}

	//// handle fading enemies
	//for (auto& f_enemy : fadingEnemies)
	//{
	//	fadeEnemy(f_enemy);
	//}
}

void Game::update()
{
	pollEvents();

	deltaTime = clock.restart().asSeconds();
	deltaTime = std::min(deltaTime, 0.1f);

	if (is_paused)
	{
		return;
	}

	// run implementation
	if (bgm[BGM::STAGE_3].getStatus() == sf::Music::Status::Playing)
	{
		updateNotes();
	}

	updateScenes();
	updateEnemies();
}

void Game::renderJudgeLine()
{
	window->draw(judge_line);
}

void Game::renderNotes()
{
	for (auto& note : notes)
	{
		window->draw(note.shape);
	}

	for (auto& f_note : fadingNotes)
	{
		window->draw(f_note.shape);
	}
}

void Game::renderLayout()
{

	for (auto& sprite : game_sprites)
	{
		window->draw(sprite);
	}
}

void Game::renderBorder()
{
	sf::Sprite border_sprite(layoutTextures.at(LayoutTextures::BORDER));
	border_sprite.setPosition({ 0.f, 0.f });

	window->draw(border_sprite);
}

void Game::renderEnemies()
{
	for (auto& enemy : enemies)
	{
		window->draw(enemy.shape);
	}

	for (auto& f_enemy : fadingEnemies)
	{
		window->draw(f_enemy.shape);
	}
}

void Game::renderPauseMenu()
{
	sf::RectangleShape pause_rect;

	pause_rect.setFillColor(sf::Color(0, 0, 0, 200));
	pause_rect.setPosition({ 0.f, 0.f });
	pause_rect.setSize(game_size);

	pause_menu_size = { 400.f, 500.f };
	pause_menu_pos = { (game_size.x / 2.f) - (pause_menu_size.x / 2.f), (game_size.y / 2.f) - (pause_menu_size.y / 2.f) };
	sf::Sprite pause_menu(uiTextures.at(uiTextures::PAUSE_OPEN));
	pause_menu.setPosition(pause_menu_pos);

	window->draw(pause_rect);
	window->draw(pause_menu);

}

void Game::render()
{
	// clear the screen - default black
	window->clear(sf::Color::Black);

	// draw everything here...
	renderLayout();
	renderJudgeLine();
	renderNotes();
	renderEnemies();
	renderBorder();

	if (is_paused)
	{
		renderPauseMenu();
	}

	// tell the window we're done drawing
	window->display();
}

void Game::throwLoadError(const std::string& message, std::optional<std::string> path) const
{
	std::cerr << "Error: " << message;
	if (path)
	{
		std::cerr << " Path: " << *path;
	}
	std::cerr << std::endl;
}
