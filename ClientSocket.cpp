#include "ClientSocket.h"

#include <unistd.h>
#include <strings.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>

const int INVALID_SOCKET_VALUE = -1;

ClientSocket::ClientSocket(unsigned short port)
	: _port(port), _tcpSocket(INVALID_SOCKET_VALUE)
{
}

ClientSocket::~ClientSocket()
{
	if (_tcpSocket != INVALID_SOCKET_VALUE) {
		close(_tcpSocket);
	}
}

bool ClientSocket::createConnection()
{
	if (_tcpSocket > 0) {
		return true;
	}
	
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	
	struct hostent *hp = gethostbyname("localhost");
	if (hp == NULL) {
		perror("Can't resolve localhost");
		return false;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	bcopy(&(addr.sin_addr), hp->h_addr, hp->h_length);

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET_VALUE) {
		perror("Can't create socket");
		return false;
	}
	
	if (connect(s, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) == -1) {
		perror("Can't connect");
		close(s);
		return false;
	}

	_tcpSocket = s;
	return true;
}

void ClientSocket::send(const std::string &message)
{
	if (_tcpSocket < 0) {
		if(!createConnection()) {
			perror("Can't connect");
			return;
		}
	}
	
	write(_tcpSocket, message.c_str(), message.size());
}
