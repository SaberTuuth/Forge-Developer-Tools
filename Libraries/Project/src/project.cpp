
#include "project.h"

bool Project::hasMember(int userId) const {
	return memberIds.count(userId) > 0;
}