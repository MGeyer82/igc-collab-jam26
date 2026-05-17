#pragma once

#include "Game.h"

// Layout positions and sizes

// -- Border Edge --
float border_edge_size;

// -- Rhythm Bar --
sf::Vector2f rhythm_bar_size;
sf::Vector2f rhythm_bar_pos;

// -- Judge Line --
sf::Vector2f judge_line_pos;

// -- Pause Menu --
sf::Vector2f pause_menu_size;
sf::Vector2f pause_menu_pos;

// -- Note Props --
sf::Vector2f note_size;
sf::Vector2f note_spawn_pos;

// -- Player --
sf::Vector2f player_size;
sf::Vector2f player_pos;

// -- Enemy --
sf::Vector2f enemy_spawn_pos;

void Game::initProps()
{
	// game dimensions
	border_edge_size = 25.f;
	rhythm_bar_size = { 1230.f, 175.f };
	rhythm_bar_pos = { border_edge_size, game_size.y - border_edge_size - rhythm_bar_size.y };

	// Notes
	note_size = { 5.f, 90.f };
	note_spawn_pos = { game_size.x - border_edge_size - note_size.x,
				   game_size.y - border_edge_size - (rhythm_bar_size.y / 2.f) - (note_size.y / 2.f) };

	// Judge Line
	judge_line_pos = { border_edge_size + 50.f, note_spawn_pos.y };

	// Player
	player_size = { 250.f, 450.f };
	player_pos = { judge_line_pos.x, game_size.y - border_edge_size - rhythm_bar_size.y - 50.f };

	// Enemy
	enemy_spawn_pos = { game_size.x, player_pos.y + (player_size.y / 2) };
}