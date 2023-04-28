#include <SFML/Graphics.hpp>
#include "TetrisConfig.h"

class UI_Utility
{
public:
    static void AlignTextToCenter(sf::Text& text)
    {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top  + textRect.height / 2.0f);
    }
};