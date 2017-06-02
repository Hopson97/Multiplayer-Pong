#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <SFML/Network.hpp>

#include <memory>
#include <thread>

#include "Paddle.h"

namespace Server
{
    class PongServer
    {
        public:
            static sf::IpAddress ipAddress;
            static uint16_t port;

            void launch();

            ~PongServer();

        private:
            std::unique_ptr<std::thread> m_exeThread;


            Paddle m_paddle;
            sf::UdpSocket m_socket;

            bool m_isRunning = true;
    };
}

#endif // SERVER_H_INCLUDED
