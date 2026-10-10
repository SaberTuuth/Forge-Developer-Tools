
#include "ProjectManager.h"

int ProjectManager::create(const std::string& name, const std::string& key, int ownerId) {
	std::lock_guard<std::mutex> lock(mtx);
	int projectId = nextId++;
	Project newProject(projectId, name, key, ownerId);
	projects.emplace(projectId, std::move(newProject));
	return projectId;
}

bool ProjectManager::remove(int projectId, int requesterId) {
	std::lock_guard<std::mutex> lock(mtx);
	auto it = projects.find(projectId);
	if (it != projects.end() && it->second.hasMember(requesterId)) {
		projects.erase(it);
		return true;
	}
	return false;
}

bool ProjectManager::addMember(int projectId, int userId, int requesterId) {
	std::lock_guard<std::mutex> lock(mtx);
	auto it = projects.find(projectId);
	if (it != projects.end() && it->second.hasMember(requesterId)) {
		it->second.getMemberIds().insert(userId);
		return true;
	}
	return false;
}

bool ProjectManager::removeMember(int projectId, int userId, int requesterId) {
	std::lock_guard<std::mutex> lock(mtx);
	auto it = projects.find(projectId);
	if (it != projects.end() && it->second.hasMember(requesterId)) {
		it->second.getMemberIds().erase(userId);
		return true;
	}
	return false;
}

std::vector<const Project*> ProjectManager::listForUser(int userId) const {
	std::lock_guard<std::mutex> lock(mtx);
	std::vector<const Project*> userProjects;
	for (const auto& [id, project] : projects) {
		if (project.hasMember(userId)) {
			userProjects.push_back(&project);
		}
	}
	return userProjects;
}

const Project* ProjectManager::get(int projectId) const {
	std::lock_guard<std::mutex> lock(mtx);
	auto it = projects.find(projectId);
	if (it != projects.end()) {
		return &it->second;
	}
	return nullptr;
}