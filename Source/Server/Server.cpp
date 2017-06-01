#include "Server.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

namespace Server
{
    sf::IpAddress PongServer::ipAddress = "127.0.0.1";
    uint16_t PongServer::port = 50'000;

    void PongServer::launch()
    {
        std::cout << "Server launched\n";
        m_exeThread = std::make_unique<std::thread>([&]()
        {
            unsigned ticks = 0;

            const sf::Time MS_PER_UPDATE = sf::seconds(0.016);// Ticks/ updates per second
            sf::Clock gameTimer;

            auto lastTime = gameTimer.getElapsedTime();
            auto updateLag = sf::Time::Zero;

            while (m_isRunning)
            {
                auto current = gameTimer.getElapsedTime();
                auto elapsed = current - lastTime;
                lastTime = current;
                updateLag += elapsed;

                while (updateLag >= MS_PER_UPDATE)
                {
                    ticks++;
                    m_ball.position += m_ball.velocity;


                    sf::Packet sendPacket;

                    std::cout << "Pos: " << m_ball.position.x << " " << m_ball.position.y << "\n";

                    sendPacket << m_ball.position.x << m_ball.position.y;
                    m_socket.send(sendPacket, ipAddress, port);
                    m_ball.update();
                    updateLag -= MS_PER_UPDATE;
                }
            }
        });
    }

    PongServer::~PongServer()
    {
        if (m_exeThread)
        {
            m_isRunning = false;
            m_exeThread->join();
        }
    }
}
