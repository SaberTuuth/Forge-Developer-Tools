
#include "authentication.h"
#include "usermanager.h"
#include <chrono>

AuthManager::AuthManager(UserManager& userManager)
    : m_UserManager(userManager)
{
}

LoginResult AuthManager::Login(const std::string& username, const std::string& password, int& outUserId)
{
    auto user = m_UserManager.FindByUsername(username);
    if (!user)
    {
        return LoginResult::UserNotFound;
    }

    if (user->GetPassword() != password)
    {
        return LoginResult::InvalidCredentials;
    }

    if (m_ActiveSessions.find(user->GetId()) != m_ActiveSessions.end())
    {
        return LoginResult::AlreadyLoggedIn;
    }

    user->SetLastLoginAt(std::chrono::system_clock::now());
    m_ActiveSessions[user->GetId()] = user;
    outUserId = user->GetId();
    return LoginResult::Success;
}

void AuthManager::Logout(int userId)
{
    m_ActiveSessions.erase(userId);
}

bool AuthManager::IsLoggedIn(int userId) const
{
    return m_ActiveSessions.find(userId) != m_ActiveSessions.end();
}

std::shared_ptr<User> AuthManager::GetLoggedInUser(int userId) const
{
    auto it = m_ActiveSessions.find(userId);
    if (it != m_ActiveSessions.end())
    {
        return it->second;
    }
    return nullptr;
}
