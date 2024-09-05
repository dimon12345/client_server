#pragma once

#include <netinet/in.h>

class ServerSocket {
	unsigned short _port;
	struct sockaddr_in _c_ain;
	int _serverSocket;
	socklen_t _clientAddrSize = sizeof(_c_ain);
public:
	ServerSocket(unsigned short port);
	bool listenClient();
	int acceptInputConnection();
};
