#pragma once
#include "GameData.h"

class TetrisGame : public Game
{
public:
    void OnInit() override;
    void OnUpdate(float deltaTime) override;
    void OnRender(RenderWindow& window) override;
    void OnProcessEvent(Event& event) override;
    void OnDestroy() override;
    void OnPause() override;
    void OnResume() override;

private:
    GameDataRef m_data;
};