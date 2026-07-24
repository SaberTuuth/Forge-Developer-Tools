#pragma once

enum class PacketType
{
    Connect,
    Disconnect,

    Heartbeat,

    JobRequest,

    JobProgress,

    JobComplete,

    LogMessage,

    Error
};