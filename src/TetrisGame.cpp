#include "TetrisGame.h"
#include "MainMenuState.h"

void TetrisGame::OnInit()
{
    m_data = std::make_shared<GameData>();
    m_data->stateMachine.AddState(std::make_unique<MainMenuState>(m_data), true);
}

void TetrisGame::OnUpdate(float deltaTime)
{
    m_data->stateMachine.Update();
    m_data->stateMachine.GetActiveState()->Update(deltaTime);
}

void TetrisGame::OnRender(RenderWindow& window)
{
    m_data->stateMachine.GetActiveState()->Render(window);
}

void TetrisGame::OnProcessEvent(Event& event)
{
    m_data->input.OnProcessEvent(event);
    m_data->stateMachine.GetActiveState()->ProcessEvent(event);
}

void TetrisGame::OnDestroy()
{
}

void TetrisGame::OnPause()
{
    m_data->stateMachine.GetActiveState()->Pause();
}

void TetrisGame::OnResume()
{
    m_data->stateMachine.GetActiveState()->Resume();
}


