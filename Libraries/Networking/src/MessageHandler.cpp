
#include "MessageHandler.h"
#include <iostream>

int MessageHandler::SendWhole(SOCKET socket, const char* data, int length)
{
    int totalSent = 0;

    while (totalSent < length)
    {
        int result = send(socket, data + totalSent, length - totalSent, 0);

        if (result <= 0)
        {
            return result;
        }

        totalSent += result;
    }

    return totalSent;
}

int MessageHandler::ReceiveWhole(SOCKET socket, char* buffer, int length)
{
    int totalReceived = 0;

    while (totalReceived < length)
    {
        int result = recv(socket, buffer + totalReceived, length - totalReceived, 0);

        if (result == 0)
        {
            // Client disconnected normally
            return 0;
        }

        if (result == SOCKET_ERROR)
        {
            return SOCKET_ERROR;
        }

        totalReceived += result;
    }

    return totalReceived;
}

NetworkResult MessageHandler::SendMessage(SOCKET socket, const char* data, uint8_t length)
{
    if (length == 0)
    {
        return NetworkResult::InvalidPacket;
    }

    int result = SendWhole(socket, reinterpret_cast<const char*>(&length), sizeof(length));

    if (result <= 0)
    {
        int error = WSAGetLastError();

        if (error == WSAESHUTDOWN)
            return NetworkResult::Shutdown;

        if (result == 0)
            return NetworkResult::Disconnected;

        return NetworkResult::Error;
    }

    result = SendWhole(socket, data, length);

    if (result <= 0)
    {
        int error = WSAGetLastError();

        if (error == WSAESHUTDOWN)
            return NetworkResult::Shutdown;

        if (result == 0)
            return NetworkResult::Disconnected;

        return NetworkResult::Error;
    }

    return NetworkResult::Success;
}

NetworkResult MessageHandler::ReadMessage(SOCKET socket, char* buffer, int bufferSize, uint8_t& messageLength)
{
    messageLength = 0;

    int result = ReceiveWhole(socket, reinterpret_cast<char*>(&messageLength), sizeof(messageLength));

    if (result <= 0)
    {
        int error = WSAGetLastError();

        if (error == WSAESHUTDOWN)
            return NetworkResult::Shutdown;

        if (result == 0)
            return NetworkResult::Disconnected;

        return NetworkResult::Error;
    }

    if (messageLength > bufferSize)
    {
        return NetworkResult::InvalidPacket;
    }

    result = ReceiveWhole(socket, buffer, messageLength);

    if (result <= 0)
    {
        int error = WSAGetLastError();

        if (error == WSAESHUTDOWN)
            return NetworkResult::Shutdown;

        if (result == 0)
            return NetworkResult::Disconnected;

        return NetworkResult::Error;
    }

    return NetworkResult::Success;
}