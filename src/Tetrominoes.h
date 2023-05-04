#pragma once
#include "TetrisTile.h"

struct Tetromino
{
	Tetromino() = default;
	~Tetromino() = default;

	Tetromino(const int& figureIndex, const Vector2i& position, const Texture& texture)
	{
		m_figure = tetris_config::Figures[figureIndex];
        const int& tileSize = tetris_config::tileSize;
		m_position = position;

		//Create tiles.
		for (int i = 0; i < 4; i++)
		{
			Vector2i tilePos(position.x + (m_figure.points[i] % 4), position.y + (m_figure.points[i] / 4));
			m_tiles[i] = TetrisTile(tilePos, texture, IntRect(tileSize * figureIndex, 0, tileSize, tileSize));
		}
	}

	void SetPosition(const Vector2i& pos)
	{
		Vector2i diff = pos - m_position;
		m_position = pos;

		for (int i = 0; i < 4; i++)
		{
			m_tiles[i].SetPosition(m_tiles[i].GetPosition() + diff);
		}
	}

	Vector2i GetPosition() const
	{
		return m_position;
	}

	void Move(const Vector2i& movement)
	{
		SetPosition(m_position + movement);
	}

	void Rotate()
	{
        std::vector<Vector2i> simulatedPoints = SimulateRotation();
		for (int i = 0; i < 4; i++)
		{
			m_tiles[i].SetPosition(simulatedPoints[i]);
		}
	}

    std::vector<Vector2i> SimulateRotation()
	{
		Vector2i origin = m_tiles[2].GetPosition();
        std::vector<Vector2i> points;
		for (int i = 0; i < 4; i++)
		{
			Vector2i newPos(origin.x - (m_tiles[i].GetPosition().y - origin.y), origin.y + (m_tiles[i].GetPosition().x - origin.x));
            points.push_back(newPos);
		}
		return points;
	}

    std::vector<Vector2i> SimulateMovement(const Vector2i& movementVector)
	{
        std::vector<Vector2i> points;

		for (int i = 0; i < 4; i++)
		{
			points.push_back(m_tiles[i].GetPosition() + movementVector);
		}
		return points;
	}

	IntRect GetColorRect() const
	{
		return m_tiles[0].GetColorRect();
	}

	Figure GetFigure() const
	{
		return m_figure;
	}

	TetrisTile* GetTiles()
	{
		return m_tiles;
	}

    std::vector<Vector2i>GetPositionArray() const
	{
        std::vector<Vector2i> points;

		for (int i = 0; i < 4; i++)
		{
            points.push_back(m_tiles[i].GetPosition());
		}
		return points;
	}

	void SetTexture(const Texture& texture, const IntRect& colorRect)
	{
		for (int i = 0; i < 4; i++)
		{
			m_tiles[i].SetTexture(texture, colorRect);
		}
	}

    void SetColorRect(const IntRect& colorRect)
    {
        for (int i = 0; i < 4; i++)
        {
            m_tiles[i].SetColorRect(colorRect);
        }
    }

	void Draw(RenderWindow& window)
	{
		for (int i = 0; i < 4; i++)
		{
			m_tiles[i].Draw(window);
		}
	}

private:
	Figure m_figure;
	TetrisTile m_tiles[4];
	Vector2i m_position;
};