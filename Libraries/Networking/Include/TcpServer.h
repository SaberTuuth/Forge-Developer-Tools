#pragma once

#include <WS2tcpip.h>
#include <winsock2.h>
#include <vector>
#include "HeartBeat.h"

#pragma comment(lib, "Ws2_32.lib")

class TcpServer
{

private:

	int server_fd;
	int port;
	sockaddr_in address;
	std::vector<SOCKET> clients;
	fd_set masterSet;
	fd_set readySet;
	SOCKET ListenSocket;
	HeartBeat heartbeat;

public:
	TcpServer(int port);
	~TcpServer();
	bool Listen();
	void stop();
	SOCKET GetClientSocket() const;
	void Update();
	void AcceptClient();
	void ReceiveClient(SOCKET clientSocket);
	HeartBeat GetHeartBeat() const;
	void RemoveClient(SOCKET clientSocket);
};