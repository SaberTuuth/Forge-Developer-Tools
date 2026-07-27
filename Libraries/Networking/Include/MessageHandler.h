#pragma once

#include <winsock2.h>
#include <cstdint>

enum class NetworkResult
{
    Success,
    Disconnected,
    Shutdown,
    Error,
    InvalidPacket,
    None
};

class MessageHandler
{
public:

    static int SendWhole(SOCKET socket,
        const char* data,
        int length);

    static int ReceiveWhole(SOCKET socket,
        char* buffer,
        int length);

    static NetworkResult SendMessage(SOCKET socket,
        const char* data,
        uint8_t length);

    static NetworkResult ReadMessage(SOCKET socket,
        char* buffer,
        int bufferSize,
        uint8_t& messageLength);
};