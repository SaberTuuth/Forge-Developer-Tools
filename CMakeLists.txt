cmake_minimum_required(VERSION 3.25)

project(
    Forge
    VERSION 0.1.0
    DESCRIPTION "Modern C++ Developer Tools Platform"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(cmake/sqlite.cmake)

add_subdirectory(libraries/Core)
add_subdirectory(Libraries/Networking)
add_subdirectory(Libraries/JobSystem)
add_subdirectory(Libraries/Project)
add_subdirectory(Libraries/Tasks)
add_subdirectory(Libraries/Database)
add_subdirectory(Applications/Server)
add_subdirectory(Applications/Client)
add_subdirectory(tests)

add_executable(
    Forge
    src/main.cpp
)

target_link_libraries(Forge
    PRIVATE
        Core
        Networking 
	    JobSystem
        Project
        Tasks
        Database
)