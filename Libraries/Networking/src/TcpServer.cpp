
#include "TcpServer.h"
#include <iostream>

TcpServer::TcpServer(int port) {
	this->port = port;

	// Initialize Winsock
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0)
	{
		std::cout << "WSAStartup failed: " << result << std::endl;
		exit(EXIT_FAILURE);
	}

	// create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == INVALID_SOCKET) {
		std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	// bind socket
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
}

TcpServer::~TcpServer() {
	closesocket(server_fd);
	WSACleanup();
}

void TcpServer::start() {
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void TcpServer::stop() {
	closesocket(server_fd);
}

void TcpServer::accept() {
	int addrlen = sizeof(address);
	SOCKET new_socket = ::accept(server_fd, (struct sockaddr*)&address, &addrlen);
	if (new_socket == INVALID_SOCKET) {
		std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Connection accepted" << std::endl;
}