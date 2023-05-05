#include "State.h"
#include "TetrisGame.h"
#include "Button.h"

class MainMenuState : public State
{
public:
    MainMenuState() = default;
    MainMenuState(GameDataRef gameData);

    void Init() override;
    void Update(float& deltaTime) override;
    void Render(RenderWindow& window) override;
    void ProcessEvent(Event& event) override;

private:
    GameDataRef m_data;

    Sprite m_mainBG;
    Text m_titleText;
    Button m_playButton;
    Button m_quitButton;
};