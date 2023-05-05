#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"
#include "TetrisConfig.h"

using namespace sf;

class Button
{
public:
    Button() = default;
    ~Button() = default;

    Button(const std::string& label, const Font& font, const Vector2f& position, const Vector2f& size, const Color& color = tetris_config::container_color, const Color& textColor = tetris_config::secondary_text_color, unsigned int fontSize = 24);
    void SetFontSize(unsigned int fontSize);
    void SetPosition(const Vector2f& position);
    void SetLabel(const std::string& label);
    void Draw(RenderWindow& window);
    bool IsClicked(const Event& event);

private:
    bool m_pressed = false;
    bool m_clicked = false;
    RoundedRectangleShape m_rect;
    Text m_label;
    Vector2f m_position;
    Vector2f m_size;
    unsigned int m_fontSize;
};
