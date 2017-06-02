#include "Server.h"

#include <iostream>
#include <SFML/System/Clock.hpp>



namespace Server
{
    sf::IpAddress ipAddress = "127.0.0.1";

    void PongServer::launch()
    {
        m_socket.bind(50'001);
        std::cout << "Server launched\n";
        m_exeThread = std::make_unique<std::thread>([&]()
        {
            m_socket.setBlocking(false);
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
                    m_socket.send(sendPacket, ipAddress, 50'000);

                    handleRequests();

                    updateLag -= MS_PER_UPDATE;
                }
            }
        });
    }

    void PongServer::handleRequests()
    {
        sf::IpAddress add;
        uint16_t port;
        sf::Packet recPacket;
        m_socket.receive(recPacket, add, port);


        uint16_t controls;
        recPacket >> controls;
        auto c = (Controls)controls;

        if (c == Controls::Down)
        {
            m_paddle.velocity.y += 0.5;
        }
        else if (c == Controls::Up)
        {
            m_paddle.velocity.y -= 0.5;
        }
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
