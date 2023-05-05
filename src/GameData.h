#pragma once
#include "InputManager.h"
#include "SoundManager.h"
#include "StateMachine.h"

struct GameData
{
    StateMachine stateMachine;
    InputManager input;
    SoundManager soundManager;
    int level = 0;
    int lines = 0;
    int score = 0;
};

typedef std::shared_ptr<GameData> GameDataRef;