#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <SFML/Network.hpp>

#include <memory>
#include <thread>

#include "Ball.h"

namespace Server
{
    class PongServer
    {
        public:
            static sf::IpAddress ipAddress;

            void launch();

            ~PongServer();

        private:
            std::unique_ptr<std::thread> m_exeThread;


            Ball m_ball;
            sf::UdpSocket m_socket;

            bool m_isRunning = true;
    };
}

#endif // SERVER_H_INCLUDED
