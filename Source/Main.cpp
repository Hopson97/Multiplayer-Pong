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

    sf::RenderWindow window({1280, 720}, "Pong");
    Client client;
    client.socket.setBlocking(false);


    window.setFramerateLimit(60);

    sf::RectangleShape ballSprite;
    ballSprite.setSize({50, 50});


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

        sf::Packet packetRec;
        sf::Vector2<int16_t> ballPosition;
        uint16_t recievePort;

        if (client.socket.receive(packetRec, Server::PongServer::ip, recievePort)
            == sf::Socket::Done)
        {
            if (packetRec >> ballPosition.x >> ballPosition.y)
            {
                ballSprite.setPosition(ballPosition.x, ballPosition.y);
            }
        }

        window.clear();
        window.draw(ballSprite);
        window.display();

    }

}


