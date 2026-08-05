#pragma once

#include <string>
#include <winsock2.h>
#include "HeartBeat.h"

class TcpClient
{

public:

    TcpClient();
    bool Connect(const std::string& ip, int port);
    void Disconnect();
    SOCKET GetSocket() const;
    HeartBeat GetHeartBeat() const;

private:

    SOCKET clientSocket;
    HeartBeat heartbeat;
};