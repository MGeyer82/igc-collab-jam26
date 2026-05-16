#pragma once

#include "Game.h"

enum class PlayerTextures
{
    IDLE,
    UP_SWING_1,
    UP_SWING_2,
    DOWN_SWING_1,
    DOWN_SWING_2
};

enum class EnemyTextures
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

enum class LayoutTextures
{
    BORDER,
    RHYTHM_BAR,
    OUTDOORS_1,
    OUTDOORS_2,
    FOREST_1,
    FOREST_2,
    CASTLE_1,
    CASTLE_2
};

const std::unordered_map<PlayerTextures, std::string> player_paths{
    { PlayerTextures::IDLE,            "assets/sprites/player/sword_idle.png"      },
    { PlayerTextures::UP_SWING_1,      "assets/sprites/player/up_swing_1.png"      },
    { PlayerTextures::UP_SWING_2,      "assets/sprites/player/up_swing_2.png"       },
    { PlayerTextures::DOWN_SWING_1,    "assets/sprites/player/down_swing_1.png"    },
    { PlayerTextures::DOWN_SWING_2,    "assets/sprites/player/down_swing_2.png"    }
};

const std::unordered_map<EnemyTextures, std::string> enemy_paths{
    { EnemyTextures::MOVE_UP,       "assets/sprites/enemy/enemy_up.png"      },
    { EnemyTextures::MOVE_DOWN,     "assets/sprites/enemy/enemy_down.png"    },
    { EnemyTextures::MOVE_LEFT,     "assets/sprites/enemy/enemy_left.png"    },
    { EnemyTextures::MOVE_RIGHT,    "assets/sprites/enemy/enemy_right.png"   }
};

const std::unordered_map<LayoutTextures, std::string> layout_paths{
    { LayoutTextures::BORDER,       "assets/sprites/layout/border.png"           },
    { LayoutTextures::RHYTHM_BAR,   "assets/sprites/layout/rhythm_bar.png"       },
    { LayoutTextures::OUTDOORS_1,   "assets/sprites/layout/outdoors_1.png"       },
    { LayoutTextures::OUTDOORS_2,   "assets/sprites/layout/outdoors_2.png"       },
    { LayoutTextures::FOREST_1,     "assets/sprites/layout/dark_forest_1.png"    },
    { LayoutTextures::FOREST_2,     "assets/sprites/layout/dark_forest_2.png"    },
    { LayoutTextures::CASTLE_1,     "assets/sprites/layout/castle_1.png"         },
    { LayoutTextures::CASTLE_2,     "assets/sprites/layout/castle_2.png"         }
};