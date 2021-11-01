/*---- LIBRARY ----*/
#include <iostream>

/*---- LIBRARY SFML ----*/
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "quarto.hpp"
#include "client.hpp"

Quarto::Quarto(std::string name):_status(PAUSE),_play(true),_name(name),_winner(0){
    for (int index=0;index<NUMBER_PIECES;++index){
        _posX[index]=index/NUMBER_ROW;
        _posY[index]=index%NUMBER_COLUMN;
        _used[index]=false;
    }
    _pick = NONE;

    _textureBack.loadFromFile("../content/sprite/plateau.png");
    _spriteBack.setTexture(_textureBack);
    _spriteBack.setPosition(0,0);
    _texturePieces.loadFromFile("../content/sprite/pions.png");
    _spritePieces.setTexture(_texturePieces);
    _spritePieces.setPosition(0,0);
    _textureHighlight.loadFromFile("../content/sprite/surbrillance.png");
    _spriteHighlight.setTexture(_textureHighlight);
    _spriteHighlight.setPosition(0,0);

    if (!_font.loadFromFile("../content/font/eraslght.ttf"))
    {
        // error...
    }
    _textQuarto.setFont(_font);
    _textQuarto.setString("Quarto");
    _textQuarto.setFillColor(sf::Color::Black);
    _textQuarto.setCharacterSize(100);
    _textQuarto.setPosition(WIDTH_PLATEAU-_textQuarto.getLocalBounds().width/2,10);

    _text.setFont(_font);
    _text.setString("Player");
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(50);
    _text.setPosition(WIDTH_PLATEAU,HEIGHT_SCORE-60);
}

void Quarto::play(Client *client){
    _client = client;
    _client->initialize(_receive);
    _status = _receive.status;
    for (int index=0;index<NUMBER_PIECES;++index){
        _posX[index] = _receive.posX[index];
        _posY[index] = _receive.posY[index];
        _used[index] = _receive.used[index];
    }
    _pick = _receive.pick;
    std::cout << "Starting ..." << std::endl;
    _window.create(sf::VideoMode(WIDTH, HEIGHT),"Quarto");
    _window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(true);
    display();
    while (_play && _window.isOpen()){
        // we process all the window events that have been generated since the last iteration of the loop
        while (_window.pollEvent(_event)){
            // Request for closing the window
            if (_event.type == sf::Event::Closed){
                _play = false;
                _client->sendData(_send, LEAVE);
                _window.close();
            }
            if (_event.type == sf::Event::MouseButtonPressed){
                if (_event.mouseButton.button == sf::Mouse::Left){
                    for (int i(0);i<4;++i){   
                        for (int j(0);j<4;++j){
                            if (_event.mouseButton.x >= SPACE+(SPACE+WIDTH_PIECE)*i && _event.mouseButton.x <= SPACE+WIDTH_PIECE+(SPACE+WIDTH_PIECE)*i && _event.mouseButton.y >= HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*j && _event.mouseButton.y <= HEIGHT_SCORE+HEIGHT_PIECE+SPACE+(SPACE+HEIGHT_PIECE)*j && _status == PLAYER_1_PLACE){
                                _send.posX = i;
                                _send.posY = j;
                                _client->sendData(_send, GAME_CLIENT);
                            }else if (_event.mouseButton.x >= WIDTH_PLATEAU+SPACE+(SPACE+WIDTH_PIECE)*i && _event.mouseButton.x <= WIDTH_PLATEAU+SPACE+WIDTH_PIECE+(SPACE+WIDTH_PIECE)*i && _event.mouseButton.y >= HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*j && _event.mouseButton.y <= HEIGHT_SCORE+HEIGHT_PIECE+SPACE+(SPACE+HEIGHT_PIECE)*j && _status == PLAYER_1_PICK){
                                _send.posX = i;
                                _send.posY = j;
                                _client->sendData(_send, GAME_CLIENT);
                            }
                        }
                    }
                }
            }
            if (_event.type == sf::Event::MouseMoved){
                display();
            }
        }
        _typeReceive = _client->receiveData(_receive);
        if (_typeReceive == GAME_SERVER){
            _status = _receive.status;
            for (int index=0;index<NUMBER_PIECES;++index){
                _posX[index] = _receive.posX[index];
                _posY[index] = _receive.posY[index];
                _used[index] = _receive.used[index];
            }
            _pick = _receive.pick;
            display();
        }else if(_typeReceive == WIN_P1){
            _status = _receive.status;
            _winner = 1;
            for (int index=0;index<NUMBER_PIECES;++index){
                _posX[index] = _receive.posX[index];
                _posY[index] = _receive.posY[index];
                _used[index] = _receive.used[index];
            }
            _pick = _receive.pick;
            display();
        }else if(_typeReceive == WIN_P2){
            _status = _receive.status;
            _winner = 2;
            for (int index=0;index<NUMBER_PIECES;++index){
                _posX[index] = _receive.posX[index];
                _posY[index] = _receive.posY[index];
                _used[index] = _receive.used[index];
            }
            _pick = _receive.pick;
            display();
        }
    }
}

