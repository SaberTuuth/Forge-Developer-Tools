#pragma once

#include <unordered_map>
#include <memory>
#include "user.h"
#include "userrepository.h"

class UserManager
{
public:
    explicit UserManager(UserRepository& repo);

    // The id is assigned by the database. Throws DatabaseError if the username or email is taken.
    std::shared_ptr<User> CreateUser(const std::string& username, const std::string& email, const std::string& password);

    std::shared_ptr<User> GetUser(int id);

    std::shared_ptr<User> FindByUsername(const std::string& username);

    void UpdateUser(const User& user);

    void RemoveUser(int id);

private:
    UserRepository& m_Repo;
    std::unordered_map<int, std::shared_ptr<User>> m_Users;
};
