#pragma once
#include "UI_Element.h"
#include "TetrisConfig.h"

class GameOverUI : public UI_Element
{
public:
	GameOverUI();
	~GameOverUI();

	virtual void OnRender(RenderWindow& window) override;
	void SetValues(int& level, int& score);

private:
	Font m_font;
	Text m_gameOverText;
	Text m_levelText;
	Text m_scoreText;
	RectangleShape m_background;
};