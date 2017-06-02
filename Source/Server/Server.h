#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <SFML/Network.hpp>

#include <memory>
#include <thread>

#include "Paddle.h"

enum class Controls
{
    None,
    Up,
    Down
};

namespace Server
{
    class PongServer
    {
        public:
            void launch();

            ~PongServer();

        private:

            void handleRequests();

            std::unique_ptr<std::thread> m_exeThread;


            Paddle m_paddle;
            sf::UdpSocket m_socket;

            bool m_isRunning = true;
    };
}

#endif // SERVER_H_INCLUDED
