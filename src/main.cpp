
#include <iostream>
#include "Config.h"
#include "TcpServer.h"

int main()
{
	Config config;

	TcpServer server(config.Port);
	server.start();
	std::cout << "Waiting for client..." << std::endl;

	server.accept();

    return 0;
}