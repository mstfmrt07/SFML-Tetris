#pragma once
#include <SFML/Graphics.hpp>

struct Figure
{
	int points[4] = { 0 };
};

namespace tetris_config
{
	//Game and Asset Constants
	const std::string game_title = "Tetris Game";
	const std::string texture_path = "assets/tetris-tileset-v2.png";
	const std::string font_path = "assets/tetris-font.ttf";

	const sf::Color background_color = Color::White;
	const sf::Color foreground_color = Color(38, 43, 57, 255);

	//A classical tetris board consists of 20 rows and 10 columns.
	const int table_rows = 20;
	const int table_columns = 10;

	//Size of an individual tile (in pixels)
	const float tileSize = 32.0f;

	//Amount of time between two consecutive moves on the horizontal axis. (Seconds)
	const float movement_threshold = 0.05f;

	//Amount of time for a tetris piece to move one block down. (Seconds)
	const float fall_threshold = 0.6f;

	//Horizontal movement time threshold. (Seconds)
	const float rotate_threshold = 0.2f;

	//Defines how fast will a tetris piece would fall when the "soft drop" key is pressed.
	const float fast_fall_factor = 15.f;

	const int figure_count = 7;

	//Point indexes indicate the values from 0 (Top-Left) to 7 (Bottom-Right) in the 2x4 grid.
	const Figure Figures[figure_count] =
	{
		///  I-Shape
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		Figure({ 1,3,5,7 }),

		///  O-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ▄▄▄▄ ▄▄▄▄ 
		/// ▀▀▀▀ ▀▀▀▀ 
		/// ▄▄▄▄ ▄▄▄▄ 
		/// ▀▀▀▀ ▀▀▀▀ 
		/// ┌───┐┌───┐
		/// └───┘└───┘
		Figure({ 2,3,4,5 }),

		///  T-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ▄▄▄▄  ▄▄▄▄ 
		/// ▀▀▀▀  ▀▀▀▀ 
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		Figure({ 3,5,4,7 }),

		///  S-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ▄▄▄▄ ┌───┐
		/// ▀▀▀▀ └───┘
		/// ▄▄▄▄  ▄▄▄▄ 
		/// ▀▀▀▀  ▀▀▀▀ 
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		Figure({ 2,4,5,7 }),

		///  Z-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ▄▄▄▄  ▄▄▄▄ 
		/// ▀▀▀▀  ▀▀▀▀ 
		/// ▄▄▄▄ ┌───┐
		/// ▀▀▀▀ └───┘
		Figure({ 3,5,4,6 }),

		///  J-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ┌───┐ ▄▄▄▄
		/// └───┘ ▀▀▀▀
		/// ▄▄▄▄  ▄▄▄▄ 
		/// ▀▀▀▀  ▀▀▀▀ 
		Figure({ 3,5,7,6 }),

		///  L-Shape
		/// ┌───┐┌───┐
		/// └───┘└───┘
		/// ▄▄▄▄ ┌───┐
		/// ▀▀▀▀ └───┘
		/// ▄▄▄▄ ┌───┐
		/// ▀▀▀▀ └───┘
		/// ▄▄▄▄  ▄▄▄▄ 
		/// ▀▀▀▀  ▀▀▀▀ 
		Figure({ 2,3,5,7 }),
	};
}