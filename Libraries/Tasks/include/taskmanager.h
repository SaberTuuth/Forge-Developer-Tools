
#pragma once

#include <vector>
#include "task.h"

class TaskManager {

	public:
	std::vector<Task> tasks;
	void addTask(const Task& task);
	void removeTask(int taskId);
	Task* getTask(int taskId);
	std::vector<Task> getTasksByProject(int projectId);
	std::vector<Task> getTasksByAssignee(int assigneeId);
	std::vector<Task> getTasksByStatus(TaskStatus status);
	std::vector<Task> getTasksByPriority(TaskPriority priority);

};