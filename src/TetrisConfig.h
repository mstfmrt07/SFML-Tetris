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

    const std::string assetsPath = "../../assets/";
	const std::string texture_path = assetsPath + "tetris-tileset.png";
    const std::string icon_path = assetsPath + "game-icon.png";
	const std::string font_path = assetsPath + "tetris-font.ttf";

    const std::string line_clear_sound = assetsPath + "line-clear.wav";
    const std::string rotate_sound = assetsPath + "rotate.wav";
    const std::string move_sound = assetsPath + "move.wav";
    const std::string place_sound = assetsPath + "place.wav";

	const sf::Color background_color = sf::Color::White;
	const sf::Color foreground_color = sf::Color(38, 43, 57, 255);

	//A classical tetris board consists of 20 rows and 10 columns.
	const int table_rows = 20;
	const int table_columns = 10;

	//Size of an individual tile (in pixels)
	const float tileSize = 32.0f;

	//Amount of time between two consecutive moves on the horizontal axis. (Seconds)
	const float movement_threshold = 0.1f;

	//Amount of time for a tetris piece to move one block down. (Seconds)
	const float fall_threshold = 0.6f;

	//Amount of time between two consecutive rotates. (Seconds)
	const float rotate_threshold = 0.2f;

    //Amount of time between two consecutive hard drops. (Seconds)
    const float hard_drop_threshold = 0.4f;

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