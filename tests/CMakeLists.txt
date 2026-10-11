add_executable(DatabaseTests DatabaseTests.cpp)

target_link_libraries(DatabaseTests
	PRIVATE
		Database
)

add_test(NAME DatabaseTests COMMAND DatabaseTests)
