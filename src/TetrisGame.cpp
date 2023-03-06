#include "TetrisGame.h"
#include <time.h>

void TetrisGame::OnInit()
{
    //Set the random seed.
    srand(time(NULL));

    //Load texture from asset path.
    m_texture.loadFromFile(tetris_config::texture_path);

    //Set UI visibility
    m_gameUI.SetVisible(true);
    m_gameOverUI.SetVisible(false);
    m_gameUI.SetValues(m_level, m_score);
    m_gameOverUI.SetValues(m_level, m_score);

    //Init variables
    m_level = 0;
    m_score = 0;
    m_nextFigureIndex = -1;
    m_ghostPositionFound = false;

    //Init table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i][j] = TetrisTile(Vector2i(j, i), m_texture, EmptyRect);
        }
    }
    
    //Spawn the first shape
    SpawnShape();
}

void TetrisGame::OnUpdate(float deltaTime)
{
    m_movementTimer += deltaTime;
    m_fallTimer += deltaTime;
    m_rotateTimer += deltaTime;

    if (m_input.rotating && m_rotateTimer > tetris_config::rotate_threshold)
    {
        RotateShape();
    }
    MoveShape();

    if (!m_ghostPositionFound)
    {
        PlaceGhostShape();
    }
}

void TetrisGame::OnRender(RenderWindow& window)
{
    //Draw Table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i][j].Draw(window);
        }
    }

    //Draw current shape and ghost.
    m_currentGhost.Draw(window);
    m_currentShape.Draw(window);

    //Draw UI
    m_gameUI.OnRender(window);
    m_gameOverUI.OnRender(window);
}

void TetrisGame::OnProcessEvent(Event& event)
{
    m_input.OnProcessEvent(event);
}

void TetrisGame::RotateShape()
{
    if (!CheckCollision(m_currentShape.SimulateRotation()))
    {
        m_currentShape.Rotate();
        m_currentGhost.Rotate();
        m_ghostPositionFound = false;
        m_rotateTimer = 0.f;
    }
}

void TetrisGame::MoveShape()
{
    //Horizontal Movement
    if (m_input.horizontalInput != 0 && m_movementTimer > tetris_config::movement_threshold)
    {
        Vector2i movement(m_input.horizontalInput, 0);
        if (!CheckCollision(m_currentShape.SimulateMovement(movement)))
        {
            m_currentShape.Move(movement);
            m_ghostPositionFound = false;
        }

        m_movementTimer = 0.f;
    }

    //Vertical Movement
    float fallDelay = tetris_config::fall_threshold / (m_input.pressingDown ? tetris_config::fast_fall_factor : 1.f);
    if (m_fallTimer > fallDelay)
    {
        Vector2i movement(0, 1);
        if (!CheckCollision(m_currentShape.SimulateMovement(movement)))
        {
            m_currentShape.Move(movement);
        }
        else
        {
            PlaceShape();
            CheckClearLines();

            if (!CheckGameOver())
            {
                SpawnShape();
            }
            else
            {
                //TODO Implement Game Over
                m_gameOverUI.SetValues(m_level, m_score);
                m_gameOverUI.SetVisible(true);
                m_gameUI.SetVisible(false);
            }
        }

        m_fallTimer = 0.f;
    }
}

//Spawn the next shape.
void TetrisGame::SpawnShape()
{
    int index = m_nextFigureIndex == -1 ? rand() % tetris_config::figure_count : m_nextFigureIndex;

    m_nextFigureIndex = rand() % tetris_config::figure_count;

    //Spawn Current Piece
    m_currentShape = Tetromino(index, Vector2i(columns / 2 - 1, -1), m_texture);

    //Spawn Ghost Piece
    m_currentGhost = Tetromino(m_currentShape);
    m_currentGhost.SetTexture(m_texture, IntRect(tetris_config::tileSize * index, tetris_config::tileSize, tetris_config::tileSize, tetris_config::tileSize));
    m_currentGhost.SetColor(Color(255, 255, 255, 200));
    m_ghostPositionFound = false;

    m_gameUI.SetNextShape(m_nextFigureIndex, m_texture);
}

//Place the current shape.
void TetrisGame::PlaceShape()
{
    auto shapeTiles = m_currentShape.GetTiles();

    for (int i = 0; i < 4; i++)
    {
        auto tile = shapeTiles[i];
        m_tetrisTable[tile.GetPosition().y][tile.GetPosition().x].isOccupied = true;
        m_tetrisTable[tile.GetPosition().y][tile.GetPosition().x].SetColorRect(tile.GetColorRect());
    }
}

//Check if there are clear lines.
void TetrisGame::CheckClearLines()
{
    for (int m = 0; m < rows; m++)
    {
        bool lineClear = true;
        for (int n = 0; n < columns; n++)
        {
            if (!m_tetrisTable[m][n].isOccupied)
            {
                lineClear = false;
                break;
            }
        }

        if (lineClear)
        {
            ClearLine(m);
        }
    }
}

//Clear the filled line.
void TetrisGame::ClearLine(int lineIndex)
{
    //Clear the line.
    for (int col = 0; col < columns; col++)
    {
        m_tetrisTable[lineIndex][col].isOccupied = false;
        m_tetrisTable[lineIndex][col].SetColorRect(EmptyRect);
    }

    //Swap the lines above.
    for (int i = lineIndex - 1; i >= 0; i--)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i + 1][j].isOccupied = m_tetrisTable[i][j].isOccupied;
            m_tetrisTable[i + 1][j].SetColorRect(m_tetrisTable[i][j].GetColorRect());

            m_tetrisTable[i][j].isOccupied = false;
            m_tetrisTable[i][j].SetColorRect(EmptyRect);
        }
    }

    m_score += 1;
    m_gameUI.SetValues(m_level, m_score);
}

void TetrisGame::PlaceGhostShape()
{
    for (int i = 1; i < tetris_config::table_rows; i++)
    {
        Vector2i movement(0, i);
        if (CheckCollision(m_currentShape.SimulateMovement(movement)))
        {
            m_currentGhost.SetPosition(m_currentShape.GetPosition() + movement - Vector2i(0, 1));
            m_ghostPositionFound = true;
            return;
        }
    }
}

//Check if the current shape fits the next movement vector.
bool TetrisGame::CheckCollision(Vector2i* targetPoints)
{
    for (int i = 0; i < 4; i++)
    {
        if (m_tetrisTable[targetPoints[i].y][targetPoints[i].x].isOccupied || targetPoints[i].x < 0 || targetPoints[i].x >= columns || targetPoints[i].y >= rows)
            return true;
    }
    return false;
}

bool TetrisGame::CheckGameOver()
{
    auto targetPoints = m_currentShape.GetPositionArray();

    for (int i = 0; i < 4; i++)
    {
        if (targetPoints[i].y <= 0)
            return true;
    }
    return false;
}

void TetrisGame::OnDestroy()
{
}