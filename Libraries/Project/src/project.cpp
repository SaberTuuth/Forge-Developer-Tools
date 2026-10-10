
#include "project.h"

Project::Project(int id, const std::string& name, const std::string& key, int ownerId)
: id(id), name(name), key(key), ownerId(ownerId) {
	memberIds.insert(ownerId); // Owner is also a member
}

bool Project::hasMember(int userId) const {
	return memberIds.count(userId) > 0;
}