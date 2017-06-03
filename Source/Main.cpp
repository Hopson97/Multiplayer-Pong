#include <iostream>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

#include "Client/Application.h"

namespace
{
    char getHostOrClient()
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
        return option;
    }
}

int main()
{
    Application app(getHostOrClient());
    app.runLoop();

    return EXIT_SUCCESS;
}


