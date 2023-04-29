#include "GameUI.h"
#include <string>

GameUI::GameUI()
{
	//Load Font
	m_font.loadFromFile(tetris_config::font_path);

	//Init Next Shape Container
	m_nextContainer = RoundedRectangleShape(Vector2f(192, 192), 16.f, 8);
	m_nextContainer.setFillColor(tetris_config::container_color);
	m_nextContainer.setPosition(360, 28);

    //Init Next Shape Title
    m_nextText = Text("NEXT:", m_font, 24);
    m_nextText.setFillColor(tetris_config::secondary_text_color);
    m_nextText.setPosition(384, 36);

    //Init Level Container
    m_levelContainer = RoundedRectangleShape(Vector2f(192, 88), 16.f, 8);
    m_levelContainer.setFillColor(tetris_config::container_color);
    m_levelContainer.setPosition(360, 256);

    //Init Lines Container
    m_linesContainer = RoundedRectangleShape(Vector2f(192, 88), 16.f, 8);
    m_linesContainer.setFillColor(tetris_config::container_color);
    m_linesContainer.setPosition(360, 370);

	//Init Score Container
	m_scoreContainer = RoundedRectangleShape(Vector2f(192, 88), 16.f, 8);
	m_scoreContainer.setFillColor(tetris_config::container_color);
	m_scoreContainer.setPosition(360, 504);

    //Init Level Label
    m_levelText = Text("LEVEL: 1", m_font, 24);
    m_levelText.setFillColor(tetris_config::secondary_text_color);
    m_levelText.setPosition(384, 280);

    //Init Lines Label
    m_linesText = Text("SCORE: 0", m_font, 24);
    m_linesText.setFillColor(tetris_config::secondary_text_color);
    m_linesText.setPosition(384, 408);

    //Init Score Label
    m_scoreText = Text("SCORE: 0", m_font, 24);
    m_scoreText.setFillColor(tetris_config::secondary_text_color);
    m_scoreText.setPosition(384, 532);
}

GameUI::~GameUI() = default;

void GameUI::OnRender(RenderWindow& window)
{
	if (!GetVisible())
		return;

	window.draw(m_nextContainer);
    window.draw(m_nextText);
	window.draw(m_scoreContainer);
	window.draw(m_scoreText);
    window.draw(m_levelContainer);
	window.draw(m_levelText);
    window.draw(m_linesContainer);
    window.draw(m_linesText);

	m_nextShape.Draw(window);
}

void GameUI::SetNextShape(int nextFigureIndex, Texture& texture)
{
	m_nextShape = Tetromino(nextFigureIndex, Vector2i(13, 2), texture);
}

void GameUI::SetValues(GameDataRef gameData)
{
    m_levelText.setString("LEVEL: " + std::to_string(gameData->level));
    m_linesText.setString("LINES: " + std::to_string(gameData->lines));
    m_scoreText.setString("SCORE: " + std::to_string(gameData->score));
}