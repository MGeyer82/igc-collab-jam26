#include "Game.h"
#include "Enemy.h"

/**
*	Game class constructor / destructor
*/
Game::Game()
{
	loadTextures();
	loadMusic();

	initVariables();
	initWindow();
	initObjects();
}

Game::~Game()
{
	delete window;
}

/**
*	Private functions
*/
void Game::initVariables()
{
	// initialize variables
	window = nullptr;
}

void Game::initWindow()
{
	// initialize window
	video_mode.size.x = window_size.x;	// width
	video_mode.size.y = window_size.y;	// height
	window = new sf::RenderWindow(video_mode, "Collab Jam 26", sf::State::Fullscreen);

	window->setFramerateLimit(60);
}

void Game::initObjects()
{
	// init judgement line
	judge_line.setSize(note_size);
	judge_line.setFillColor(sf::Color::White);
	judge_line.setPosition({ 50.f, window_size.y - 100.f });

	// init enemy

}

void Game::loadTextures()
{

}

void Game::loadMusic()
{
	if (!music.openFromFile(".\\assets\\Wub_Wub_Thing.wav"))
	{
		throwLoadError("Failed to load music!", ".\\assets\\Wub_Wub_Thing.wav");
	}
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
	return window_size;
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
					window->close();
					break;
			
				case sf::Keyboard::Key::Enter:
					if (music.getStatus() != sf::Music::Status::Playing)
					{
						music.play();
						clock.restart(); // Start the clock when the music starts playing
					}
					break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{

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
	note.shape.setPosition(note_spawn_position);
	note.shape.setFillColor(sf::Color::Red);
	note.shape.setSize(note_size);

	notes.push_back(note);
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

void Game::updateNotes()
{
	float distance = (note_spawn_position.x - judge_line.getPosition().x);
	float noteSpeed = distance / travelTime;

	// if the note spawn timer has reached its max, spawn a new note and reset the timer	
	noteSpawnTimer += deltaTime;

	while (noteSpawnTimer >= secondsPerBeat)
	{
		spawnNote();
		noteSpawnTimer -= secondsPerBeat;
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

void Game::update()
{
	pollEvents();

	// run implementation
	if (music.getStatus() == sf::Music::Status::Playing)
	{
		deltaTime = clock.restart().asSeconds();
		deltaTime = std::min(deltaTime, 0.1f);

		updateNotes();
	}
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

void Game::render()
{
	// clear the screen - default black
	window->clear(sf::Color::Black);

	// draw everything here...
	renderJudgeLine();
	renderNotes();

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
