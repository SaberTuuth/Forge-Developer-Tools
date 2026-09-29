
#include "usermanager.h"

std::shared_ptr<User> UserManager::CreateUser(int id, const std::string& username, const std::string& email, const std::string& password)
{
	auto user = std::make_shared<User>(id, username, email, password);
	AddUser(user);
	return user;
}

void UserManager::AddUser(std::shared_ptr<User> user)
{
	m_Users[user->GetId()] = user;
}

std::shared_ptr<User> UserManager::GetUser(int id)
{
	auto it = m_Users.find(id);
	if (it != m_Users.end())
	{
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<User> UserManager::FindByUsername(const std::string& username)
{
	for (const auto& pair : m_Users)
	{
		if (pair.second->GetUsername() == username)
		{
			return pair.second;
		}
	}
	return nullptr;
}

void UserManager::RemoveUser(int id)
{
	m_Users.erase(id);
}
