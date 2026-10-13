#pragma once

#include <memory>
#include <string>
#include <vector>
#include "database.h"
#include "user.h"

class UserRepository {

public:

	explicit UserRepository(Database& db);

    // Inserts a new user and returns it with the database-assigned id.
    // Throws DatabaseError if the username or email is already taken.
    std::shared_ptr<User> Create(const std::string& username, const std::string& email, const std::string& password);
    void Update(const User& user);
    std::shared_ptr<User> Load(int id);
    std::shared_ptr<User> LoadByUsername(const std::string& username);
    std::vector<std::shared_ptr<User>> LoadAll();
    void Remove(int id);

private:
    Database& Db;
};
