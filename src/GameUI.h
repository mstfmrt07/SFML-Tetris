#pragma once
#include "Tetrominoes.h"
#include "UI_Element.h"
#include "RoundedRectangleShape.hpp"
#include "GameData.h"

class GameUI : public UI_Element
{
public:
	GameUI();
	~GameUI();

	virtual void OnRender(RenderWindow& window) override;
	void SetNextShape(int nextFigureIndex, Texture& texture);
	void SetValues(GameDataRef gameData);

private:
	Font m_font;

	Text m_nextText;
    RoundedRectangleShape m_nextContainer;
    Tetromino m_nextShape;

    RoundedRectangleShape m_scoreContainer;
    RoundedRectangleShape m_levelContainer;
    RoundedRectangleShape m_linesContainer;
    Text m_levelText;
    Text m_scoreText;
    Text m_linesText;

};