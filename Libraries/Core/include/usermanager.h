
#pragma once

#include <unordered_map>
#include <memory>
#include "user.h"

class UserManager
{
public:
    std::shared_ptr<User> CreateUser(int id, const std::string& username, const std::string& email, const std::string& password);

    void AddUser(std::shared_ptr<User> user);

    std::shared_ptr<User> GetUser(int id);

    std::shared_ptr<User> FindByUsername(const std::string& username);

    void RemoveUser(int id);

private:
    std::unordered_map<int, std::shared_ptr<User>> m_Users;
};
