#pragma once
#include "InputManager.h"
#include "SoundManager.h"
#include "StateMachine.h"
#include "AssetManager.h"

struct GameData
{
    StateMachine stateMachine;
    InputManager input;
    SoundManager soundManager;
    AssetManager assetManager;
    int level = 0;
    int score = 0;
};

typedef std::shared_ptr<GameData> GameDataRef;