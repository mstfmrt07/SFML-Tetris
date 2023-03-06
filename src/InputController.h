#pragma once
#include "Game.h"

using namespace sf;

class InputController
{
public:
	void OnProcessEvent(Event& event)
	{
        //Keyboard events
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
                horizontalInput = -1;
            else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
                horizontalInput = 1;

            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
                pressingDown = true;
            else
                pressingDown = false;

            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
                rotating = true;
            else
                rotating = false;
        }
        else //If there is no keyboard event
        {
            pressingDown = false;
            rotating = false;
            horizontalInput = 0;
        }
	}

    int horizontalInput = 0;
    bool pressingDown = false;
    bool rotating = false;
};