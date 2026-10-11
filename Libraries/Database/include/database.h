#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

struct sqlite3;
struct sqlite3_stmt;

class DatabaseError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class Statement
{
public:
	~Statement();

	Statement(const Statement&) = delete;
	Statement& operator=(const Statement&) = delete;
	Statement(Statement&& other) noexcept;
	Statement& operator=(Statement&& other) noexcept;

	// Bind indexes are 1-based
	void Bind(int index, int value);
	void Bind(int index, int64_t value);
	void Bind(int index, double value);
	void Bind(int index, const std::string& value);
	void Bind(int index, std::nullptr_t);

	// Returns true while a row is available, false when done
	bool Step();
	void Reset();

	// Column indexes are 0-based
	int GetInt(int column) const;
	int64_t GetInt64(int column) const;
	double GetDouble(int column) const;
	std::string GetText(int column) const;
	bool IsNull(int column) const;

private:
	friend class Database;
	Statement(sqlite3* db, sqlite3_stmt* stmt);

	void Check(int result) const;

	sqlite3* m_Db = nullptr;
	sqlite3_stmt* m_Stmt = nullptr;
};

class Database
{
public:
	explicit Database(const std::string& path);
	~Database();

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	Database(Database&& other) noexcept;
	Database& operator=(Database&& other) noexcept;

	void Execute(const std::string& sql);
	Statement Prepare(const std::string& sql);

	int64_t LastInsertId() const;
	int Changes() const;

private:
	sqlite3* m_Db = nullptr;
};
