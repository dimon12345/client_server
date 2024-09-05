#include "ServerSocket.h"

#include <strings.h>
#include <stdio.h>

static const int BACKLOG_CONNECTIONS_COUNT = 10;

ServerSocket::ServerSocket(unsigned short port)
	: _port(port)
{
}

bool ServerSocket::listenClient()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == -1) {
		perror("Can't create socket");
		return false;
	}
	
	struct sockaddr_in s_ain;
	bzero((char *)&s_ain, sizeof(s_ain));
	s_ain.sin_family = AF_INET;
	s_ain.sin_addr.s_addr = INADDR_ANY;
	s_ain.sin_port = htons(_port);

	if(bind(_serverSocket, (struct sockaddr *)&s_ain, sizeof(s_ain)) == -1) {
		perror("Can't bind socket");
		return false;
	}
	
	if(listen(_serverSocket, BACKLOG_CONNECTIONS_COUNT) == -1) {
		perror("Listen failed");
		return false;
	}

	return true;
}

int ServerSocket::acceptInputConnection()
{
	_clientAddrSize = sizeof(_c_ain);
	int clientSocket = accept(_serverSocket, reinterpret_cast<struct sockaddr *>(&_c_ain), &_clientAddrSize);
	if (clientSocket == -1) {
		perror("Can't accept connection");
		return -1;
	}
	return clientSocket;
}
