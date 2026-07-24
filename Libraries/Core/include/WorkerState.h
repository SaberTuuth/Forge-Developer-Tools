#pragma once

enum class WorkerState
{
	Offline = 0,
	Connecting = 1,
	Idle = 2,
	Busy = 3,
	Error = 4,
};