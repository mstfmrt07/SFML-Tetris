#include "State.h"
#include "TetrisGame.h"

class MainMenuState : public State
{
public:
    MainMenuState() = default;
    MainMenuState(GameDataRef gameData);

    void Init() override;
    void Update(float& deltaTime) override;
    void Render(RenderWindow& window) override;

private:
    GameDataRef m_data;

    Sprite m_mainBG;
    Text m_titleText;
    Text m_playText;
    Text m_quitText;
};