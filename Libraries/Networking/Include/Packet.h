#pragma once

#include <vector>
#include <cstddef>
#include "PacketType.h"

struct Packet
{
    PacketType Type;

    std::vector<std::byte> Data;
};