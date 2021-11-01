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
#include "home_page.hpp"

HomePage::HomePage(std::string name):_client(new Client),_quarto(name),_typeGame(NO_GAME),_name(name){

	_buttonQuarto.setSize(sf::Vector2f(WIDTH_BUTTON, HEIGHT_BUTTON));
	_buttonQuarto.setOutlineThickness(5);        	
	_buttonQuarto.setFillColor(sf::Color(216,154,86));
    _buttonQuarto.setOutlineColor(sf::Color(58,31,16));
	_buttonQuarto.setPosition(POS_BUTTON_X, POS_BUTTON_Y);

	if (!_font.loadFromFile("../content/font/eraslght.ttf"))
    {
        // error...
    }

    _text1.setFont(_font);
    _text1.setString("DIDOU'S GAMES");
    _text1.setFillColor(sf::Color::Black);
    _text1.setCharacterSize(80);
    _text1.setPosition(WIDTH_HOME_PAGE/2-_text1.getLocalBounds().width/2,10);

    _text2.setFont(_font);
    _text2.setString("Quarto");
    _text2.setFillColor(sf::Color::Black);
    _text2.setCharacterSize(50);
    _text2.setPosition(WIDTH_HOME_PAGE/2-_text2.getLocalBounds().width/2,POS_BUTTON_Y+10);
}

HomePage::~HomePage(){
	delete _client;
}


void HomePage::mainWindow(){
    _window.create(sf::VideoMode(WIDTH_HOME_PAGE, HEIGHT_HOME_PAGE),"Home page");
    _window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(true);
    while (_window.isOpen()){
    	// we process all the window events that have been generated since the last iteration of the loop
        while (_window.pollEvent(_event)){
            // Request for closing the window
            if (_event.type == sf::Event::Closed){
                _client->sendData(_send, LEAVE);
                _window.close();
            }
            if (_typeGame == NO_GAME && _event.type == sf::Event::MouseButtonPressed){
                if (_event.mouseButton.button == sf::Mouse::Left){
                	if (_event.mouseButton.x >= POS_BUTTON_X && _event.mouseButton.x <= POS_BUTTON_X+WIDTH_BUTTON && _event.mouseButton.y >= POS_BUTTON_Y && _event.mouseButton.y <= POS_BUTTON_Y+HEIGHT_BUTTON){
                		_typeGame = QUARTO;
                		_client->connectToServer(_name); // Connection with the server
                	}
                }
            }
        }

        if (_typeGame == NO_GAME){
        	_text1.setString("DIDOU'S GAMES");
        	_text2.setString("Quarto");
        	_text1.setPosition(WIDTH_HOME_PAGE/2-_text1.getLocalBounds().width/2,10);
        	_window.clear(sf::Color(255,198,141)); // We erase the windows
	        if (sf::Mouse::getPosition(_window).x >= POS_BUTTON_X && sf::Mouse::getPosition(_window).x <= POS_BUTTON_X+WIDTH_BUTTON && sf::Mouse::getPosition(_window).y >= POS_BUTTON_Y && sf::Mouse::getPosition(_window).y <= POS_BUTTON_Y+HEIGHT_BUTTON){
	        	_buttonQuarto.setFillColor(sf::Color(104,55,30));
	        	_buttonQuarto.setOutlineColor(sf::Color(216,154,86));
	        }else{
				_buttonQuarto.setFillColor(sf::Color(216,154,86));
			    _buttonQuarto.setOutlineColor(sf::Color(58,31,16));
	        }
	        _window.draw(_buttonQuarto);
	        _window.draw(_text1);
	        _window.draw(_text2);
	        _window.display();
        }else if (_typeGame == QUARTO){
     		_text1.setString("QUARTO");
        	_text2.setString("Number of players : "+std::to_string(_client->getNbrPlayer())+"/2");
    		_text1.setPosition(WIDTH_HOME_PAGE/2-_text1.getLocalBounds().width/2,10);
    		_text2.setPosition(WIDTH_HOME_PAGE/2-_text2.getLocalBounds().width/2,POS_BUTTON_Y+10);
        	_window.clear(sf::Color(255,198,141)); // We erase the windows
	        _window.draw(_text1);
	        _window.draw(_text2);
	        _window.display();
	        _client->receiveData(_receive);
	        if (_client->getReady()){
	        	_window.close();
	    		_quarto.play(_client);
	        }
        }
        
    }
}
