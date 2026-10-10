
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include "Project.h"

class ProjectManager {

public:
    int create(const std::string& name, const std::string& key, int ownerId);
    bool remove(int projectId, int requesterId);          // owner only
    bool addMember(int projectId, int userId, int requesterId);
    bool removeMember(int projectId, int userId, int requesterId);
    std::vector<const Project*> listForUser(int userId) const;
    const Project* get(int projectId) const;

private:
    std::unordered_map<int, Project> projects;
    int nextId = 1;
    mutable std::mutex mtx;
};