#pragma once
#include "Game.h"
#include "TetrisConfig.h"

const IntRect EmptyRect = IntRect(224, 0, 32, 32);

struct TetrisTile
{
public:
	TetrisTile() = default;
	~TetrisTile() = default;

	bool isOccupied = false;

	TetrisTile(const Vector2i& position, const Texture& texture, const IntRect& colorRect)
	{
		m_tileSize = tetris_config::tileSize;
		isOccupied = false;

		SetTexture(texture, colorRect);
		SetPosition(position);
	}

	void SetTexture(const Texture& texture, const IntRect& colorRect)
	{
		m_sprite = Sprite(texture, colorRect);
	}

	void SetColor(const Color& color)
	{
		m_sprite.setColor(color);
	}

	void SetPosition(const Vector2i& pos)
	{
		m_position = pos;
		m_sprite.setPosition(Vector2f(m_position) * m_tileSize);
	}

	void SetColorRect(const IntRect& colorRect)
	{
		m_sprite.setTextureRect(colorRect);
	}

	IntRect GetColorRect() const
	{
		return m_sprite.getTextureRect();
	}

	Vector2i GetPosition() const
	{
		return m_position;
	}

	Vector2f GetScale() const
	{
		return m_sprite.getScale();
	}

	void SetScaleFactor(float factor)
	{
		m_sprite.setScale(factor, factor);
	}

	void Draw(RenderWindow& window)
	{
		window.draw(m_sprite);
	}

private:
	Sprite m_sprite;
	Vector2i m_position;
	float m_tileSize = 100.f;
};