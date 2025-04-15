#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Player.h"






int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Initialize random seed

    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);
    Player player(playerName);

    Game game(player);

    char playAgain;
    do {
        game.privateChoice();
        std::cout << "Do you want to play another game? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');


    // sf::RenderWindow window;
    // ///////////////////////////////////////////////////////////////////////////
    // /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    // window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    // ///////////////////////////////////////////////////////////////////////////
    // //
    // ///////////////////////////////////////////////////////////////////////////
    // /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    // /// This is needed so we do not burn the GPU                            ///
    // window.setVerticalSyncEnabled(true);                                    ///
    // /// window.setFramerateLimit(60);                                       ///
    // ///////////////////////////////////////////////////////////////////////////
    //
    // while (window.isOpen()) {
    //     bool shouldExit = false;
    //     sf::Event e{};
    //     while (window.pollEvent(e)) {
    //         switch (e.type) {
    //         case sf::Event::Closed:
    //             window.close();
    //             break;
    //         case sf::Event::Resized:
    //             std::cout << "New width: " << window.getSize().x << '\n'
    //                       << "New height: " << window.getSize().y << '\n';
    //             break;
    //         case sf::Event::KeyPressed:
    //             std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
    //             if (e.key.code == sf::Keyboard::Escape)
    //                 shouldExit = true;
    //             break;
    //         default:
    //             break;
    //         }
    //     }
    //     if (shouldExit) {
    //         window.close();
    //         break;
    //     }
    //     using namespace std::chrono_literals;
    //     std::this_thread::sleep_for(300ms);
    //
    //     window.clear();
    //     window.display();
    // }
    return 0;
}