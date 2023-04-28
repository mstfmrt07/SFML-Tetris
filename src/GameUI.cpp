#include "GameUI.h"
#include <string>

GameUI::GameUI()
{
	//Load Font
	m_font.loadFromFile(tetris_config::font_path);

	//Init Next Shape Container
	m_nextContainer = RoundedRectangleShape(Vector2f(192, 192), 16.f, 8);
	m_nextContainer.setFillColor(tetris_config::container_color);
	m_nextContainer.setPosition(360, 120);

	//Init Score Container
	m_scoreContainer = RoundedRectangleShape(Vector2f(192, 88), 16.f, 8);
	m_scoreContainer.setFillColor(tetris_config::container_color);
	m_scoreContainer.setPosition(360, 388);

	//Init Next Shape Title
	m_nextText = Text("NEXT:", m_font, 20);
	m_nextText.setFillColor(tetris_config::secondary_text_color);
	m_nextText.setPosition(384, 128);

	//Init Level Label
	m_levelText = Text("LEVEL: 1", m_font, 20);
	m_levelText.setFillColor(tetris_config::secondary_text_color);
	m_levelText.setPosition(384, 400);

	//Init Score Label
	m_scoreText = Text("SCORE: 0", m_font, 20);
	m_scoreText.setFillColor(tetris_config::secondary_text_color);
	m_scoreText.setPosition(384, 432);
}

GameUI::~GameUI() = default;

void GameUI::OnRender(RenderWindow& window)
{
	if (!GetVisible())
		return;

	window.draw(m_nextContainer);
	window.draw(m_scoreContainer);
	window.draw(m_nextText);
	window.draw(m_scoreText);
	window.draw(m_levelText);

	m_nextShape.Draw(window);
}

void GameUI::SetNextShape(int nextFigureIndex, Texture& texture)
{
	m_nextShape = Tetromino(nextFigureIndex, Vector2i(13, 5), texture);
}

void GameUI::SetValues(int& level, int& score)
{
	m_scoreText.setString("SCORE: " + std::to_string(score));
	m_levelText.setString("LEVEL: " + std::to_string(level));
}