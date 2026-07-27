
#include <iostream>
#include "TcpServer.h"
#include "Config.h"
#include "MessageHandler.h"

int main()
{
    Config config;

    TcpServer server(config.Port);

    server.start();

    std::cout << "Waiting for client...\n";


    while (true)
    {
        server.accept();

        std::cout << "Client connected!\n";

        char buffer[256];
        uint8_t length = 0;

        NetworkResult result = MessageHandler::ReadMessage(server.GetClientSocket(), buffer, sizeof(buffer), length);

        if (result == NetworkResult::Disconnected)
        {
            std::cout << "Client disconnected." << WSAGetLastError() << std::endl;
            result = NetworkResult::None;
			continue;
        }

        std::string message(buffer, length);

        std::cout << "Client: " << message << std::endl;

        MessageHandler::SendMessage(server.GetClientSocket(), message.c_str(), static_cast<uint8_t>(message.size()));
    }

    return 0;
}