#include "Server.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

namespace Server
{
    sf::IpAddress PongServer::ipAddress = "192.168.0.11";

    void PongServer::launch()
    {
        std::cout << "Server launched\n";
        m_exeThread = std::make_unique<std::thread>([&]()
        {
            m_socket.bind(50'001);
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

                    unsigned short port = 50'000;
                    sf::Packet sendPacket;
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
