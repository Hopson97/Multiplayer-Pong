#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/System/Vector2.hpp>

namespace Server
{
    struct Paddle
    {
        sf::Vector2f size       = { 50, 200 };
        sf::Vector2f position   = { 50, 50  };
        sf::Vector2f velocity;

        void update()
        {
            if (position.y > 720 - size.y)
            {
                position.y = 720 - size.y;
                velocity.y = -1;
            }
            if (position.y < 0)
            {
                position.y = 0;
                velocity.y = 1;
            }
            velocity.y *= 0.90;
        }
    };
}

#endif // BALL_H_INCLUDED
