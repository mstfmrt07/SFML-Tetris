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

    m_playAgainText = Text("-PLAY AGAIN-", AssetManager::GetInstance()->GetFont("Default_Font"), 36);
    UI_Utility::AlignTextToCenter(m_playAgainText);
    m_playAgainText.setPosition(tetris_config::screen_width / 2.0f, 420.0f);
    m_playAgainText.setFillColor(tetris_config::primary_text_color);

    m_menuText = Text("-BACK TO MENU-", AssetManager::GetInstance()->GetFont("Default_Font"), 36);
    UI_Utility::AlignTextToCenter(m_menuText);
    m_menuText.setPosition(tetris_config::screen_width / 2.0f, 480.0f);
    m_menuText.setFillColor(tetris_config::primary_text_color);
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
    window.draw(m_playAgainText);
    window.draw(m_menuText);

    if(m_data->input.IsTextClicked(m_playAgainText, window))
    {
        std::cout << "Clicked on Play Again!" << std::endl;
        m_data->stateMachine.AddState(std::make_unique<TetrisGameState>(m_data), true);
    }

    if(m_data->input.IsTextClicked(m_menuText, window))
    {
        std::cout << "Clicked on Back to Menu!" << std::endl;
        m_data->stateMachine.RemoveState();
    }
}