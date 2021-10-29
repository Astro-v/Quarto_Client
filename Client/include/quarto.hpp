#ifndef __QUARTO_HPP__
#define __QUARTO_HPP__

/*---- LIBRARY ----*/
#include <iostream>

/*---- LIBRARY SFML ----*/
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "client.hpp"

class Quarto{
    public:
    Quarto();
    void play();

    private:
    // METHOD
    bool isPlacable(int posX, int posY) const;   // Return true if the given position car receive a piece
    bool isPickable(int posX, int posY) const;   // Return true if the picked piece is pickable
    int picked(int posX, int posY) const;        // Return the picked piece
    void display();

    // GAME
    Status _status;                               // Status of the game
    bool _play;                                   // Booleen that worth true as long as no one win
    int _posX[NUMBER_PIECES];                     // Abscissa of the pieces
    int _posY[NUMBER_PIECES];                     // Ordinate of the pieces
    bool _used[NUMBER_PIECES];                    // True if a piece is used
    int _pick;                                    // Correspond to the picked piece -1:NONE
    
    // SERVER
    Client _client;                               // client that allow to communicate with client
    ToReceive _receive;              
	ToSend _send;

    // WINDOW
    sf::RenderWindow _window;
    sf::Event _event;

    // SPRITE
    sf::Texture _textureBack;
    sf::Sprite _spriteBack;
    sf::Texture _texturePieces;
    sf::Sprite _spritePieces;
    sf::Texture _textureHighlight;
    sf::Sprite _spriteHighlight;

    // TEXT
    sf::Font _font;                              // Font for the game
    sf::Text _text;                              // Text for the player
    sf::Text _textQuarto;                        // Text for the name of the game
};

#endif // __QUARTO_HPP__