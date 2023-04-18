#include "GameOverUI.h"

GameOverUI::GameOverUI()
{
	//Load Font
	m_font.loadFromFile(tetris_config::font_path);

	//Init Container
	m_background = RectangleShape(Vector2f(640, 640));
	Color bgColor = tetris_config::foreground_color;
	bgColor.a = 200;
	m_background.setFillColor(bgColor);
	m_background.setPosition(0, 0);

	//Init Title
	m_gameOverText = Text("GAME OVER!", m_font, 32);
	m_gameOverText.setFillColor(tetris_config::background_color);
	m_gameOverText.setStyle(Text::Style::Bold);
	m_gameOverText.setPosition(240, 240);

	//Init Level Label
	m_levelText = Text("LEVEL: 1", m_font, 24);
	m_levelText.setFillColor(tetris_config::background_color);
	m_levelText.setPosition(240, 360);

	//Init Score Label
	m_scoreText = Text("SCORE: 0", m_font, 24);
	m_scoreText.setFillColor(tetris_config::background_color);
	m_scoreText.setPosition(240, 392);
}

GameOverUI::~GameOverUI() = default;

void GameOverUI::OnRender(RenderWindow& window)
{
	if (!GetVisible())
		return;

	window.draw(m_background);
	window.draw(m_gameOverText);
	window.draw(m_scoreText);
	window.draw(m_levelText);
}

void GameOverUI::SetValues(int& level, int& score)
{
	m_scoreText.setString("SCORE: " + std::to_string(score));
	m_levelText.setString("LEVEL: " + std::to_string(level));
}
