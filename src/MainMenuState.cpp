#include "MainMenuState.h"
#include "TetrisGameState.h"
#include "UI_Utility.h"
#include "AssetManager.h"

MainMenuState::MainMenuState(GameDataRef gameData) : m_data(gameData){}

void MainMenuState::Init()
{
    AssetManager::GetInstance()->LoadFont("Default_Font", tetris_config::font_path);
    AssetManager::GetInstance()->LoadTexture("Main_BG", tetris_config::main_bg_path);

    m_mainBG = Sprite(AssetManager::GetInstance()->GetTexture("Main_BG"));
    m_mainBG.setPosition(0.f, 0.f);

    m_titleText = Text("TETRIS", AssetManager::GetInstance()->GetFont("Default_Font"), 80);
    UI_Utility::AlignTextToCenter(m_titleText);
    m_titleText.setPosition(tetris_config::screen_width / 2.0f, 200.0f);
    m_titleText.setFillColor(tetris_config::primary_text_color);
    m_titleText.setStyle(Text::Style::Bold);

    m_playButton = Button("PLAY", AssetManager::GetInstance()->GetFont("Default_Font"), Vector2f(tetris_config::screen_width / 2.0f, 360.0f), Vector2f(192.f, 64.f));
    m_playButton.SetFontSize(42);

    m_quitButton = Button(m_playButton);
    m_quitButton.SetPosition(Vector2f(tetris_config::screen_width / 2.0f, 440.0f));
    m_quitButton.SetLabel("QUIT");
}

void MainMenuState::Update(float &deltaTime)
{
}

void MainMenuState::Render(RenderWindow &window)
{
    window.draw(m_mainBG);
    window.draw(m_titleText);
    m_playButton.Draw(window);
    m_quitButton.Draw(window);
}

void MainMenuState::ProcessEvent(Event &event)
{
    State::ProcessEvent(event);
    if(m_playButton.IsClicked(event))
    {
        std::cout << "Clicked on Play Game!" << std::endl;
        m_data->stateMachine.AddState(std::make_unique<TetrisGameState>(m_data), false);
    }

    if(m_quitButton.IsClicked(event))
    {
        //TODO: Quit Game
        std::cout << "Clicked on Quit Game!" << std::endl;
    }
}
