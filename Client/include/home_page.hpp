#ifndef __HOME_PAGE_HPP__
#define __HOME_PAGE_HPP__

/*---- LIBRARY ----*/
#include <iostream>
#include <string>

/*---- LIBRARY SFML ----*/
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "quarto.hpp"
#include "client.hpp"

class HomePage{
public:
    HomePage(std::string name);
    ~HomePage();
    void mainWindow();

private:
    // HOME PAGE
    Quarto _quarto;
    TypeGame _typeGame;
    std::string _name;

    // WINDOW
    sf::RenderWindow _window;                     // For the window
    sf::Event _event;                             // For the events
    sf::RectangleShape _buttonQuarto;

    // TEXT
    sf::Font _font;                               // Font for the game
    sf::Text _text1;                              // Text
    sf::Text _text2;                              // Text

    // SERVER
    Client *_client;                              // Client that allow to communicate with client
    ToReceive _receive;                           // Structure to receive from the server
    ToSend _send;                                 // Structure to send to the server
    TypeReceive _typeReceive;
    
};

#endif // __HOME_PAGE_HPP__