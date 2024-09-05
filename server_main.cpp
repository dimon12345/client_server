#include "Server.h"

#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Bad command line arguments\n";
		return 1;
	}
	
	char *endptr;
	errno = 0;
	long port = strtol(argv[1], &endptr, 10);
	if (errno != 0) {
		perror("bad port argument");
		return 1;
	}
	
	Server server(port);
	
	return server.run();
}
