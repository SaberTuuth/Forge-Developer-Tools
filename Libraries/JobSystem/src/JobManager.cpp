
#include "JobManager.h"
#include <iostream>

void JobManager::CreateJob(uint32_t id, const std::string& name, const std::string& command) {
	Job job(id, name, command);
	jobList.push_back(job);
}

void JobManager::ShowJobLists() {
	for(int i = 0; i < jobList.size(); i++) {
		Job& job = jobList[i];
		std::cout << "Job ID: " << job.id << ", Name: " << job.name << ", Command: " << job.command << ", Status: ";
		switch(job.status) {
			case JobStatus::Queued:
				std::cout << "Queued";
				break;
			case JobStatus::Assigned:
				std::cout << "Assigned";
				break;
			case JobStatus::InProgress:
				std::cout << "In Progress";
				break;
			case JobStatus::Testing:
				std::cout << "Testing";
				break;
			case JobStatus::Completed:
				std::cout << "Completed";
				break;
			case JobStatus::Failed:
				std::cout << "Failed";
				break;
		}
		std::cout << std::endl;
	}
}

void JobManager::RemoveJob(uint32_t id) {
	for(int i = 0; i < jobList.size(); i++) {
		if(jobList[i].id == id) {
			jobList.erase(jobList.begin() + i);
			return;
		}
	}
}

int JobManager::GetJobCount() const {
	return jobList.size();
}	

Job JobManager::GetJob(uint32_t id) {
	for(int i = 0; i < jobList.size(); i++) {
		if(jobList[i].id == id) {
			return jobList[i];
		}
	}
	return Job();
}

void JobManager::UpdateJobStatus(uint32_t id, JobStatus status) {
	for(int i = 0; i < jobList.size(); i++) {
		if(jobList[i].id == id) {
			jobList[i].status = status;
			return;
		}
	}
}