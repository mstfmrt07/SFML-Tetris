#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class UI_Element
{
public:
	virtual void OnRender(RenderWindow& window) = 0;

	void SetVisible(bool value)
	{
		m_visible = value;
	}

	bool GetVisible() const
	{
		return m_visible;
	}

private:
	bool m_visible = true;
};