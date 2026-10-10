
#include "task.h"

Task::Task(int id, int projectId, const std::string& title, const std::string& description, int creatorId, std::optional<int> assigneeId, TaskStatus status, TaskPriority priority)
	: id(id), projectId(projectId), title(title), description(description), creatorId(creatorId), assigneeId(assigneeId), status(status), priority(priority) {
}