#pragma once
#include "SFML/Audio.hpp"
#include "TetrisConfig.h"
#include <iostream>
#include <deque>
#include "AssetManager.h"

using namespace sf;

class SoundManager
{

public:
    enum SoundType
    {
        LineClear, Rotate, Move, Place
    };

    SoundManager()
    {
        AssetManager::GetInstance()->LoadSoundBuffer("Line Clear", tetris_config::line_clear_sound);
        AssetManager::GetInstance()->LoadSoundBuffer("Rotate", tetris_config::rotate_sound);
        AssetManager::GetInstance()->LoadSoundBuffer("Move", tetris_config::move_sound);
        AssetManager::GetInstance()->LoadSoundBuffer("Place", tetris_config::place_sound);
    }

    void Update()
    {
        for (int i = 0; i < m_playingQueue.size(); ++i)
        {
            //Move stopped sound to awaiting queue.
            if (m_playingQueue[i].getStatus() == Sound::Stopped)
            {
                m_waitingQueue.emplace_back(std::move(m_playingQueue[i]));
                m_playingQueue.erase(m_playingQueue.begin() + i);
                --i;
            }
        }

    }

    void PlaySound(SoundType soundType)
    {
        //If there is no waiting sound, push a new one into playing queue.
        if(m_waitingQueue.empty())
        {
            m_playingQueue.emplace_back();
        }
        else
        {
            m_playingQueue.emplace_back(std::move(m_waitingQueue.back()));
            m_waitingQueue.pop_back();
        }

        switch (soundType) {
            case LineClear:
                m_playingQueue.back().setBuffer(AssetManager::GetInstance()->GetSoundBuffer("Line Clear"));
                break;
            case Rotate:
                m_playingQueue.back().setBuffer(AssetManager::GetInstance()->GetSoundBuffer("Rotate"));
                break;
            case Move:
                m_playingQueue.back().setBuffer(AssetManager::GetInstance()->GetSoundBuffer("Move"));
                break;
            case Place:
                m_playingQueue.back().setBuffer(AssetManager::GetInstance()->GetSoundBuffer("Place"));
                break;
            default:
                std::cout << "Error! Unexpected sound type." << std::endl;
        }

        if(m_playingQueue.back().getBuffer())
            m_playingQueue.back().play();
    }

    void DisposeAll()
    {
        //Clear the queues.
        m_waitingQueue.clear();
        m_playingQueue.clear();
    }

private:
    std::deque<Sound> m_waitingQueue;
    std::deque<Sound> m_playingQueue;
};
