#include "Client.h"

#include <iostream>
#include <climits>

int main(int argc, char **argv) {
	if (argc != 4) {
		std::cerr << "Bad command line arguments\n";
		return 1;
	}
	
	char *endptr;
	errno = 0;
	long port = strtol(argv[2], &endptr, 10);
	if (errno != 0) {
		perror("bad port argument");
		return 1;
	}

	if (argv[2] == endptr) {
		std::cerr << "Bad port argument\n";
		return 1;
	}

	if (port <= 0 && port > USHRT_MAX) {
		std::cerr << "Bad port number\n";
		return 1;
	}
	
	long seconds = strtol(argv[3], &endptr, 10);
	if (errno != 0) {
		perror("bad request period argument");
		return 1;
	}

	if (argv[2] == endptr) {
		std::cerr << "Bad request period argument\n";
		return 1;
	}

	if (seconds <= 0) {
		std::cerr << "Bad connection period\n";
	}

	Client client(std::string(argv[1]), port, seconds);

	std::cout << "start client\n";
	return client.run();
}
