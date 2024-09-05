#include "Client.h"

#include "ClientSocket.h"

#include <iomanip>

#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>

Client::Client(
		std::string &&name,
		unsigned short port,
		int connection_period
) : _name(std::move(name)), _port(port), _connection_period(connection_period) {
}
	
int Client::run() {

	while(true) {
		auto now = std::chrono::system_clock::now();

		auto millis = (now.time_since_epoch().count() / 1000000) % 1000;

		auto time_t_time = std::chrono::system_clock::to_time_t(now);
		auto tm = *std::localtime(&time_t_time);

		std::ostringstream oss;
		oss
			<< std::put_time(&tm, "[%Y-%m-%d %H:%M:%S")
			<< "." << millis
			<< "] " << _name;

		ClientSocket tcpSocket(_port);
		tcpSocket.send(oss.str());

		if (_connection_period > 0) {
			std::this_thread::sleep_for(std::chrono::seconds(_connection_period));
		}
	}

	return 0;
}
