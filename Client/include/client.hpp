#ifndef __SERVER_HPP__
#define __SERVER_HPP__

/*---- LIBRARY ----*/
#include <iostream>
#include <string>

/*---- LIBRARY SFML ----*/
#include "SFML/Network.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"

class Client
{
public:
	Client();
	void initialize(ToReceive &data, std::string &nameP1, std::string &nameP2);
	bool receiveData(ToReceive &data);
	void sendData(const ToSend &data, const TypeSend &typeSend);
	
private:
	sf::UdpSocket _socket;
	sf::Packet _packetR;           // packet to receive
	sf::Packet _packetS;           // packet to send
	TypeReceive _typeReceive;
	unsigned short _port;
	sf::IpAddress _address;        // For the last sender
	unsigned short _portServer;
	sf::IpAddress _addressServer;  // For the server
	std::string _namePlayer2;

};

sf::Packet& operator >>(sf::Packet& packet, ToReceive& data);
sf::Packet& operator >>(sf::Packet& packet, TypeReceive& data);
sf::Packet& operator <<(sf::Packet& packet, const ToSend& data);
sf::Packet& operator <<(sf::Packet& packet, const TypeSend& data);

#endif // __SERVER_HPP__