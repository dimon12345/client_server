#pragma once

#include "LineLogger.h"

#include <thread>

class InputHandlerThread {
	std::thread _thread;
	volatile int _clientSocket;
	static LineLogger _lineLogger;

	void handleInternal();
public:
	InputHandlerThread(int clientSocket);
	~InputHandlerThread();
	bool handle();
	inline bool isConnectionClosed() { return _clientSocket == -1; }
};
