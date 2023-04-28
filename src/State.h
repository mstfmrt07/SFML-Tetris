#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
    virtual ~State() = default;

    virtual void Init() = 0;
    virtual void ProcessEvent(sf::Event& event) {}
    virtual void Update(float& deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void Pause() {};
    virtual void Resume() {};
};