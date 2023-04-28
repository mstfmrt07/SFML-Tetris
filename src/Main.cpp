#include "TetrisGame.h"

//The entry point to any game. Usually you wouldn't need to alter this code.
//However, window size, title, background color and framerate limit can be changed.
int main()
{
    //Init the window.
    RenderWindow window(VideoMode(tetris_config::screen_width, tetris_config::screen_height), tetris_config::game_title);
    window.setFramerateLimit(60);

    //Set the window icon.
    sf::Image icon;
    if(icon.loadFromFile(tetris_config::icon_path))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (std::unique_ptr<Game> game = std::make_unique<TetrisGame>())
    {
        //Init the game.
        game->OnInit();

        Clock clock;

        //Game loop.
        while (window.isOpen())
        {
            //Calculate Delta time
            float deltaTime = clock.getElapsedTime().asSeconds();
            clock.restart();

            //Events
            Event event;
            while (window.pollEvent(event))
            {
                //Catch the close events.
                if (event.type == sf::Event::Closed)
                    window.close();

                //Catch the resize events.
                if (event.type == sf::Event::Resized)
                {
                    //Update the view to the new size of the window.
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }

                //Handle window focus changes.
                if (event.type == sf::Event::LostFocus)
                    game->OnPause();

                if (event.type == sf::Event::GainedFocus)
                    game->OnResume();

                //Process Game Events
                game->OnProcessEvent(event);
            }

            window.clear(tetris_config::secondary_text_color);

            //Update the game and display it on the screen.
            game->OnUpdate(deltaTime);
            game->OnRender(window);

            window.display();
        }

        //Destroy the game.
        game->OnDestroy();
        return 0;
    }
    return -1;
}