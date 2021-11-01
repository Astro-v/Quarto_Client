#ifndef __QUARTO_HPP__
#define __QUARTO_HPP__

/*---- LIBRARY ----*/
#include <iostream>
#include <string>

/*---- LIBRARY SFML ----*/
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "client.hpp"

class Quarto{
    public:
    Quarto(std::string name);
    void play(Client *client);

    private:
    // METHOD
    bool isPlacable(int posX, int posY) const;   // Return true if the given position car receive a piece
    void display();

    // GAME
    Status _status;                               // Status of the game
    bool _play;                                   // Booleen that worth true as long as no one win
    int _posX[NUMBER_PIECES];                     // Abscissa of the pieces
    int _posY[NUMBER_PIECES];                     // Ordinate of the pieces
    bool _used[NUMBER_PIECES];                    // True if a piece is used
    int _pick;                                    // Correspond to the picked piece -1:NONE
    std::string _name;
    int _winner;
    
    // SERVER
    Client *_client;                               // Client that allow to communicate with client
    ToReceive _receive;                           // Structure to receive from the server
	ToSend _send;                                 // Structure to send to the server
    TypeReceive _typeReceive;

    // WINDOW
    sf::RenderWindow _window;                     // For the window
    sf::Event _event;                             // For the events

    // SPRITE
    sf::Texture _textureBack;
    sf::Sprite _spriteBack;                       // Background of the game
    sf::Texture _texturePieces;
    sf::Sprite _spritePieces;                     // Sprites with all the pieces
    sf::Texture _textureHighlight;
    sf::Sprite _spriteHighlight;                  // Sprite for the highlight

    // TEXT
    sf::Font _font;                               // Font for the game
    sf::Text _text;                               // Text for the player
    sf::Text _textQuarto;                         // Text for the name of the game
};

#endif // __QUARTO_HPP__