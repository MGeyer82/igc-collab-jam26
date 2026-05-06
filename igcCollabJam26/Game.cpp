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
	delete this->window;
}

/**
*	Private functions
*/
void Game::initVariables()
{
	// initialize variables
	this->window = nullptr;
}

void Game::initWindow()
{
	// initialize window
	this->video_mode.size.x = this->window_size.x;	// width
	this->video_mode.size.y = this->window_size.y;	// height
	this->window = new sf::RenderWindow(this->video_mode, "Collab Jam 26");

	this->window->setFramerateLimit(60);
}

void Game::initObjects()
{
	// init judgement line
	judge_line.setSize(this->note_size);
	judge_line.setFillColor(sf::Color::White);
	judge_line.setPosition({ 50.f, this->window_size.y - 100.f });


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
	return this->window->isOpen();
}

sf::Vector2u Game::getWindowSize() const
{
	return this->window_size;
}

/**
*	Public functions
*/
void Game::pollEvents()
{
	// poll events
	while (const std::optional event = this->window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			this->window->close();
			break;
		}

		if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPress->code)
			{
			case sf::Keyboard::Key::Escape:
				this->window->close();
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{

		}

		// Space key press handling - note hit detection
		this->pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);;

			if (this->pressed && !this->was_pressed)
			{
				// enlarge notes while adjusting transparency to indicate note hit
				notes.front().fading = true;

				//std::cout << "Pressed space!" << std::endl;
			}

			this->was_pressed = this->pressed;
	}
}

void Game::spawnNote()
{
	this->note.shape.setPosition(this->note_spawn_position);
	this->note.shape.setFillColor(sf::Color::Red);
	this->note.shape.setSize(this->note_size);

	this->notes.push_back(this->note);
}

void Game::fadeNote(Note& note)
{
	// Begin the fade animation for the note
	if (note.fading)
	{
		// TODO: This needs some tweaking to look better... also only seem to fade one note at a time?
		
		//if (note.fadeTimer < 30.f)
		//{
		//	note.fadeTimer += 1.f;
		//	this->notes.front().shape.setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(255 - (note.fadeTimer * 2.f))));
		//	this->notes.front().shape.setSize(this->note_size + sf::Vector2f(note.fadeTimer, note.fadeTimer));
		//}
		//else // Once the fade animation is complete, mark the note as faded
		//{
			note.faded = true;
		//}
	}

	// Once the note has fully faded, remove it from the vector
	if (note.faded)
	{
		// then pop the note from the vector...
		if (!notes.empty())
			this->notes.erase(this->notes.begin());
	}
}

void Game::updateNotes()
{
	float distance = (this->note_spawn_position.x - this->judge_line.getPosition().x);
	float noteSpeed = distance / this->travelTime;

	// if the note spawn timer has reached its max, spawn a new note and reset the timer	
	noteSpawnTimer += this->deltaTime;

	while (this->noteSpawnTimer >= this->secondsPerBeat)
	{
		spawnNote();
		this->noteSpawnTimer -= this->secondsPerBeat;
	}

	// move the notes and handle fading
	for (auto& note : this->notes)
	{
		if (!note.fading)
		{
			note.shape.move({ -noteSpeed * deltaTime, 0.f });
		}
		else
		{
			fadeNote(note);
		}

		if (note.shape.getPosition().x < 0.f)
		{
			//std::cout << "Missed Note!" << std::endl;
			this->notes.erase(this->notes.begin());
		}
	}
}

void Game::update()
{
	// run implementation
	this->deltaTime = this->clock.restart().asSeconds();
	this->deltaTime = std::min(this->deltaTime, 0.1f);

	pollEvents();
	updateNotes();
}

void Game::renderJudgeLine()
{
	this->window->draw(this->judge_line);
}

void Game::renderNotes()
{
	for (auto& note : this->notes)
	{
		this->window->draw(note.shape);
	}
}

void Game::render()
{
	// clear the screen - default black
	this->window->clear(sf::Color::Black);

	// draw everything here...
	renderJudgeLine();
	renderNotes();

	// tell the window we're done drawing
	this->window->display();
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
