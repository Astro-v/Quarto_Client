/*---- LIBRARY ----*/
#include <iostream>

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
void Client::initialize(ToReceive &dataR){
	_socket.setBlocking(true);

	// Connection to the server
	std::cout << "connecting to server" << std::endl;
	_packetS.clear();
	ToSend dataS = {0,0};
	_packetS << dataS;
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
			_packetR >> data;
			_packetR.clear();
			return true; // the sender is the server
		}else{
			// error 
		}
	}
	_packetR.clear();
	return false; // No data received
}


void Client::sendData(const ToSend &data){
	_packetS.clear();
	_packetS << data;
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

sf::Packet& operator <<(sf::Packet& packet, const ToSend& data){
    return packet << data.posX << data.posY;
}