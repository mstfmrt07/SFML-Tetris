#pragma once
#include "Game.h"

using namespace sf;

class InputManager
{
public:
	void OnProcessEvent(Event& event)
	{
        //Keyboard events
        if (event.type == Event::KeyPressed)
            HandleKeyPressed(event.key.code);
        else if(event.type == Event::KeyReleased)
            HandleKeyReleased(event.key.code);
	}

    bool IsTextClicked(sf::Text& text, sf::RenderWindow& window )
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Vector2i mousePos = sf::Mouse::getPosition(window);
            if(text.getGlobalBounds().contains(mousePos.x, mousePos.y))
                return true;
        }
        return false;
    }

    int horizontalInput = 0;
    bool hardDrop = false;
    bool pressingDown = false;
    bool rotating = false;

private:
    void HandleKeyPressed(Keyboard::Key& key)
    {
        if (key == Keyboard::Left || key == Keyboard::A)
            horizontalInput = -1;
        else if (key == Keyboard::Right || key == Keyboard::D)
            horizontalInput = 1;

        if (key == Keyboard::Down || key == Keyboard::S)
            pressingDown = true;

        if (key == Keyboard::Up || key == Keyboard::W)
            rotating = true;

        if (key == Keyboard::Space)
            hardDrop = true;
    }

    void HandleKeyReleased(Keyboard::Key& key)
    {
        if (key == Keyboard::Left || key == Keyboard::A || key == Keyboard::Right || key == Keyboard::D)
            horizontalInput = 0;

        if (key == Keyboard::Down || key == Keyboard::S)
            pressingDown = false;

        if (key == Keyboard::Up || key == Keyboard::W)
            rotating = false;

        if (key == Keyboard::Space)
            hardDrop = false;
    }
};