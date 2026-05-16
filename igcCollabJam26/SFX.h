#pragma once

#include "Game.h"

enum class menuSFX
{
    MENU_HOVER,
    MENU_CLICK
};

enum class hitSFX
{
    SWORD_HIT_1,
    SWORD_HIT_2,
    SWORD_HIT_3,
    SWORD_HIT_4,
    SWORD_HIT_5,
    SWORD_HIT_6,
    SWORD_HIT_7
};

enum class swingSFX
{
    SWORD_SWING_1,
    SWORD_SWING_2,
    SWORD_SWING_3,
    SWORD_SWING_4,
    SWORD_SWING_5,
    SWORD_SWING_6,
    SWORD_SWING_7,
    SWORD_SWING_8,
    SWORD_SWING_9,
    SWORD_SWING_10,
    SWORD_SWING_11,
    SWORD_SWING_12
};

const std::unordered_map<menuSFX, std::string> menu_paths{
    { menuSFX::MENU_HOVER,     "assets/music/test_1.wav"          },
    { menuSFX::MENU_CLICK,     "assets/music/dark_forest.wav"     },
};

const std::unordered_map<hitSFX, std::string> hit_paths{
    { hitSFX::SWORD_HIT_1,      "assets/sfx/sword_hit_1.wav"       },
    { hitSFX::SWORD_HIT_2,      "assets/sfx/sword_hit_2.wav"       },
    { hitSFX::SWORD_HIT_3,      "assets/sfx/sword_hit_3.wav"       },
    { hitSFX::SWORD_HIT_4,      "assets/sfx/sword_hit_4.wav"       },
    { hitSFX::SWORD_HIT_5,      "assets/sfx/sword_hit_5.wav"       },
    { hitSFX::SWORD_HIT_6,      "assets/sfx/sword_hit_6.wav"       },
    { hitSFX::SWORD_HIT_7,      "assets/sfx/sword_hit_7.wav"       },
};

const std::unordered_map<swingSFX, std::string> swing_paths{
    { swingSFX::SWORD_SWING_1,      "assets/sfx/sword_hit_1.wav"        },
    { swingSFX::SWORD_SWING_2,      "assets/sfx/sword_hit_2.wav"        },
    { swingSFX::SWORD_SWING_3,      "assets/sfx/sword_hit_3.wav"        },
    { swingSFX::SWORD_SWING_4,      "assets/sfx/sword_hit_4.wav"        },
    { swingSFX::SWORD_SWING_5,      "assets/sfx/sword_hit_5.wav"        },
    { swingSFX::SWORD_SWING_6,      "assets/sfx/sword_hit_6.wav"        },
    { swingSFX::SWORD_SWING_7,      "assets/sfx/sword_hit_7.wav"        },
    { swingSFX::SWORD_SWING_8,      "assets/sfx/sword_hit_8.wav"        },
    { swingSFX::SWORD_SWING_9,      "assets/sfx/sword_hit_9.wav"        },
    { swingSFX::SWORD_SWING_10,     "assets/sfx/sword_hit_10.wav"       },
    { swingSFX::SWORD_SWING_11,     "assets/sfx/sword_hit_11.wav"       },
    { swingSFX::SWORD_SWING_12,     "assets/sfx/sword_hit_12.wav"       },
};