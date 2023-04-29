#include "State.h"
#include "TetrisGame.h"

class GameOverState : public State
{
public:
    GameOverState() = default;
    GameOverState(GameDataRef gameData);

    void Init() override;
    void Update(float& deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    GameDataRef m_data;

    Text m_gameOverText;
    Text m_levelText;
    Text m_linesText;
    Text m_scoreText;
    Text m_menuText;
    Text m_playAgainText;
    Sprite m_background;
};