
#pragma once

#include <string>
#include <chrono>

class User
{
public:
    User(int id, std::string username, std::string email, std::string password);

    int GetId() const;
    const std::string& GetUsername() const;
    const std::string& GetEmail() const;
    const std::string& GetPassword() const;

    const std::string& GetDisplayName() const;
    void SetDisplayName(std::string displayName);

    std::chrono::system_clock::time_point GetCreatedAt() const;
    std::chrono::system_clock::time_point GetLastLoginAt() const;
    void SetLastLoginAt(std::chrono::system_clock::time_point lastLoginAt);

private:
    int Id;
    std::string Username;
    std::string Email;
    std::string Password;
    std::string DisplayName;
    std::chrono::system_clock::time_point CreatedAt;
    std::chrono::system_clock::time_point LastLoginAt;
};
