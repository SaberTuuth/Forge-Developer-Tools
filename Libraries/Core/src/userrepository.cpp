
#include "userrepository.h"
#include <chrono>


static int64_t ToSeconds(std::chrono::system_clock::time_point tp)
{
    return std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
}

static std::chrono::system_clock::time_point FromSeconds(int64_t seconds)
{
    return std::chrono::system_clock::time_point{ std::chrono::seconds{ seconds } };
}

// Builds a User from the current row. Column order must match the SELECT in Load/LoadAll.
static std::shared_ptr<User> ReadUser(const Statement& stmt)
{
    auto user = std::make_shared<User>(
        stmt.GetInt(0),                 // id
        stmt.GetText(1),                // username
        stmt.GetText(2),                // email
        stmt.GetText(3));               // password

    user->SetDisplayName(stmt.GetText(4));
    user->SetCreatedAt(FromSeconds(stmt.GetInt64(5)));

    if (!stmt.IsNull(6))
    {
        user->SetLastLoginAt(FromSeconds(stmt.GetInt64(6)));
    }

    return user;
}

UserRepository::UserRepository(Database& db) : Db(db)
{
}

std::shared_ptr<User> UserRepository::Create(const std::string& username, const std::string& email, const std::string& password)
{
    // id is omitted so SQLite assigns a unique one (INTEGER PRIMARY KEY)
    auto stmt = Db.Prepare(R"(
        INSERT INTO users (username, email, password_hash, display_name, created_at)
        VALUES (?, ?, ?, ?, ?);
    )");

    auto createdAt = std::chrono::system_clock::now();

    stmt.Bind(1, username);
    stmt.Bind(2, email);
    stmt.Bind(3, password);                      // TODO: hash
    stmt.Bind(4, username);                      // display name defaults to username
    stmt.Bind(5, ToSeconds(createdAt));

    stmt.Step();                                 // throws DatabaseError on UNIQUE violation

    auto user = std::make_shared<User>(static_cast<int>(Db.LastInsertId()), username, email, password);
    user->SetCreatedAt(createdAt);
    return user;
}

void UserRepository::Update(const User& user)
{
    auto stmt = Db.Prepare(R"(
        UPDATE users SET
            username = ?,
            email = ?,
            password_hash = ?,
            display_name = ?,
            last_login_at = ?
        WHERE id = ?;
    )");

    stmt.Bind(1, user.GetUsername());
    stmt.Bind(2, user.GetEmail());
    stmt.Bind(3, user.GetPassword());            // TODO: hash
    stmt.Bind(4, user.GetDisplayName());

    if (user.GetLastLoginAt() == std::chrono::system_clock::time_point{})
        stmt.Bind(5, nullptr);                    // never logged in
    else
        stmt.Bind(5, ToSeconds(user.GetLastLoginAt()));

    stmt.Bind(6, user.GetId());

    stmt.Step();
}

std::shared_ptr<User> UserRepository::Load(int id) {
    auto stmt = Db.Prepare(R"(
        SELECT id, username, email, password_hash, display_name, created_at, last_login_at
        FROM users
        WHERE id = ?;
    )");

    stmt.Bind(1, id);

    if (!stmt.Step()) {
        return nullptr;
    }

    return ReadUser(stmt);
}

std::shared_ptr<User> UserRepository::LoadByUsername(const std::string& username) {
    auto stmt = Db.Prepare(R"(
        SELECT id, username, email, password_hash, display_name, created_at, last_login_at
        FROM users
        WHERE username = ?;
    )");

    stmt.Bind(1, username);

    if (!stmt.Step()) {
        return nullptr;
    }

    return ReadUser(stmt);
}

std::vector<std::shared_ptr<User>> UserRepository::LoadAll() {
    auto stmt = Db.Prepare(R"(
        SELECT id, username, email, password_hash, display_name, created_at, last_login_at
        FROM users
        ORDER BY id;
    )");

    std::vector<std::shared_ptr<User>> users;
    while (stmt.Step()) {
        users.push_back(ReadUser(stmt));
    }
    return users;
}

void UserRepository::Remove(int id) {
    auto stmt = Db.Prepare("DELETE FROM users WHERE id = ?;");
    stmt.Bind(1, id);
    stmt.Step();
}
