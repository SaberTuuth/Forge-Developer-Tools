#pragma once

#include <string>
#include <winsock2.h>

class TcpClient
{

public:

    TcpClient();
    bool Connect(const std::string& ip, int port);
    void Disconnect();
    SOCKET GetSocket() const;

private:

    SOCKET clientSocket;
};