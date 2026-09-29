
#include "TcpServer.h"
#include <iostream>
#include <sstream>
#include "MessageHandler.h"

TcpServer::TcpServer(int port) : authManager(userManager) {
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

	userManager.CreateUser(1, "Alice", "alice@example.com", "password");
	userManager.CreateUser(2, "Bob", "bob@example.com", "password");
	userManager.CreateUser(3, "Charlie", "charlie@example.com", "password");
}

TcpServer::~TcpServer() {
	closesocket(server_fd);
	WSACleanup();
}

bool TcpServer::Listen() {
	ListenSocket = listen(server_fd, SOMAXCONN);

	if (ListenSocket == SOCKET_ERROR)
	{
		return false;
	}

	FD_ZERO(&masterSet);
	FD_SET(server_fd, &masterSet);
	FD_ZERO(&readySet);

	return true;
}

void TcpServer::stop() {
	for (SOCKET client : clients)
		closesocket(client);

	clients.clear();

	closesocket(server_fd);
}

SOCKET TcpServer::GetClientSocket() const {
	if (!clients.empty()) {
		return clients.back();
	}
	return INVALID_SOCKET;
}

void TcpServer::Update() {
	readySet = masterSet;

	timeval timeout{};
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	int readySockets =
		select(0, &readySet, nullptr, nullptr, &timeout);

	if (readySockets == SOCKET_ERROR)
		return;

	for (u_int i = 0; i < readySet.fd_count; i++)
	{
		SOCKET socket = readySet.fd_array[i];

		if (socket == server_fd)
		{
			AcceptClient();
		}
		else
		{
			ReceiveClient(socket);
		}
	}

	if (heartbeat.ShouldSend(3.0f)) {
		for (SOCKET client : clients) {
			const char* heartbeatMessage = "PING\n";
			MessageHandler::SendMessageA(client, heartbeatMessage, static_cast<uint8_t>(strlen(heartbeatMessage)));
		}
	}
}

void TcpServer::AcceptClient() {
	int addrlen = sizeof(address);
	SOCKET clientSocket = ::accept(server_fd, (struct sockaddr*)&address, &addrlen);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
		return;
	}
	std::cout << "Connection accepted" << std::endl;
	clients.push_back(clientSocket);
	FD_SET(clientSocket, &masterSet);
}

void TcpServer::ReceiveClient(SOCKET clientSocket) {
	char buffer[256];
	uint8_t messageLength = 0;

	NetworkResult result = MessageHandler::ReadMessage(clientSocket, buffer, sizeof(buffer) - 1, messageLength);
	if (result == NetworkResult::Success) {
		buffer[messageLength] = '\0';
	}
	std::string command = buffer;

	switch (result)
	{
	case NetworkResult::Success:
		if (command.rfind("login ", 0) == 0) {
			std::istringstream iss(command.substr(6));
			std::string username, password;
			iss >> username >> password;

			int userId = -1;
			LoginResult loginResult = authManager.Login(username, password, userId);

			std::string response;
			switch (loginResult) {
			case LoginResult::Success:
				loggedInUsers[clientSocket] = userId;
				response = "Login successful. Welcome, " + username + "!\n";
				break;
			case LoginResult::UserNotFound:
				response = "Login failed: user not found.\n";
				break;
			case LoginResult::InvalidCredentials:
				response = "Login failed: invalid credentials.\n";
				break;
			case LoginResult::AlreadyLoggedIn:
				response = "Login failed: already logged in.\n";
				break;
			}
			MessageHandler::SendMessage(clientSocket, response.c_str(), static_cast<uint8_t>(response.size()));
			break;
		}
		if (command.rfind("logout", 0) == 0) {
			auto it = loggedInUsers.find(clientSocket);
			std::string response;
			if (it != loggedInUsers.end()) {
				authManager.Logout(it->second);
				loggedInUsers.erase(it);
				response = "Logged out.\n";
			}
			else {
				response = "Not logged in.\n";
			}
			MessageHandler::SendMessage(clientSocket, response.c_str(), static_cast<uint8_t>(response.size()));
			break;
		}
		if (command.find("show") != std::string::npos) {
			jobManager.ShowJobLists();
			break;
		}
		std::cout << "Received data from client: "
			<< std::string(buffer, messageLength)
			<< std::endl;
		break;

	case NetworkResult::Disconnected:
		std::cout << "Client disconnected." << std::endl;
		RemoveClient(clientSocket);
		break;

	case NetworkResult::Shutdown:
		std::cout << "Client shutdown." << std::endl;
		RemoveClient(clientSocket);
		break;

	case NetworkResult::InvalidPacket:
		std::cout << "Invalid packet received." << std::endl;
		break;

	case NetworkResult::Error:
	default:
		std::cout << "ReadMessage failed." << std::endl;
		break;
	}
}

HeartBeat TcpServer::GetHeartBeat() const {
	return heartbeat;
}

void TcpServer::RemoveClient(SOCKET clientSocket) {
	closesocket(clientSocket);
	FD_CLR(clientSocket, &masterSet);
	clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());

	auto it = loggedInUsers.find(clientSocket);
	if (it != loggedInUsers.end()) {
		authManager.Logout(it->second);
		loggedInUsers.erase(it);
	}
}