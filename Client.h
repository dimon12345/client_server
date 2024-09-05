#pragma once

#include <string>

class Client {
	std::string _name;
	unsigned short _port;
	int _connection_period;

public:	
	Client(
		std::string &&name,
		unsigned short port,
		int connection_period
	);
	
	int run();
};
