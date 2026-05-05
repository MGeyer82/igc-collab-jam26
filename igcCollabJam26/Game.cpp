#include "Game.h"

/**
*	Game class constructor / destructor
*/
Game::Game()
{
	loadTextures();

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

		// TODO: Get this to trigger once per key press and fix note fade
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			this->pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);;

			if (this->pressed && !this->was_pressed)
			{
				//// enlarge notes while adjusting transparency to indicate note hit
				//float noteFadeTimer = 0.f;

				//if (noteFadeTimer < 60.f)
				//{
				//	noteFadeTimer += 1.f;
				//	this->notes.front().setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(255 - (noteFadeTimer * 2.f))));
				//	this->notes.front().setSize(this->note_size + sf::Vector2f(noteFadeTimer, noteFadeTimer));
				//}

				std::cout << "Pressed space!" << std::endl;

				// then pop the note from the vector...
				if (!notes.empty())
				this->notes.erase(this->notes.begin());
			}

			this->was_pressed = this->pressed;
		}
	}
}

void Game::spawnNote()
{
	this->note.setPosition(this->note_spawn_position);
	this->note.setFillColor(sf::Color::Red);
	this->note.setSize(this->note_size);

	this->notes.push_back(this->note);
}

void Game::updateNotes()
{
	//std::cout << this->noteSpawnTimer << std::endl;

	if (this->noteSpawnTimer >= this->noteSpawnTimerMax)
	{
		spawnNote();
		this->noteSpawnTimer = 0.f;
	}
	else
	{
		this->noteSpawnTimer += 1.f;
	}

	for (auto& note : this->notes)
	{
		note.move( { -5.f, 0.f } );
	}
}

void Game::update()
{
	// run implementation
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
		this->window->draw(note);
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

void Game::throwError(const std::string& message, std::optional<std::string> path) const
{
	std::cerr << "Error: " << message;
	if (path)
	{
		std::cerr << " Path: " << *path;
	}
	std::cerr << std::endl;
}
