
#include "job.h"

Job::Job(uint32_t id, const std::string& name, const std::string& command)
	: id(id), name(name), command(command), status(JobStatus::Queued) {
}