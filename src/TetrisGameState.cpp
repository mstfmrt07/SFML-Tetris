#include <random>
#include "TetrisGameState.h"
#include "GameOverState.h"
#include "AssetManager.h"

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
    AssetManager::GetInstance()->LoadTexture("Tileset", tetris_config::texture_path);

    //Init UI
    InitUI();
    UpdateUI();

    //Init table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m_tetrisTable[i][j] = TetrisTile(Vector2i(j, i), AssetManager::GetInstance()->GetTexture("Tileset"), tetris_config::EmptyRect);
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
    RenderUI(window);
}

void TetrisGameState::ProcessEvent(Event& event)
{
}

void TetrisGameState::SpawnShape()
{
    int currentIndex = -1;
    Vector2i spawnPos = Vector2i((columns - 1) / 2 - 1, 0);
    //If next figure hasn't been set yet.
    if (m_nextFigureIndex == -1)
    {
        currentIndex = RollDice();
        m_currentShape = Tetromino(currentIndex, spawnPos, AssetManager::GetInstance()->GetTexture("Tileset"));
    }
    else
    {
        //Spawn Current Piece
        currentIndex = m_nextFigureIndex;
        m_currentShape = Tetromino(m_nextShape);
        m_currentShape.SetPosition(spawnPos);
    }

    m_nextFigureIndex = RollDice();

    //Spawn Ghost Piece
    m_currentGhost = Tetromino(m_currentShape);
    const int& tileSize = tetris_config::tileSize;
    m_currentGhost.SetColorRect( IntRect( tileSize * currentIndex, tileSize, tileSize, tileSize));
    m_ghostPositionFound = false;

    m_nextShape = Tetromino(m_nextFigureIndex, Vector2i(12, 3), AssetManager::GetInstance()->GetTexture("Tileset"));
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
    UpdateUI();
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

void TetrisGameState::InitUI()
{
    Vector2f containerSize = Vector2f(192, 88);
    float spacing = 12.0f;

    //Init Next Shape Container
    m_nextContainer = RoundedRectangleShape(Vector2f(192, 192), 16.f, 8);
    m_nextContainer.setFillColor(tetris_config::container_color);
    m_nextContainer.setPosition(352, 28);

    //Init Next Shape Title
    m_nextText = Text("NEXT:", AssetManager::GetInstance()->GetFont("Default_Font"), 24);
    m_nextText.setFillColor(tetris_config::secondary_text_color);
    m_nextText.setPosition(372, 36);

    //Init Level Container
    m_levelContainer = RoundedRectangleShape(containerSize, 16.f, 8);
    m_levelContainer.setFillColor(tetris_config::container_color);
    m_levelContainer.setPosition(352, 240);

    //Init Level Label
    m_levelText = Text("LEVEL: 0", AssetManager::GetInstance()->GetFont("Default_Font"), 24);
    m_levelText.setFillColor(tetris_config::secondary_text_color);
    m_levelText.setLineSpacing(1.2f);
    m_levelText.setPosition(372, 252);

    //Init Lines Container
    m_linesContainer = RoundedRectangleShape(m_levelContainer);
    m_linesContainer.setPosition(352, 348);

    //Init Lines Label
    m_linesText = Text(m_levelText);
    m_linesText.setString("LINES: 0");
    m_linesText.setPosition(372, 360);

    //Init Score Container
    m_scoreContainer = RoundedRectangleShape(m_levelContainer);
    m_scoreContainer.setPosition(352, 456);

    //Init Score Label
    m_scoreText = Text(m_levelText);
    m_scoreText.setString("SCORE: 0");
    m_scoreText.setPosition(372, 468);

    m_pauseOverlay = RectangleShape(Vector2f(tetris_config::screen_width, tetris_config::screen_height));
    m_pauseOverlay.setPosition(0, 0);
    Color overlayColor(tetris_config::container_color);
    overlayColor.a = 160;
    m_pauseOverlay.setFillColor(overlayColor);

    //Init Pause Container
    m_pauseContainer = RoundedRectangleShape(m_levelContainer);
    m_pauseContainer.setSize(Vector2f(192.0f, 44.0f));
    m_pauseContainer.setPosition(352, 564);

    //Init Pause Label
    m_pauseText = Text(m_levelText);
    m_pauseText.setString("|| PAUSE");
    m_pauseText.setPosition(372, 572);
}

void TetrisGameState::UpdateUI()
{
    m_levelText.setString("LEVEL: \n" + std::to_string(m_data->level + 1));
    m_linesText.setString("LINES: \n" + std::to_string(m_data->lines));
    m_scoreText.setString("SCORE: \n" + std::to_string(m_data->score));
}

void TetrisGameState::RenderUI(RenderWindow& window)
{
    if(!m_isPlaying)
        window.draw(m_pauseOverlay);

    window.draw(m_nextContainer);
    window.draw(m_nextText);
    window.draw(m_scoreContainer);
    window.draw(m_scoreText);
    window.draw(m_levelContainer);
    window.draw(m_levelText);
    window.draw(m_linesContainer);
    window.draw(m_linesText);
    window.draw(m_pauseContainer);
    window.draw(m_pauseText);

    m_nextShape.Draw(window);

    if(m_data->input.IsTextClicked(m_pauseText, window))
    {
        if(m_isPlaying)
        {
            std::cout << "Clicked on Pause!" << std::endl;
            m_pauseText.setString("> RESUME");
            m_isPlaying = false;
        }
        else
        {
            std::cout << "Clicked on Resume!" << std::endl;
            m_pauseText.setString("|| PAUSE");
            m_isPlaying = true;
        }
    }
}
