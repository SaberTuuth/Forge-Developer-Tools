
#include <iostream>
#include "TcpServer.h"
#include "Config.h"
#include "MessageHandler.h"

int main()
{
	Config config;

	TcpServer server(config.Port);
	if (server.Listen()) {

		std::cout << "Waiting for client...\n";

		while (true)
		{
			server.Update();
		}
	}
	return 0;
}