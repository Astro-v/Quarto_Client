/*---- LIBRARY ----*/
#include <iostream>
#include <string>

/*---- LIBRARY SFML ----*/
#include "SFML/Network.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "client.hpp"

Client::Client():_addressServer(SERVER_ADRESS),_portServer(SERVER_PORT),_nbrPlayer(0),_playing(false){
	_packetR.clear();
	_packetS.clear();
}

/*
Wait until the two player connect to the server
*/
void Client::connectToServer(std::string &name){
	++_nbrPlayer;
	_socket.setBlocking(true);

	// Connection to the server
	if (_socket.connect(_addressServer,_portServer) != sf::Socket::Done){
		// error
	}
	_packetS.clear();
	_packetS << CONNECT_CLIENT << name;
	_socket.send(_packetS);
	_packetS.clear();
	_socket.setBlocking(false);
}

void Client::initialize(ToReceive &data){
	_socket.setBlocking(true);
	receiveData(data);
	_socket.setBlocking(false);
}

TypeReceive Client::receiveData(ToReceive &data){
	_packetR.clear();
	if (_socket.receive(_packetR) == sf::Socket::Done){
		// we received something
		_packetR >> _typeReceive;
		if (_typeReceive == GAME_SERVER){
			_packetR >> data;
		}else if (_typeReceive == CONNECT_SERVER){
			_packetR >> _namePlayer2;
			_playing = true;
			++_nbrPlayer;
		}else if (_typeReceive == WIN_P1){
			_packetR >> data;
		}else if (_typeReceive == WIN_P2){
			_packetR >> data;
		}
		_packetR.clear();
		return _typeReceive; // the sender is the server
	}
	_packetR.clear();
	return NOTHING; // No data received
}

void Client::sendData(const ToSend &data, const TypeSend &typeSend){
	_packetS.clear();
	_packetS << typeSend << data;
	_socket.send(_packetS); // send to the server
	_packetS.clear();
}

std::string Client::getNamePlayer2(){
	return _namePlayer2;
}

bool Client::getReady() const{
	return _playing;
}

int Client::getNbrPlayer() const{
	return _nbrPlayer;
}

sf::Packet& operator >>(sf::Packet& packet, ToReceive& data){
	int status;
    packet >> status;
    data.status = (Status)status;
    for (int index=0;index<NUMBER_PIECES;++index){
    	packet >> data.posX[index];
    }
    for (int index=0;index<NUMBER_PIECES;++index){
    	packet >> data.posY[index];
    }
    for (int index=0;index<NUMBER_PIECES;++index){
    	packet >> data.used[index];
    }
    return packet >> data.pick;
}

sf::Packet& operator >>(sf::Packet& packet, TypeReceive& data){
	int receive;
	packet >> receive;
	data = (TypeReceive)receive;
    return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const ToSend& data){
    return packet << data.posX << data.posY;
}

sf::Packet& operator <<(sf::Packet& packet, const TypeSend& data){
	int send;
	send = (int)data;
    return packet << send;
}