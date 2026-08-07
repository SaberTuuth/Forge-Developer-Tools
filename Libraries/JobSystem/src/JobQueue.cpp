
#include "JobQueue.h"

void JobQueue::PushJob(Job job) {
	jobs.push(job);
}

Job JobQueue::PopJob() {
	if (jobs.empty()) {
		return Job();
	}
	Job job = jobs.front();
	jobs.pop();
	return job;
}

bool JobQueue::isEmpty() const {
	return jobs.empty();
}

Job JobQueue::PeekJob() const {
	if (!jobs.empty()) {
		return jobs.front();
	}
}

int JobQueue::JobsWaiting() const {
	return jobs.size();
}