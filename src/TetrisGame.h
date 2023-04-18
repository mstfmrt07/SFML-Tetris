#pragma once
#include "Tetrominoes.h"
#include "GameUI.h"
#include "InputController.h"
#include "GameOverUI.h"
#include "SoundManager.h"

const int rows = tetris_config::table_rows;
const int columns = tetris_config::table_columns;

class TetrisGame : public Game
{
public:
    void OnInit() override;
    void OnUpdate(float deltaTime) override;
    void OnRender(RenderWindow& window) override;
    void OnProcessEvent(Event& event) override;
    void OnDestroy() override;

private:
    bool CheckCollision(std::vector<Vector2i> targetPoints);
    bool CheckGameOver();
    void MoveShape();
    void RotateShape();
    void SpawnShape();
    void PlaceShape();
    void CheckClearLines();
    void ClearLine(int lineIndex);
    void PlaceGhostShape();

    InputController m_input;
    SoundManager m_soundManager;
    GameUI m_gameUI;
    GameOverUI m_gameOverUI;

    Texture m_texture;

    TetrisTile m_tetrisTable[rows][columns];

    int m_level = 0;
    int m_score = 0;

    float m_fallTimer = 0.f;
    float m_movementTimer = 0.f;
    float m_rotateTimer = 0.f;

    Tetromino m_currentShape;
    Tetromino m_currentGhost;
    bool m_ghostPositionFound = false;

    int m_nextFigureIndex = -1;
};