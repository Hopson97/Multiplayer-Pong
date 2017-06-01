#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/System/Vector2.hpp>

namespace Server
{
    struct Ball
    {
        sf::Vector2<int16_t> position;
        sf::Vector2<int16_t> velocity = {1, 1};

        void update()
        {
            if (position.x > 1280 || position.x < 0)
            {
                velocity.x = -velocity.x;
            }
            if (position.y > 720 || position.y < 0)
            {
                velocity.y = -velocity.y;
            }
        }
    };
}

#endif // BALL_H_INCLUDED
