﻿#pragma once
#include <SFML/Graphics.hpp>

struct Figure
{
	int points[4] = { 0 };
};

namespace tetris_config
{
	//Game and Asset Constants
	const std::string game_title = "Tetris Game";

    const std::string assetsPath = "../assets/";
	const std::string texture_path = assetsPath + "tetris-tileset.png";
    const std::string icon_path = assetsPath + "game-icon.png";
    const std::string main_bg_path = assetsPath + "tetris-main.png";
	const std::string font_path = assetsPath + "tetris-font.ttf";

    const std::string line_clear_sound = assetsPath + "line-clear.wav";
    const std::string rotate_sound = assetsPath + "rotate.wav";
    const std::string move_sound = assetsPath + "move.wav";
    const std::string place_sound = assetsPath + "place.wav";

	const sf::Color background_color = sf::Color(132, 132, 132, 255);
	const sf::Color container_color = sf::Color(31, 31, 31, 255);
    const sf::Color primary_text_color = sf::Color(31, 31, 31, 255);
    const sf::Color secondary_text_color = sf::Color(229, 229, 229, 255);

    //Sprite rects in texture
    const sf::IntRect EmptyRect = sf::IntRect(224, 0, 32, 32);
    const sf::IntRect ClearRect = sf::IntRect(224, 32, 32, 32);

    //Width and height of the screen.
    const int screen_width = 640;
    const int screen_height = 640;

	//A classical tetris board consists of 20 rows and 10 columns.
	const int table_rows = 20;
	const int table_columns = 10;

	//Size of an individual tile (in pixels)
	const int tileSize = 32;

	//Time between two consecutive moves on the horizontal axis. (Seconds)
	const float movement_threshold = 0.1f;

	//Time for a tetris piece to move one block down. (Seconds)
	const float fall_threshold = 0.8f;

	//Time between two consecutive rotates. (Seconds)
	const float rotate_threshold = 0.2f;

    //Time between two consecutive hard drops. (Seconds)
    const float hard_drop_threshold = 0.4f;

	//Defines how fast will a tetris piece would fall when the "soft drop" key is pressed.
	const float fast_fall_factor = 8.0f;

    const float line_clear_effect_duration = 0.2f;

    const int score_per_row = 100;

	const int figure_count = 7;
	//Point indexes indicate the values from 0 (Top-Left) to 7 (Bottom-Right) in the 2x4 grid.
	const Figure Figures[figure_count] =
	{
        ///  I-Shape
        /// ┌───┐┌───┐┌───┐┌───┐
        /// └───┘└───┘└───┘└───┘
        /// ▄▄▄▄ ▄▄▄▄ ▄▄▄▄ ▄▄▄▄
        /// ▀▀▀▀ ▀▀▀▀ ▀▀▀▀ ▀▀▀▀
		Figure({{ 4,5,6,7 }}),

		///  O-Shape
        /// ┌───┐▄▄▄▄ ▄▄▄▄┌───┐
        /// └───┘▀▀▀▀ ▀▀▀▀└───┘
        /// ┌───┐▄▄▄▄ ▄▄▄▄┌───┐
        /// └───┘▀▀▀▀ ▀▀▀▀└───┘
		Figure({{ 1,2,5,6 }}),

		///  T-Shape
        /// ┌───┐▄▄▄▄┌───┐┌───┐
        /// └───┘▀▀▀▀└───┘└───┘
        /// ▄▄▄▄ ▄▄▄▄ ▄▄▄▄┌───┐
        /// ▀▀▀▀ ▀▀▀▀ ▀▀▀▀└───┘
		Figure({{ 1,4,5,6 }}),

		///  S-Shape
        /// ┌───┐▄▄▄▄ ▄▄▄▄┌───┐
        /// └───┘▀▀▀▀ ▀▀▀▀└───┘
        /// ▄▄▄▄ ▄▄▄▄┌───┐┌───┐
        /// ▀▀▀▀ ▀▀▀▀└───┘└───┘
		Figure({{ 1,2,5,4 }}),

		///  Z-Shape
        /// ▄▄▄▄ ▄▄▄▄┌───┐┌───┐
        /// ▀▀▀▀ ▀▀▀▀└───┘└───┘
        /// ┌───┐▄▄▄▄ ▄▄▄▄┌───┐
        /// └───┘▀▀▀▀ ▀▀▀▀└───┘
		Figure({{ 0,1,5,6 }}),

		///  J-Shape
        /// ▄▄▄▄┌───┐┌───┐┌───┐
        /// ▀▀▀▀└───┘└───┘└───┘
        /// ▄▄▄▄ ▄▄▄▄ ▄▄▄▄┌───┐
        /// ▀▀▀▀ ▀▀▀▀ ▀▀▀▀└───┘
		Figure({{ 0,4,5,6 }}),

		///  L-Shape
        /// ┌───┐┌───┐┌───┐▄▄▄▄
        /// └───┘└───┘└───┘▀▀▀▀
        /// ┌───┐▄▄▄▄ ▄▄▄▄ ▄▄▄▄
        /// └───┘▀▀▀▀ ▀▀▀▀ ▀▀▀▀
		Figure({{ 3,5,6,7 }}),
	};
}