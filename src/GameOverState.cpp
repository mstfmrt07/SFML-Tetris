#include "GameOverState.h"
#include "TetrisConfig.h"
#include "TetrisGameState.h"
#include "UI_Utility.h"
#include "AssetManager.h"

GameOverState::GameOverState(GameDataRef gameData) : m_data(gameData){}

void GameOverState::Init()
{
    //Init Container
    m_background = Sprite(AssetManager::GetInstance()->GetTexture("Main_BG"));
    m_background.setPosition(0.f, 0.f);

    //Init Title
    m_gameOverText = Text("GAME OVER!", AssetManager::GetInstance()->GetFont("Default_Font"), 54);
    UI_Utility::AlignTextToCenter(m_gameOverText);
    m_gameOverText.setPosition(tetris_config::screen_width / 2.0f, 180);
    m_gameOverText.setFillColor(tetris_config::primary_text_color);
    m_gameOverText.setStyle(Text::Style::Bold);

    //Init Level Label
    m_levelText = Text("LEVEL: " + std::to_string(m_data->level), AssetManager::GetInstance()->GetFont("Default_Font"), 32);
    UI_Utility::AlignTextToCenter(m_levelText);
    m_levelText.setPosition(tetris_config::screen_width / 2.0f, 240);
    m_levelText.setFillColor(tetris_config::primary_text_color);

    //Init Lines Label
    m_linesText = Text("LINES: " + std::to_string(m_data->lines), AssetManager::GetInstance()->GetFont("Default_Font"), 32);
    UI_Utility::AlignTextToCenter(m_linesText);
    m_linesText.setPosition(tetris_config::screen_width / 2.0f, 280);
    m_linesText.setFillColor(tetris_config::primary_text_color);

    //Init Score Label
    m_scoreText = Text("SCORE: " + std::to_string(m_data->score), AssetManager::GetInstance()->GetFont("Default_Font"), 32);
    UI_Utility::AlignTextToCenter(m_scoreText);
    m_scoreText.setPosition(tetris_config::screen_width / 2.0f, 320);
    m_scoreText.setFillColor(tetris_config::primary_text_color);

    m_playAgainButton = Button("PLAY AGAIN", AssetManager::GetInstance()->GetFont("Default_Font"), Vector2f(tetris_config::screen_width / 2.0f, 420.0f), Vector2f(256.f, 64.f));
    m_playAgainButton.SetFontSize(28);

    m_menuButton = Button(m_playAgainButton);
    m_menuButton.SetPosition(Vector2f(tetris_config::screen_width / 2.0f, 496.0f));
    m_menuButton.SetLabel("BACK TO MENU");
}

void GameOverState::Update(float &deltaTime)
{
}

void GameOverState::Render(sf::RenderWindow &window)
{
    window.draw(m_background);
    window.draw(m_gameOverText);
    window.draw(m_scoreText);
    window.draw(m_levelText);
    window.draw(m_linesText);

    m_playAgainButton.Draw(window);
    m_menuButton.Draw(window);
}

void GameOverState::ProcessEvent(Event &event)
{
    State::ProcessEvent(event);
    if(m_playAgainButton.IsClicked(event))
    {
        std::cout << "Clicked on Play Again!" << std::endl;
        m_data->stateMachine.AddState(std::make_unique<TetrisGameState>(m_data), true);
    }

    if(m_menuButton.IsClicked(event))
    {
        std::cout << "Clicked on Back to Menu!" << std::endl;
        m_data->stateMachine.RemoveState();
    }
}
