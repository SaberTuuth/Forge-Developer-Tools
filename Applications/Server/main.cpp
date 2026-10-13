
#include <iostream>
#include "TcpServer.h"
#include "Config.h"
#include "MessageHandler.h"
#include "database.h"
#include "schema.h"
#include "userrepository.h"

int main()
{
	Config config;

	try {
		Database database("forge.db");

		InitializeSchema(database);

		UserRepository users(database);
		TcpServer server(config.Port, users);
		if (server.Listen()) {

			std::cout << "Waiting for client...\n";

			while (true)
			{
				server.Update();
			}
		}
	}
	catch (const DatabaseError& e)
	{
		std::cerr << "Database error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}