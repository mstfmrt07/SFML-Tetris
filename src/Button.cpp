#include "Button.h"
#include "UI_Utility.h"

Button::Button(const std::string& label, const Font& font, const Vector2f& position, const Vector2f& size, const Color& color, const Color& textColor, unsigned int fontSize)
{
    m_fontSize = fontSize;
    m_position = position;
    m_size = size;

    m_rect = RoundedRectangleShape(size, 16.f, 8);
    m_rect.setFillColor(color);
    m_rect.setOrigin(m_size / 2.f);
    m_rect.setPosition(position);

    m_label = Text(label, font, fontSize);
    m_label.setFillColor(textColor);
    UI_Utility::AlignTextToCenter(m_label);
    m_label.setPosition(position);
}

void Button::Draw(RenderWindow &window)
{
    window.draw(m_rect);
    window.draw(m_label);
}

bool Button::IsClicked(const Event& event)
{
    m_clicked = false;

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left && !m_pressed)
        {
            if(m_rect.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                m_pressed = true;
                m_rect.setScale(0.9f, 0.9f);
                m_label.setScale(0.9f, 0.9f);
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == Mouse::Left && m_pressed)
        {
            m_pressed = false;
            m_rect.setScale(1.f, 1.f);
            m_label.setScale(1.f, 1.f);

            if(m_rect.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                m_clicked = true;
        }
    }
    return m_clicked;
}

void Button::SetFontSize(unsigned int fontSize)
{
    m_label.setCharacterSize(fontSize);
    UI_Utility::AlignTextToCenter(m_label);
}

void Button::SetPosition(const Vector2f &position)
{
    m_rect.setPosition(position);
    m_label.setPosition(position);
}

void Button::SetLabel(const std::string &label)
{
    m_label.setString(label);
    UI_Utility::AlignTextToCenter(m_label);
}
