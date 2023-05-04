#include <random>
#include "TetrisGameState.h"
#include "GameOverState.h"

TetrisGameState::TetrisGameState(GameDataRef gameData) : m_data(gameData){}

void TetrisGameState::Init()
{
    m_isPlaying = true;

    //Set the random seed.
    srand(time(nullptr));

    //Init variables
    m_data->level = 0;
    m_data->lines = 0;
    m_data->score = 0;
    m_nextFigureIndex = -1;
    m_ghostPositionFound = false;

    //Load texture from asset path.
    m_data->assetManager.LoadTexture("Tileset", tetris_config::texture_path);

    //Set UI visibility
    m_gameUI.SetVisible(true);
    m_gameUI.SetValues(m_data);

    //Init table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i][j] = TetrisTile(Vector2i(j, i), m_data->assetManager.GetTexture("Tileset"), tetris_config::EmptyRect);
        }
    }

    SpawnShape();
}

void TetrisGameState::Update(float& deltaTime)
{
    //If game is not playing, return.
    if(!m_isPlaying)
        return;

    if(m_isClearOnProcess)
    {
        m_clearTimer += deltaTime;

        if(m_clearTimer >= tetris_config::line_clear_effect_duration)
        {
            for (int i = 0; i < m_rowsOnClearProcess.size(); ++i)
            {
                EndClearRow(m_rowsOnClearProcess[i]);
                m_rowsOnClearProcess.erase(m_rowsOnClearProcess.begin() + i);
                --i;
            }

            m_ghostPositionFound = false;
            m_isClearOnProcess = false;
            m_clearTimer = 0.0f;
        }
        return;
    }

    m_movementTimer += deltaTime;
    m_fallTimer += deltaTime;
    m_rotateTimer += deltaTime;
    m_hardDropTimer += deltaTime;

    if (m_data->input.rotating && m_rotateTimer > tetris_config::rotate_threshold)
    {
        RotateShape();
    }
    MoveShape();

    if (m_data->input.hardDrop && m_hardDropTimer > tetris_config::hard_drop_threshold)
    {
        HardDropShape();
    }

    if (!m_ghostPositionFound)
    {
        PlaceGhostShape();
    }

    m_data->soundManager.Update();
}

void TetrisGameState::Render(RenderWindow& window)
{
    //Draw Table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i][j].Draw(window);
        }
    }

    //Draw current shape and ghost when clear effect is not on.
    if (!m_isClearOnProcess)
    {
        m_currentGhost.Draw(window);
        m_currentShape.Draw(window);
    }

    //Draw UI
    m_gameUI.OnRender(window);
}

void TetrisGameState::ProcessEvent(Event& event)
{
}

void TetrisGameState::SpawnShape()
{
    int currentIndex = -1;
    //If next figure hasn't been set yet.
    if (m_nextFigureIndex == -1)
        currentIndex = RollDice();
    else
        currentIndex = m_nextFigureIndex;

    m_nextFigureIndex = RollDice();

    //Spawn Current Piece
    m_currentShape = Tetromino(currentIndex, Vector2i((columns - 1) / 2 - 1, 0), m_data->assetManager.GetTexture("Tileset"));

    //Spawn Ghost Piece
    m_currentGhost = Tetromino(m_currentShape);
    const int& tileSize = tetris_config::tileSize;
    m_currentGhost.SetColorRect( IntRect( tileSize * currentIndex, tileSize, tileSize, tileSize));
    m_ghostPositionFound = false;

    m_gameUI.SetNextShape(m_nextFigureIndex, m_data->assetManager.GetTexture("Tileset"));
}

void TetrisGameState::RotateShape()
{
    if (!CheckCollision(m_currentShape.SimulateRotation()))
    {
        m_currentShape.Rotate();
        m_currentGhost.Rotate();
        m_ghostPositionFound = false;
        m_rotateTimer = 0.f;

        m_data->soundManager.PlaySound(SoundManager::Rotate);
    }
}

void TetrisGameState::MoveShape()
{
    //Horizontal Movement
    if (m_data->input.horizontalInput != 0 && m_movementTimer > tetris_config::movement_threshold)
    {
        Vector2i movement(m_data->input.horizontalInput, 0);

        if (!CheckCollision(m_currentShape.SimulateMovement(movement)))
        {
            m_currentShape.Move(movement);
            m_ghostPositionFound = false;

            m_data->soundManager.PlaySound(SoundManager::Move);
        }

        m_movementTimer = 0.f;
    }

    //Vertical Movement
    float fallDelay = m_fallThresholdByLevel / (m_data->input.pressingDown ? tetris_config::fast_fall_factor : 1.f);

    if (m_fallTimer > fallDelay)
    {
        Vector2i movement(0, 1);
        if (!CheckCollision(m_currentShape.SimulateMovement(movement)))
        {
            m_currentShape.Move(movement);

            //Play the sound only when player is pressing down.
            if (m_data->input.pressingDown)
                m_data->soundManager.PlaySound(SoundManager::Move);
        }
        else
        {
            PlaceShape();
        }

        m_fallTimer = 0.f;
    }
}

