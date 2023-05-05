#include "State.h"
#include "TetrisGame.h"
#include "Button.h"

class GameOverState : public State
{
public:
    GameOverState() = default;
    GameOverState(GameDataRef gameData);

    void Init() override;
    void Update(float& deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void ProcessEvent(Event& event) override;

private:
    GameDataRef m_data;

    Sprite m_background;
    Text m_gameOverText;
    Text m_levelText;
    Text m_linesText;
    Text m_scoreText;
    Button m_menuButton;
    Button m_playAgainButton;
};