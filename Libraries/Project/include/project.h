#pragma once

#include <string>
#include <unordered_set>

class Project {

    int id;
    std::string name;
    std::string key;            
    int ownerId;
    std::unordered_set<int> memberIds;

    bool hasMember(int userId) const;
};