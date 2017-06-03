#include "Application.h"



    sf::RectangleShape paddleSprite;


    sf::Vector2f paddlePosition;
    sf::Vector2f lastPos;




Application::Application(char option)
:   m_window    ({1280, 720}, "Pong")
{
    m_window.setFramerateLimit(60);
    paddleSprite.setSize({50, 200});

    switch (option)
    {
        case 'H':
            m_server.launch();
            break;

        default:
            break;
    }

    if (!m_client.tryConnect())
    {
        //error
    }
}


void Application::runLoop()
{
    while (m_window.isOpen())
    {
        event   ();
        input   ();
        handleRequests();
        sendToServer();
        update  ();
        draw    ();
    }
}

void Application::event()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Application::input()
{

    m_input = Controls::None;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_input = Controls::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_input = Controls::Down;
    }
}

//Get data sent from the server
void Application::handleRequests()
{
    sf::Packet packetRec;
    uint16_t receivePort;

    m_client.socket.receive(packetRec,
                            m_serverIP,
                            receivePort);

    packetRec >> paddlePosition.x >> paddlePosition.y;
}

//On the tin
void Application::sendToServer()
{
    sf::Packet sendPacket;
    sendPacket << (uint16_t)m_input;
    m_client.socket.send(sendPacket, m_serverIP, 50'001);
}

void Application::update()
{
    paddleSprite.setPosition(paddlePosition.x, paddlePosition.y);
    lastPos = paddlePosition;
}

void Application::draw()
{
    m_window.clear();
    m_window.draw(paddleSprite);
    m_window.display();
}

