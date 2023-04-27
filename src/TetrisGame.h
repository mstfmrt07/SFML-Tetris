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
    void OnPause() override;
    void OnResume() override;

private:
    bool CheckCollision(std::vector<Vector2i> targetPoints);
    bool CheckGameOver();
    void MoveShape();
    void RotateShape();
    void SpawnShape();
    void PlaceShape();
    void HardDropShape();
    void CheckClearRows();
    void ClearLine(int lineIndex);
    void PlaceGhostShape();

    InputController m_input;
    SoundManager m_soundManager;
    GameUI m_gameUI;
    GameOverUI m_gameOverUI;

    Texture m_texture;

    TetrisTile m_tetrisTable[rows][columns];

    bool m_isPlaying = false;
    int m_level = 0;
    int m_score = 0;

    float m_fallTimer = tetris_config::fall_threshold;
    float m_movementTimer = tetris_config::movement_threshold;
    float m_rotateTimer = tetris_config::rotate_threshold;
    float m_hardDropTimer = tetris_config::hard_drop_threshold;

    Tetromino m_currentShape;
    Tetromino m_currentGhost;
    bool m_ghostPositionFound = false;

    int m_nextFigureIndex = -1;
};