//Check if the current shape fits the next movement vector.
bool TetrisGameState::CheckCollision(std::vector<Vector2i> targetPoints)
{
    for (int i = 0; i < 4; i++)
    {
        if (m_tetrisTable[targetPoints[i].y][targetPoints[i].x].isOccupied || targetPoints[i].x < 0 || targetPoints[i].x >= columns || targetPoints[i].y >= rows)
            return true;
    }
    return false;
}

void TetrisGameState::PlaceGhostShape()
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

void TetrisGameState::HardDropShape()
{
    m_currentShape.SetPosition(m_currentGhost.GetPosition());
    PlaceShape();

    m_ghostPositionFound = false;
    m_hardDropTimer = 0.0f;
}

//Clear the filled line.
void TetrisGameState::StartClearRow(int lineIndex)
{
    //Clear the line.
    for (int col = 0; col < columns; col++)
    {
        m_tetrisTable[lineIndex][col].isOccupied = false;
        m_tetrisTable[lineIndex][col].SetColorRect(tetris_config::ClearRect);
    }

    m_ghostPositionFound = false;
    m_data->soundManager.PlaySound(SoundManager::LineClear);
}

void TetrisGameState::EndClearRow(int lineIndex)
{
    //Clear the line.
    for (int col = 0; col < columns; col++)
    {
        m_tetrisTable[lineIndex][col].SetColorRect(tetris_config::EmptyRect);
    }

    //Swap the lines above.
    for (int i = lineIndex - 1; i >= 0; i--)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i + 1][j].isOccupied = m_tetrisTable[i][j].isOccupied;
            m_tetrisTable[i + 1][j].SetColorRect(m_tetrisTable[i][j].GetColorRect());

            m_tetrisTable[i][j].isOccupied = false;
            m_tetrisTable[i][j].SetColorRect(tetris_config::EmptyRect);
        }
    }
}

//Place the current shape.
void TetrisGameState::PlaceShape()
{
    auto shapeTiles = m_currentShape.GetTiles();

    for (int i = 0; i < 4; i++)
    {
        auto tile = shapeTiles[i];
        m_tetrisTable[tile.GetPosition().y][tile.GetPosition().x].isOccupied = true;
        m_tetrisTable[tile.GetPosition().y][tile.GetPosition().x].SetColorRect(tile.GetColorRect());
    }

    m_fallTimer = 0.f;
    m_ghostPositionFound = false;
    m_data->soundManager.PlaySound(SoundManager::Place);

    CheckClearRows();

    if(!CheckGameOver())
        SpawnShape();
}

//Check if there are clear rows.
void TetrisGameState::CheckClearRows()
{
    for (int row = 0; row < rows; row++)
    {
        bool rowIsClear = true;
        for (int col = 0; col < columns; col++)
        {
            if (!m_tetrisTable[row][col].isOccupied)
            {
                rowIsClear = false;
                break;
            }
        }

        if (rowIsClear)
            m_rowsOnClearProcess.push_back(row);
    }

    if (m_rowsOnClearProcess.empty())
        return;

    int scoreToAdd = 0;

    m_isClearOnProcess = true;
    m_clearTimer = 0.0f;

    for (int i = 0; i < m_rowsOnClearProcess.size(); ++i)
    {
        StartClearRow(m_rowsOnClearProcess[i]);
        scoreToAdd += tetris_config::score_per_row * (i + 1);
    }

    m_data->lines += m_rowsOnClearProcess.size();
    m_data->score += scoreToAdd;

    int level = (int)(m_data->lines / 10);
    if(level > m_data->level)
    {
        //Update Game Level
        m_data->level = level;
        m_fallThresholdByLevel = pow(tetris_config::fall_threshold - (m_data->level * 0.007), m_data->level);
    }
    m_gameUI.SetValues(m_data);
}

bool TetrisGameState::CheckGameOver()
{
    bool gameOver = false;
    auto targetPoints = m_currentShape.GetPositionArray();

    for (int i = 0; i < 4; i++)
    {
        if (targetPoints[i].y <= 0)
            gameOver = true;
    }

    if (gameOver)
    {
        m_isPlaying = false;
        m_data->soundManager.DisposeAll();
        m_gameUI.SetVisible(false);
        m_data->stateMachine.AddState(std::make_unique<GameOverState>(m_data), true);
    }
    return gameOver;
}

void TetrisGameState::Pause()
{
    m_isPlaying = false;
}

void TetrisGameState::Resume()
{
    m_isPlaying = true;
}

int TetrisGameState::RollDice()
{
    int number = -1;
    if (m_figuresBag.empty())
    {
        for (int i = 0; i < tetris_config::figure_count; ++i)
        {
            m_figuresBag.push_back(i);
        }
        std::shuffle(m_figuresBag.begin(), m_figuresBag.end(), std::mt19937(std::random_device()()));
    }
    number = m_figuresBag.back();
    m_figuresBag.pop_back();

    return number;
}
