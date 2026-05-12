#include "Game.h"

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
	window = new sf::RenderWindow(video_mode, "Collab Jam 26");

	window->setFramerateLimit(60);
}

void Game::initObjects()
{
	// init judgement line
	judge_line.setSize(note_size);
	judge_line.setFillColor(sf::Color::White);
	judge_line.setPosition({ 50.f, window_size.y - 100.f });


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
	else
	{
		music.play();
		clock.restart(); // Start the clock when the music starts playing
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
				std::cout << "empty vector!" << std::endl;
				return;
			}

			std::cout << "contained at least one note... " << std::endl;

			// remove note from notes vector and add to fadingNotes vector to begin fade animation
			notes.erase(notes.begin());
			fadingNotes.push_back(notes.front());

			//std::cout << "Pressed space!" << std::endl;
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

void Game::fadeNote(Note& note)
{
	// Begin the fade animation for the note

	// TODO: This needs some tweaking to look better... also only seem to fade one note at a time?
		
	// enlarge notes while adjusting transparency to indicate note hit
	if (note.fadeTimer < 30.f)
	{
		note.fadeTimer += 1.f;
		this->notes.front().shape.setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(255 - (note.fadeTimer * 2.f))));
		this->notes.front().shape.setSize(this->note_size + sf::Vector2f(note.fadeTimer, note.fadeTimer));
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
			fadingNotes.erase(fadingNotes.begin());
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
	// run implementation
	deltaTime = clock.restart().asSeconds();
	deltaTime = std::min(deltaTime, 0.1f);

	pollEvents();
	updateNotes();
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
