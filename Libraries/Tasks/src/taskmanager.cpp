
#include "taskmanager.h"

void TaskManager::addTask(const Task& task) {
	tasks.push_back(task);
}

void TaskManager::removeTask(int taskId) {
	tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [taskId](const Task& task) {
		return task.id == taskId;
	}), tasks.end());
}

Task* TaskManager::getTask(int taskId) {
	auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& task) {
		return task.id == taskId;
	});
	return it != tasks.end() ? &(*it) : nullptr;
}

std::vector<Task> TaskManager::getTasksByProject(int projectId) {
	std::vector<Task> result;
	for (const auto& task : tasks) {
		if (task.projectId == projectId) {
			result.push_back(task);
		}
	}
	return result;
}

std::vector<Task> TaskManager::getTasksByAssignee(int assigneeId) {
	std::vector<Task> result;
	for (const auto& task : tasks) {
		if (task.assigneeId && *task.assigneeId == assigneeId) {
			result.push_back(task);
		}
	}
	return result;
}

std::vector<Task> TaskManager::getTasksByStatus(TaskStatus status) {
	std::vector<Task> result;
	for (const auto& task : tasks) {
		if (task.status == status) {
			result.push_back(task);
		}
	}
	return result;
}

std::vector<Task> TaskManager::getTasksByPriority(TaskPriority priority) {
	std::vector<Task> result;
	for (const auto& task : tasks) {
		if (task.priority == priority) {
			result.push_back(task);
		}
	}
	return result;
}

