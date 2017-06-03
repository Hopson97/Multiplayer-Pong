#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>

struct Client
{
    sf::UdpSocket socket;

    bool tryConnect()
    {
        if (socket.bind(50'000) == sf::Socket::Done)
        {
            std::cout << "Connected.\n";
            socket.setBlocking(false);
            return true;
        }
        return false;
    }
};

#endif // CLIENT_H_INCLUDED
