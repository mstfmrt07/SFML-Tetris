#include "SFML/Audio.hpp"
#include "TetrisConfig.h"
#include <iostream>
#include <deque>

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
        m_lineClear.loadFromFile(tetris_config::line_clear_sound);
        m_rotate.loadFromFile(tetris_config::rotate_sound);
        m_move.loadFromFile(tetris_config::move_sound);
        m_place.loadFromFile(tetris_config::place_sound);
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
                m_playingQueue.back().setBuffer(m_lineClear);
                break;
            case Rotate:
                m_playingQueue.back().setBuffer(m_rotate);
                break;
            case Move:
                m_playingQueue.back().setBuffer(m_move);
                break;
            case Place:
                m_playingQueue.back().setBuffer(m_place);
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
        m_waitingQueue = {};
        m_playingQueue = {};
    }

private:
    std::deque<Sound> m_waitingQueue;
    std::deque<Sound> m_playingQueue;

    SoundBuffer m_lineClear;
    SoundBuffer m_rotate;
    SoundBuffer m_move;
    SoundBuffer m_place;
};
