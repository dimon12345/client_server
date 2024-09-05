#include "Server.h"

#include <iostream>
#include <algorithm>

#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


Server::Server(unsigned short port)
	: _serverSocket(port)
{
}

int Server::run()
{
	if (!_serverSocket.listenClient()) {
		std::cerr << "Can't start server\n";
		return 1;
	}
	
	std::cout << "Server running\n";

	while(true) {
		
		int clientSocket = _serverSocket.acceptInputConnection();
		if (clientSocket == -1) {
			continue;
		}

		auto clientHandlerThread = std::make_shared<InputHandlerThread>(clientSocket);
		clientHandlerThread->handle();
		_handlers.push_back(clientHandlerThread);
		cleanupHandlers();
	}

	return 0;
}

void Server::cleanupHandlers() {
	std::list<std::shared_ptr<InputHandlerThread>> updatedList;
	
	std::copy_if(_handlers.begin(), _handlers.end(), std::back_inserter(updatedList),[](auto val) {
		return !val->isConnectionClosed();
	});
	
	_handlers = updatedList;
}
