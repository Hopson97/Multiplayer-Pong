#include "Server.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

namespace Server
{
    sf::IpAddress PongServer::ipAddress = "127.0.0.1";
    uint16_t PongServer::port = 50'000;

    void PongServer::launch()
    {
        m_socket.bind(50'001);
        std::cout << "Server launched\n";
        m_exeThread = std::make_unique<std::thread>([&]()
        {
            m_socket.setBlocking(false);
            unsigned ticks = 0;

            const sf::Time MS_PER_UPDATE = sf::seconds(0.05);// Ticks/ updates per second
            sf::Clock gameTimer;

            auto lastTime = gameTimer.getElapsedTime();
            auto updateLag = sf::Time::Zero;

            while (m_isRunning)
            {
                auto current = gameTimer.getElapsedTime();
                auto elapsed = current - lastTime;
                lastTime = current;
                updateLag += elapsed;

                //Fixed loop
                while (updateLag >= MS_PER_UPDATE)
                {
                    ticks++;

                    //Move the ball's position based on it's velocity vector
                    m_paddle.position += m_paddle.velocity;
                    m_paddle.update();


                    //Create a packet and send it to the only client lol
                    sf::Packet sendPacket;
                    sendPacket << m_paddle.position.x << m_paddle.position.y;
                    m_socket.send(sendPacket, ipAddress, port);

                    sf::IpAddress add;
                    uint16_t port;
                    sf::Packet recPacket;
                    m_socket.receive(recPacket, add, port);
                    std::string recStr;
                    recPacket >> recStr;

                    if (recStr == "D")
                    {
                        m_paddle.velocity.y += 0.5;
                    }
                    else if (recStr == "W")
                    {
                        m_paddle.velocity.y -= 0.5;
                    }

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
