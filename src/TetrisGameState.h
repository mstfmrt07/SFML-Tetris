#include "State.h"
#include "TetrisConfig.h"
#include "Tetrominoes.h"
#include "GameData.h"
#include "GameUI.h"

using namespace sf;

const int rows = tetris_config::table_rows;
const int columns = tetris_config::table_columns;


class TetrisGameState : public State
{
public:
    TetrisGameState() = default;
    TetrisGameState(GameDataRef gameData);

    void Init() override;
    void ProcessEvent(sf::Event& event) override;
    void Update(float& deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void Pause() override;
    void Resume() override;

private:
    bool CheckCollision(std::vector<Vector2i> targetPoints);
    bool CheckGameOver();
    void MoveShape();
    void RotateShape();
    void SpawnShape();
    void PlaceShape();
    void HardDropShape();
    void CheckClearRows();
    void StartClearRow(int lineIndex);
    void EndClearRow(int lineIndex);
    void PlaceGhostShape();
    int RollDice();

    GameDataRef m_data;

    GameUI m_gameUI;

    TetrisTile m_tetrisTable[rows][columns];

    bool m_isPlaying = false;

    float m_fallTimer = 0.0f;
    float m_movementTimer = tetris_config::movement_threshold;
    float m_rotateTimer = tetris_config::rotate_threshold;
    float m_hardDropTimer = tetris_config::hard_drop_threshold;

    float m_clearTimer = 0.0f;
    bool m_isClearOnProcess = false;
    std::vector<int> m_rowsOnClearProcess;

    Tetromino m_currentShape;
    Tetromino m_currentGhost;
    bool m_ghostPositionFound = false;

    int m_nextFigureIndex = -1;
    std::vector<int> m_figuresBag; // Used to randomly pick the next figure.
};