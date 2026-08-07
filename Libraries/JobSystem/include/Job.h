#pragma once

#include <string>

enum class JobStatus {
	Queued,
	Assigned,
	InProgress,
	Testing,
	Completed,
	Failed
};
class Job {
public:

	uint32_t id;
	std::string name;
	std::string command;
	JobStatus status;

	Job() = default;
	Job(uint32_t id, const std::string& name, const std::string& command);
};