#include <iostream>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

#include "Server/Server.h"

struct Client
{
    sf::UdpSocket socket;

    Client()
    {
        if (socket.bind(50000) == sf::Socket::Done)
        {
            std::cout << "Connected.\n";
        }
    }

};

int main()
{
    char option = 'n';

    while (!(option == 'C' ||
              option == 'H'))
    {
        std::cout << "[C]lient or [H]ost?\n";
        std::cin >> option;

        if (!(option == 'C' ||
              option == 'H'))
        {
            std::cout << "Invalid." << std::endl;
        }
    }

    Server::PongServer server;

    switch (option)
    {
        case 'H':
            server.launch();
            break;

        default:
            break;
    }

    Client client;
    sf::RenderWindow window({1280, 720}, "Pong");
    sf::RectangleShape shape;
    shape.setSize({50, 50});

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        int16_t x, y;
        sf::Packet p;
        uint16_t port;
        client.socket.receive(p, Server::PongServer::ip, port);

        if (p >> x >> y)
        {
            shape.setPosition(x, y);
        }

        window.clear();
        window.draw(shape);
        window.display();

    }

}






















