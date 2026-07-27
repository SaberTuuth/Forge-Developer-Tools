
#include <iostream>
#include "Config.h"
#include "TcpServer.h"
#include "TcpClient.h"

int main()
{
	Config config;

	TcpServer server(config.Port);
	server.start();

	std::cout << "Waiting for client..." << std::endl;

	server.accept();

	TcpClient client;

	client.Connect("127.0.0.1", config.Port);

    return 0;
}