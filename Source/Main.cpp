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
        if (socket.bind(50'000) == sf::Socket::Done)
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
    ballSprite.setSize({50, 200});


    sf::Vector2f paddlePosition;
    sf::Vector2f lastPos;
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

        uint16_t receivePort;

        sf::IpAddress address;
        client.socket.receive(packetRec,
                              address,
                              receivePort);



        sf::Packet sendPacket;
        Controls controls;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            controls = Controls::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            controls = Controls::Down;
        }

        sendPacket << (uint16_t)controls;
        client.socket.send(sendPacket, address, 50'001);

        packetRec >> paddlePosition.x >> paddlePosition.y;
        {
            ballSprite.setPosition(paddlePosition.x, paddlePosition.y);
        }

        window.clear();
        window.draw(ballSprite);
        window.display();
    }
}


