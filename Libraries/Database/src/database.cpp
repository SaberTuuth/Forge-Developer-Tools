#include "database.h"

#include <sqlite3.h>
#include <utility>

// ---- Statement ----

Statement::Statement(sqlite3* db, sqlite3_stmt* stmt)
	: m_Db(db), m_Stmt(stmt)
{
}

Statement::~Statement()
{
	sqlite3_finalize(m_Stmt);
}

Statement::Statement(Statement&& other) noexcept
	: m_Db(std::exchange(other.m_Db, nullptr)), m_Stmt(std::exchange(other.m_Stmt, nullptr))
{
}

Statement& Statement::operator=(Statement&& other) noexcept
{
	if (this != &other)
	{
		sqlite3_finalize(m_Stmt);
		m_Db = std::exchange(other.m_Db, nullptr);
		m_Stmt = std::exchange(other.m_Stmt, nullptr);
	}
	return *this;
}

void Statement::Check(int result) const
{
	if (result != SQLITE_OK)
	{
		throw DatabaseError(sqlite3_errmsg(m_Db));
	}
}

void Statement::Bind(int index, int value)
{
	Check(sqlite3_bind_int(m_Stmt, index, value));
}

void Statement::Bind(int index, int64_t value)
{
	Check(sqlite3_bind_int64(m_Stmt, index, value));
}

void Statement::Bind(int index, double value)
{
	Check(sqlite3_bind_double(m_Stmt, index, value));
}

void Statement::Bind(int index, const std::string& value)
{
	Check(sqlite3_bind_text(m_Stmt, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT));
}

void Statement::Bind(int index, std::nullptr_t)
{
	Check(sqlite3_bind_null(m_Stmt, index));
}

bool Statement::Step()
{
	int result = sqlite3_step(m_Stmt);
	if (result == SQLITE_ROW)
	{
		return true;
	}
	if (result == SQLITE_DONE)
	{
		return false;
	}
	throw DatabaseError(sqlite3_errmsg(m_Db));
}

void Statement::Reset()
{
	sqlite3_reset(m_Stmt);
	sqlite3_clear_bindings(m_Stmt);
}

int Statement::GetInt(int column) const
{
	return sqlite3_column_int(m_Stmt, column);
}

int64_t Statement::GetInt64(int column) const
{
	return sqlite3_column_int64(m_Stmt, column);
}

double Statement::GetDouble(int column) const
{
	return sqlite3_column_double(m_Stmt, column);
}

std::string Statement::GetText(int column) const
{
	auto text = reinterpret_cast<const char*>(sqlite3_column_text(m_Stmt, column));
	if (text == nullptr)
	{
		return {};
	}
	return std::string(text, sqlite3_column_bytes(m_Stmt, column));
}

bool Statement::IsNull(int column) const
{
	return sqlite3_column_type(m_Stmt, column) == SQLITE_NULL;
}

// ---- Database ----

Database::Database(const std::string& path)
{
	if (sqlite3_open(path.c_str(), &m_Db) != SQLITE_OK)
	{
		std::string message = m_Db ? sqlite3_errmsg(m_Db) : "out of memory";
		sqlite3_close(m_Db);
		m_Db = nullptr;
		throw DatabaseError("Failed to open database '" + path + "': " + message);
	}
	Execute("PRAGMA foreign_keys = ON;");
}

Database::~Database()
{
	sqlite3_close(m_Db);
}

Database::Database(Database&& other) noexcept
	: m_Db(std::exchange(other.m_Db, nullptr))
{
}

Database& Database::operator=(Database&& other) noexcept
{
	if (this != &other)
	{
		sqlite3_close(m_Db);
		m_Db = std::exchange(other.m_Db, nullptr);
	}
	return *this;
}

void Database::Execute(const std::string& sql)
{
	char* error = nullptr;
	if (sqlite3_exec(m_Db, sql.c_str(), nullptr, nullptr, &error) != SQLITE_OK)
	{
		std::string message = error ? error : sqlite3_errmsg(m_Db);
		sqlite3_free(error);
		throw DatabaseError(message);
	}
}

Statement Database::Prepare(const std::string& sql)
{
	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(m_Db, sql.c_str(), static_cast<int>(sql.size()), &stmt, nullptr) != SQLITE_OK)
	{
		throw DatabaseError(sqlite3_errmsg(m_Db));
	}
	return Statement(m_Db, stmt);
}

int64_t Database::LastInsertId() const
{
	return sqlite3_last_insert_rowid(m_Db);
}

int Database::Changes() const
{
	return sqlite3_changes(m_Db);
}
