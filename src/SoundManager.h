#include "SFML/Audio.hpp"
#include "TetrisConfig.h"
#include <iostream>

using namespace sf;

class SoundManager
{

public:
    enum SoundType
    {
        LineClear, Rotate, Move
    };

    SoundManager()
    {
        if(!m_lineClear.loadFromFile(tetris_config::line_clear_sound))
            std::cout << "Error while loading sound." << std::endl;

        if(!m_rotate.loadFromFile(tetris_config::rotate_sound))
            std::cout << "Error while loading sound." << std::endl;

        if(!m_move.loadFromFile(tetris_config::move_sound))
            std::cout << "Error while loading sound." << std::endl;
    }

    void PlaySound(SoundType soundType)
    {
        switch (soundType) {
            case LineClear:
                m_sound.setBuffer(m_lineClear);
                break;
            case Rotate:
                m_sound.setBuffer(m_rotate);
                break;
            case Move:
                m_sound.setBuffer(m_move);
                break;
            default:
                std::cout << "Error! Unexpected sound type." << std::endl;
        }

        if(m_sound.getBuffer())
            m_sound.play();
    }

private:
    Sound m_sound;

    SoundBuffer m_lineClear;
    SoundBuffer m_rotate;
    SoundBuffer m_move;
};
