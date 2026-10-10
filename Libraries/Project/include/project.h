#pragma once

#include <string>
#include <unordered_set>
#include <vector>   

class Project {

    int id;
    std::string name;
    std::string key;            
    int ownerId;
    std::unordered_set<int> memberIds;
	std::vector<int> taskIds;

public:
    Project(int id, const std::string& name, const std::string& key, int ownerId);

    bool hasMember(int userId) const;

    std::unordered_set<int> getMemberIds() const {
        return memberIds;
	}
};