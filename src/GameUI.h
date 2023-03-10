#pragma once
#include "Tetrominoes.h"
#include "UI_Element.h"

class GameUI : public UI_Element
{
public:
	GameUI();
	~GameUI();

	virtual void OnRender(RenderWindow& window) override;
	void SetNextShape(int nextFigureIndex, Texture& texture);
	void SetValues(int& level, int& score);

private:
	Font m_font;
	Text m_nextText;
	Text m_levelText;
	Text m_scoreText;
	RectangleShape m_nextContainer;
	RectangleShape m_scoreContainer;
	Tetromino m_nextShape;
};