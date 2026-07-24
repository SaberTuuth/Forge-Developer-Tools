#pragma once

#include <WS2tcpip.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

class TcpServer
{

private:

    int server_fd;
    int port;
    sockaddr_in address;

public:
    TcpServer(int port);
    ~TcpServer();
    void start();
	void stop();
    void accept();


};