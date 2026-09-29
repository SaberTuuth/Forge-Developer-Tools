#pragma once

#include <vector>
#include "Job.h"
#include "JobQueue.h"

class JobManager {

private:

	std::vector<Job> jobList;
	JobQueue jobQueue;

public:

	void CreateJob(uint32_t id, const std::string& name, const std::string& command);
	void ShowJobLists();
	void RemoveJob(uint32_t id);
	int GetJobCount() const;
	Job GetJob(uint32_t id);
	void UpdateJobStatus(uint32_t id, JobStatus status);
};