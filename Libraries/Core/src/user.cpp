
#include "user.h"

User::User(int id, std::string username, std::string email, std::string password)
    : Id(id),
      Username(std::move(username)),
      Email(std::move(email)),
      Password(std::move(password)),
      DisplayName(Username),
      CreatedAt(std::chrono::system_clock::now()),
      LastLoginAt()
{
}

int User::GetId() const
{
    return Id;
}

const std::string& User::GetUsername() const
{
    return Username;
}

const std::string& User::GetEmail() const
{
    return Email;
}

const std::string& User::GetPassword() const
{
    return Password;
}

const std::string& User::GetDisplayName() const
{
    return DisplayName;
}

void User::SetDisplayName(std::string displayName)
{
    DisplayName = std::move(displayName);
}

std::chrono::system_clock::time_point User::GetCreatedAt() const
{
    return CreatedAt;
}

std::chrono::system_clock::time_point User::GetLastLoginAt() const
{
    return LastLoginAt;
}

void User::SetLastLoginAt(std::chrono::system_clock::time_point lastLoginAt)
{
    LastLoginAt = lastLoginAt;
}
