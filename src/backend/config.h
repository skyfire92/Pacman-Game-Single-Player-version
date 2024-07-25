#pragma once

#include <chrono>
#include "coordinates.h"
#include "common.h"

namespace Config
{
    namespace Timing
    {
        using namespace std::chrono_literals;

        /*Approximately 60Hz refresh rate*/
        static constexpr auto VIEWPORT_UPDATE_INTERVAL = 17ms;

        namespace MovableCharacter
        {
            const auto NORMAL_SPEED = 6ms;
        }

        namespace Pacman
        {
            const auto ANIMATION_SPEED_FACTOR = 6;
        }

        namespace Ghost
        {
            const auto SCARED_BLUE_TIME = 1s;
            const auto SCARED_WHITE_TIME = 1s;
        }

        static const auto GAME_LOOP_INTERVAL = MovableCharacter::NORMAL_SPEED;
    }

    namespace InitialDirection
    {
        const Direction PACMAN = Direction::LEFT;
        const Direction BLUE_GHOST = Direction::UP;
        const Direction ORANGE_GHOST = Direction::UP;
        const Direction PURPLE_GHOST = Direction::UP;
        const Direction RED_GHOST = Direction::LEFT;
    }

    namespace StartingCoordinates
    {
        const Coordinates PACMAN{320, 514};
        const Coordinates BLUE_GHOST{265, 318};
        const Coordinates ORANGE_GHOST{349, 318};
        const Coordinates PURPLE_GHOST{307, 318};
        const Coordinates RED_GHOST{307, 252};
    }

    namespace MoveOutOfTheStartingBoxTimeout
    {
        using namespace std::chrono_literals;

        const auto BLUE_GHOST = 3s;
        const auto ORANGE_GHOST = 2s;
        const auto PURPLE_GHOST = 1s;
        const auto RED_GHOST = 0s;
    }
}
