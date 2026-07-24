#pragma once

enum class Result
{
	Success = 0,
	Failure = 1,
	Timeout = 2,
	InvalidPacket = 3,
	AlreadyConnected = 4,
	FileNotFound = 5,
};