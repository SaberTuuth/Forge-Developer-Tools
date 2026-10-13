#include "usermanager.h"

UserManager::UserManager(UserRepository& repo)
	: m_Repo(repo)
{
}

std::shared_ptr<User> UserManager::CreateUser(const std::string& username, const std::string& email, const std::string& password)
{
	auto user = m_Repo.Create(username, email, password);
	m_Users[user->GetId()] = user;
	return user;
}

std::shared_ptr<User> UserManager::GetUser(int id)
{
	auto it = m_Users.find(id);
	if (it != m_Users.end())
	{
		return it->second;
	}

	auto user = m_Repo.Load(id);
	if (user)
	{
		m_Users[id] = user;
	}
	return user;
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

	auto user = m_Repo.LoadByUsername(username);
	if (user)
	{
		m_Users[user->GetId()] = user;
	}
	return user;
}

void UserManager::UpdateUser(const User& user)
{
	m_Repo.Update(user);
}

void UserManager::RemoveUser(int id)
{
	m_Repo.Remove(id);
	m_Users.erase(id);
}
