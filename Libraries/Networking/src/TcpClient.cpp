
#include "TcpClient.h"
#include <iostream>

TcpClient::TcpClient() : clientSocket(INVALID_SOCKET) {}

bool TcpClient::Connect(const std::string& ip, int port)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cout << "Connection error " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return false;
	}
	std::cout << "accepted client\n";
	return true;
}

void TcpClient::Disconnect()
{
	if (clientSocket != INVALID_SOCKET)
	{
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}
	WSACleanup();
}

SOCKET TcpClient::GetSocket() const
{
	return clientSocket;
}
