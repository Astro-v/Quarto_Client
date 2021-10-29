#ifndef __SERVER_HPP__
#define __SERVER_HPP__

/*---- LIBRARY ----*/
#include <iostream>

/*---- LIBRARY SFML ----*/
#include "SFML/Network.hpp"

/*---- LOCAL FILE ----*/
#include "constant.hpp"

class Client
{
public:
	Client();
	void initialize(ToReceive &data);
	bool receiveData(ToReceive &data);
	void sendData(const ToSend &data);
	
private:
	sf::UdpSocket _socket;
	sf::Packet _packetR;           // packet to receive
	sf::Packet _packetS;           // packet to send
	unsigned short _port;
	sf::IpAddress _address;        // For the last sender
	unsigned short _portServer;
	sf::IpAddress _addressServer;  // For the server

};

sf::Packet& operator >>(sf::Packet& packet, ToReceive& data);
sf::Packet& operator <<(sf::Packet& packet, const ToSend& data);

#endif // __SERVER_HPP__