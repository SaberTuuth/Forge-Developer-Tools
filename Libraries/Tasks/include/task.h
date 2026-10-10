
#pragma once

#include <string>
#include <optional>

enum class TaskStatus { 
	Todo,
	InProgress,
	InReview, 
	Done
};

enum class TaskPriority { 
	Low, 
	Medium,
	High, 
	Critical 
};

class Task {

public:

	int id;
	int projectId;
	std::string title;
	std::string description;
	int creatorId;
	std::optional<int> assigneeId;
	TaskStatus status = TaskStatus::Todo;
	TaskPriority priority = TaskPriority::Medium;

	Task(int id, int projectId, const std::string& title, const std::string& description, int creatorId, std::optional<int> assigneeId = std::nullopt, TaskStatus status = TaskStatus::Todo, TaskPriority priority = TaskPriority::Medium);
};