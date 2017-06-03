#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../Server/Server.h"
#include "Client.h"

class Application
{
    public:
        Application(char option);

        void runLoop();

    private:
        void handleRequests ();
        void sendToServer   ();

        void event  ();
        void input  ();
        void update ();
        void draw   ();



        sf::RenderWindow    m_window;

        Client              m_client;
        Server::PongServer  m_server;
        sf::IpAddress       m_serverIP;

        Controls m_input;

};

#endif // APPLICATION_H_INCLUDED
