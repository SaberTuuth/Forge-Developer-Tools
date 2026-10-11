#include "database.h"

#include <iostream>
#include <utility>

static int g_Failures = 0;

#define CHECK(cond)                                                              \
	do                                                                           \
	{                                                                            \
		if (!(cond))                                                             \
		{                                                                        \
			std::cerr << __FILE__ << ":" << __LINE__ << " CHECK failed: " #cond "\n"; \
			++g_Failures;                                                        \
		}                                                                        \
	} while (0)

static void TestInsertAndSelect()
{
	Database db(":memory:");
	db.Execute("CREATE TABLE tasks (id INTEGER PRIMARY KEY, title TEXT NOT NULL, priority INTEGER, assignee INTEGER);");

	auto insert = db.Prepare("INSERT INTO tasks (title, priority, assignee) VALUES (?, ?, ?);");
	insert.Bind(1, std::string("Write tests"));
	insert.Bind(2, 2);
	insert.Bind(3, 7);
	CHECK(!insert.Step());
	int64_t firstId = db.LastInsertId();
	CHECK(db.Changes() == 1);

	// Reuse the prepared statement
	insert.Reset();
	insert.Bind(1, std::string("Ship it"));
	insert.Bind(2, 3);
	insert.Bind(3, nullptr);
	CHECK(!insert.Step());
	CHECK(db.LastInsertId() == firstId + 1);

	auto select = db.Prepare("SELECT id, title, priority, assignee FROM tasks ORDER BY id;");
	CHECK(select.Step());
	CHECK(select.GetInt64(0) == firstId);
	CHECK(select.GetText(1) == "Write tests");
	CHECK(select.GetInt(2) == 2);
	CHECK(!select.IsNull(3));
	CHECK(select.GetInt(3) == 7);

	CHECK(select.Step());
	CHECK(select.GetText(1) == "Ship it");
	CHECK(select.GetInt(2) == 3);
	CHECK(select.IsNull(3));

	CHECK(!select.Step());
}

static void TestInvalidSqlThrows()
{
	Database db(":memory:");

	bool threw = false;
	try
	{
		db.Execute("CREATE TABEL oops (id INTEGER);");
	}
	catch (const DatabaseError&)
	{
		threw = true;
	}
	CHECK(threw);

	threw = false;
	try
	{
		db.Prepare("SELECT * FROM missing_table;");
	}
	catch (const DatabaseError&)
	{
		threw = true;
	}
	CHECK(threw);
}

static void TestMove()
{
	Database first(":memory:");
	first.Execute("CREATE TABLE t (v REAL);");

	Database second = std::move(first);
	auto insert = second.Prepare("INSERT INTO t (v) VALUES (?);");
	insert.Bind(1, 1.5);
	CHECK(!insert.Step());

	auto select = second.Prepare("SELECT v FROM t;");
	CHECK(select.Step());
	CHECK(select.GetDouble(0) == 1.5);
}

int main()
{
	TestInsertAndSelect();
	TestInvalidSqlThrows();
	TestMove();

	if (g_Failures == 0)
	{
		std::cout << "All database tests passed\n";
		return 0;
	}
	std::cerr << g_Failures << " check(s) failed\n";
	return 1;
}
