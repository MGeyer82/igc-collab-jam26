#pragma once

#include "Game.h"

enum class BGM
{
    STAGE_1,
    STAGE_2,
    STAGE_3
};

const std::unordered_map<BGM, std::string> music_paths{
    { BGM::STAGE_1,     "assets/music/dark_forest.wav"          },
    { BGM::STAGE_2,     "assets/music/test_1.wav"               },
    { BGM::STAGE_3,     "assets/music/frantic_castle.wav"       }
};
