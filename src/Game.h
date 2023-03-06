#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Game
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief OnInit
    ///
    /// is called at the time a game is initialized.
    ///
    ////////////////////////////////////////////////////////////
	virtual void OnInit() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief OnUpdate
    ///
    /// is called every frame.
    /// \param deltaTime    the time passed between two frames. (in seconds)
    ///
    ////////////////////////////////////////////////////////////
	virtual void OnUpdate(float deltaTime) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief OnRender
    ///
    /// is used to render objects on the screen.
    /// \param window    SFML Window is required to draw objects.
    ///
    ////////////////////////////////////////////////////////////
	virtual void OnRender(RenderWindow& window) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief OnProcessEvent
    ///
    /// is used to handle captured events such as Keyboard, Touch, Joystick or Mouse events.
    /// \param event    SFML Event is required to handle events.
    ///
    ////////////////////////////////////////////////////////////
	virtual void OnProcessEvent(Event& event) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief OnDestroy
    ///
    /// is called when a game is shut down.
    ///
    ////////////////////////////////////////////////////////////
	virtual void OnDestroy() = 0;
};