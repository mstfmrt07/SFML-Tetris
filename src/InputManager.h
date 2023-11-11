#pragma once
#include "Game.h"
#include "Action.h"

using namespace sf;

class InputManager
{
public:
    void OnProcessEvent(Event &event)
    {
        //Mouse events
        if (event.type == Event::MouseButtonPressed)
        {
            MouseClicked.Notify(Vector2i(event.mouseButton.x, event.mouseButton.y));
        }

        //Text events
        if (event.type == Event::TextEntered)
        {
            CharEntered.Notify(event.text.unicode);
        }

        //Keyboard events
        if (event.type == Event::KeyPressed)
        {
            bool isMovementEvent = true;

            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
                m_horizontalMovement = -1;
            else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
                m_horizontalMovement = 1;
            else
                isMovementEvent = false;

            if (isMovementEvent)
                Moved.Notify(m_horizontalMovement);

            KeyPressed.Notify(event.key.code);
        }
        else if (event.type == Event::KeyReleased)
        {
            bool isMovementEvent = true;

            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
                m_horizontalMovement = 0;
            else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
                m_horizontalMovement = 0;
            else
                isMovementEvent = false;

            if (isMovementEvent)
                Moved.Notify(m_horizontalMovement);

            KeyReleased.Notify(event.key.code);
        }
    }

    Action<int> Moved;
    Action<Keyboard::Key> KeyPressed;
    Action<Keyboard::Key> KeyReleased;
    Action<Uint32> CharEntered;
    Action<Vector2i> MouseClicked;

private:
    int m_horizontalMovement = 0;
};