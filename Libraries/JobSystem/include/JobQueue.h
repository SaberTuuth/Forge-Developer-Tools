#pragma once

#include <queue>
#include <stdexcept>
#include "Job.h"

class JobQueue {

private:

	std::queue<Job> jobs;

public:

	void PushJob(Job job);
	Job PopJob();
	bool isEmpty() const;
	Job PeekJob() const;
	int JobsWaiting() const;
};