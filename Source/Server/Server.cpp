#include "Server.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

namespace Server
{
    sf::IpAddress PongServer::ip = "192.168.0.11";

    void PongServer::launch()
    {
        std::cout << "Launched Server.\n";

        sf::Clock gameTimer;

        auto MS_PER_UPDATE = 0.05; //20 Ticks/ updates per second

        float lastTime = gameTimer.getElapsedTime().asSeconds();
        float lag = 0.0f;

        float current = gameTimer.getElapsedTime().asSeconds();
        float elapsed = current - lastTime;
        lastTime = current;

        m_socket.setBlocking(false);


        m_exeThread = std::make_unique<std::thread>([&]()
        {
            while (m_isRunning)
            {
                while (lag >= MS_PER_UPDATE)
                {
                    m_ball.position += m_ball.velocity;

                    unsigned short port = 50'000;
                    sf::Packet packet;
                    packet << m_ball.position.x << m_ball.position.y;
                    m_socket.send(packet, ip, port);
                    m_ball.update();
                    lag -= MS_PER_UPDATE;
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
