add_library(Database STATIC)

target_sources(Database
	PRIVATE
		src/database.cpp
		src/schema.cpp
)

target_include_directories(Database
	PUBLIC
		include
)

target_link_libraries(Database
	PRIVATE
		sqlite3
)
