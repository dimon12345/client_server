#pragma once

#include "ServerSocket.h"
#include "InputHandlerThread.h"
#include <memory>
#include <list>

class Server {
	ServerSocket _serverSocket;
	std::list<std::shared_ptr<InputHandlerThread>> _handlers;

	void handleInputConnection(int clientSocket);
	void cleanupHandlers();
public:
	Server(unsigned short port);
	int run();
};
