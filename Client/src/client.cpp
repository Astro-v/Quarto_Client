/*---- LIBRARY ----*/
#include <iostream>
#include <string>

/*---- LIBRARY SFML ----*/
#include "SFML/Network.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "client.hpp"

Client::Client():_addressServer(SERVER_ADRESS),_portServer(SERVER_PORT){
	if (_socket.bind(sf::Socket::AnyPort) != sf::Socket::Done){
    	// error...
	}
	_packetR.clear();
	_packetS.clear();
}

/*
Wait until the two player connect to the server
*/
void Client::initialize(ToReceive &dataR, std::string &nameP1, std::string &nameP2){
	_socket.setBlocking(true);

	// Connection to the server
	std::cout << "connecting to server" << std::endl;
	_packetS.clear();
	_packetS << CONNECT_CLIENT << nameP1;
	if (_socket.send(_packetS,_addressServer,_portServer) != sf::Socket::Done){
		// error
	}
	_packetS.clear();

	std::cout << "Waiting for other player" << std::endl;
	// Waiting the server for begin
	receiveData(dataR);

	_socket.setBlocking(false);
}

bool Client::receiveData(ToReceive &data){
	_packetR.clear();
	if (_socket.receive(_packetR,_address,_port) == sf::Socket::Done){
		// we received something
		if (_addressServer == _address && _portServer == _port){
			_packetR >> _typeReceive;
			if (_typeReceive == GAME_SERVER){
				_packetR >> data;
			}else if (_typeReceive == CONNECT_SERVER){
				_packetR >> _namePlayer2;
			}else if (_typeReceive == WIN_P1){

			}else if (_typeReceive == WIN_P2){

			}
			_packetR.clear();
			return true; // the sender is the server
		}
	}
	_packetR.clear();
	return false; // No data received
}


void Client::sendData(const ToSend &data, const TypeSend &typeSend){
	_packetS.clear();
	_packetS << typeSend << data;
	_socket.send(_packetS, _addressServer, _portServer); // send to the server
	_packetS.clear();
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