
#include <iostream>
#include "TcpClient.h"
#include "Config.h"
#include "MessageHandler.h"
#include "User.h"


int main()
{
	Config config;

	TcpClient client;

	client.Connect(config.ServerIP, config.Port);
	while (true)
	{
		std::string message;

		std::cout << "> ";
		std::getline(std::cin, message);
		
		if (message == "quit") {
			client.Disconnect();
			break;
		}

		MessageHandler::SendMessage(client.GetSocket(), message.c_str(), static_cast<uint8_t>(message.size()));

		char buffer[256];
		uint8_t length = 0;

		NetworkResult result = MessageHandler::ReadMessage(client.GetSocket(), buffer, sizeof(buffer), length);

		if (result != NetworkResult::Success)
		{
			std::cout << "Server disconnected.\n";
			break;
		}

		std::string response(buffer, length);

		std::cout << "Server: " << response << std::endl;

		std::string heartbeatMessage = "PING\n";

		if(response == heartbeatMessage) {
			std::cout << "Received heartbeat from server." << std::endl;
			MessageHandler::SendMessage(client.GetSocket(), "PONG\n", 5);
		}
	}

	return 0;
}