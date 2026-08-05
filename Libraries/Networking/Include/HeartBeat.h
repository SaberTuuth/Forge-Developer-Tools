
#pragma once

#include <chrono>

class HeartBeat
{
private:

    std::chrono::steady_clock::time_point lastReceived;
    std::chrono::steady_clock::time_point lastSent;

public:

    HeartBeat();
    void Reset();
    bool IsExpired(float timeoutSeconds) const;
    bool ShouldSend(float intervalSeconds) const;

};