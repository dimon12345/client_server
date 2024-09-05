#include "InputHandlerThread.h"

#include <iostream>
#include <cassert>

#include <unistd.h>

static const int INTERNAL_BUFFER_SIZE = 1024;

LineLogger InputHandlerThread::_lineLogger;

InputHandlerThread::InputHandlerThread(int clientSocket)
	: _clientSocket(clientSocket)
{
}

InputHandlerThread::~InputHandlerThread()
{
	_thread.join();
}

bool InputHandlerThread::handle()
{
	assert(_clientSocket != -1);
	if (_clientSocket == -1) {
		std::cerr << "bad call\n";
		return false;
	}
	auto functor = [this]() { handleInternal(); };

	_thread = std::thread(functor);

	return true;
}

void InputHandlerThread::handleInternal()
{
	std::string result;
	char buff[INTERNAL_BUFFER_SIZE];

	int readen = INTERNAL_BUFFER_SIZE;
	while(readen > 0) {
		readen = read(_clientSocket, buff, INTERNAL_BUFFER_SIZE);
		result += std::string(buff, readen);
	}

	_lineLogger.addLine(result);
	close(_clientSocket);
	_clientSocket = -1;
}	