void Quarto::display(){
    _window.clear(sf::Color::White); // We erase the windows
    _window.draw(_spriteBack);
    for (int index=0;index<NUMBER_PIECES;++index){
        _spritePieces.setTextureRect(sf::IntRect(index*WIDTH_PIECE, 0, WIDTH_PIECE, HEIGHT_PIECE));
        if (!_used[index]){
            _spritePieces.setPosition(WIDTH_PLATEAU+SPACE+(SPACE+WIDTH_PIECE)*_posX[index],HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*_posY[index]);
        }else{
            _spritePieces.setPosition(SPACE+(SPACE+WIDTH_PIECE)*(_posX[index]),HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*_posY[index]);
        }
        _window.draw(_spritePieces);
    }
    if(_pick != NONE){
        _spriteHighlight.setPosition(WIDTH_PLATEAU+SPACE/2+(SPACE+WIDTH_PIECE)*(_pick/NUMBER_ROW),HEIGHT_SCORE+SPACE/2+(SPACE+WIDTH_PIECE)*(_pick%NUMBER_COLUMN));
        _window.draw(_spriteHighlight);
    }
    if (_status == PLAYER_1_PICK){
        for (int i(0);i<4;++i){   
            for (int j(0);j<4;++j){
                if (sf::Mouse::getPosition(_window).x >= WIDTH_PLATEAU+SPACE+(SPACE+WIDTH_PIECE)*i && sf::Mouse::getPosition(_window).x <= WIDTH_PLATEAU+SPACE+WIDTH_PIECE+(SPACE+WIDTH_PIECE)*i && sf::Mouse::getPosition(_window).y >= HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*j && sf::Mouse::getPosition(_window).y <= HEIGHT_SCORE+HEIGHT_PIECE+SPACE+(SPACE+HEIGHT_PIECE)*j){
                    if (!_used[i*NUMBER_COLUMN+j]){
                        _spriteHighlight.setPosition(WIDTH_PLATEAU+SPACE/2+(SPACE+WIDTH_PIECE)*i,HEIGHT_SCORE+SPACE/2+(SPACE+WIDTH_PIECE)*j);
                        _window.draw(_spriteHighlight);
                    }
                }
            }
        }
    }
    if (_status == PLAYER_1_PLACE){
        for (int i(0);i<4;++i){   
            for (int j(0);j<4;++j){
                if (sf::Mouse::getPosition(_window).x >= SPACE+(SPACE+WIDTH_PIECE)*i && sf::Mouse::getPosition(_window).x <= SPACE+WIDTH_PIECE+(SPACE+WIDTH_PIECE)*i && sf::Mouse::getPosition(_window).y >= HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*j && sf::Mouse::getPosition(_window).y <= HEIGHT_SCORE+HEIGHT_PIECE+SPACE+(SPACE+HEIGHT_PIECE)*j){
                    if (isPlacable(i,j)){
                        _spritePieces.setTextureRect(sf::IntRect(_pick*WIDTH_PIECE, 0, WIDTH_PIECE, HEIGHT_PIECE));
                        _spritePieces.setPosition(SPACE+(SPACE+WIDTH_PIECE)*i,HEIGHT_SCORE+SPACE+(SPACE+HEIGHT_PIECE)*j);
                        _window.draw(_spritePieces);
                    }
                }
            }
        }
    }
    _window.draw(_textQuarto);
    if (_status == PLAYER_1_PICK && _winner == 0){
        _text.setString("You pick");
        _text.setPosition(WIDTH_PLATEAU+WIDTH_PLATEAU/2-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }else if (_status == PLAYER_1_PLACE && _winner == 0){
        _text.setString("You place");
        _text.setPosition(WIDTH_PLATEAU/2-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }else if (_status == PLAYER_2_PICK && _winner == 0){
        _text.setString(_client->getNamePlayer2()+std::string(" picks"));
        _text.setPosition(WIDTH_PLATEAU+WIDTH_PLATEAU/2-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }else if (_status == PLAYER_2_PLACE && _winner == 0){
        _text.setString(_client->getNamePlayer2()+std::string(" places"));
        _text.setPosition(WIDTH_PLATEAU/2-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }else if (_winner == 1){
        _text.setString(std::string("YOU WIN"));
        _text.setPosition(WIDTH_PLATEAU-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }else if (_winner == 2){
        _text.setString(_client->getNamePlayer2()+std::string("WIN"));
        _text.setPosition(WIDTH_PLATEAU-_text.getLocalBounds().width/2,HEIGHT_SCORE-80);
        _window.draw(_text);
    }

    _window.display();
}

bool Quarto::isPlacable(int posX, int posY) const{
    for (int index=0;index<NUMBER_PIECES;++index){
        if (_posX[index] == posX && _posY[index] == posY && _used[index]){
            return false;
        } 
    }
    return true;
}