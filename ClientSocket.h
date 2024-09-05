#pragma once

#include <string>

class ClientSocket {
	unsigned short _port;
	int _tcpSocket;

	bool createConnection();
public:
	ClientSocket(unsigned short port);
	~ClientSocket();
	void send(const std::string &message);
};
