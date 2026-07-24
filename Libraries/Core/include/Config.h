#pragma once

#include <string>

class Config
{

public:

	Config() = default;

    std::string ServerIP = "127.0.0.1";

    uint16_t Port = 55000;

    uint32_t WorkerTimeout = 10;

    uint32_t MaxWorkers = 8;
};

