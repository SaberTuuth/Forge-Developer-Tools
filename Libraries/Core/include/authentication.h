
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "user.h"

class UserManager;

enum class LoginResult
{
    Success,
    UserNotFound,
    InvalidCredentials,
    AlreadyLoggedIn
};

class AuthManager
{
public:
    explicit AuthManager(UserManager& userManager);

    LoginResult Login(const std::string& username, const std::string& password, int& outUserId);

    void Logout(int userId);

    bool IsLoggedIn(int userId) const;

    std::shared_ptr<User> GetLoggedInUser(int userId) const;

private:
    UserManager& m_UserManager;
    std::unordered_map<int, std::shared_ptr<User>> m_ActiveSessions;
};
