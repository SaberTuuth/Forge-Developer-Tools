
#include "schema.h"

void InitializeSchema(Database& db) {

	db.Execute(R"(
		BEGIN;

		CREATE TABLE IF NOT EXISTS users(
			id INTEGER PRIMARY KEY,
			username TEXT NOT NULL UNIQUE,
			email TEXT NOT NULL UNIQUE,
			password_hash TEXT NOT NULL,
			display_name TEXT,
			created_at INTEGER NOT NULL, 
			last_login_at INTEGER
		);

		CREATE  TABLE IF NOT EXISTS projects(
			id INTEGER PRIMARY KEY,
			name TEXT NOT NULL, 
			key TEXT NOT NULL UNIQUE, 
			owner_id INTEGER NOT NULL REFERENCES users(id)
		);

		CREATE  TABLE IF NOT EXISTS project_members(
			project_id INTEGER REFERENCES projects(id) ON DELETE CASCADE, 
			user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
			PRIMARY KEY(project_id, user_id)
		);

		CREATE TABLE IF NOT EXISTS tasks(
			id INTEGER PRIMARY KEY, 
			project_id INTEGER NOT NULL REFERENCES projects(id) ON DELETE CASCADE, 
			title TEXT NOT NULL, 
			description TEXT NOT NULL DEFAULT '', 
			creator_id INTEGER NOT NULL REFERENCES users(id), 
			assignee_id INTEGER REFERENCES users(id) ON DELETE SET NULL, 
			status INTEGER NOT NULL DEFAULT 0, 
			priority INTEGER NOT NULL DEFAULT 1
		);

		COMMIT;
		)");
}