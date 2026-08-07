cmake_minimum_required(VERSION 3.25)

project(
    Forge
    VERSION 0.1.0
    DESCRIPTION "Modern C++ Developer Tools Platform"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libraries/Core)
add_subdirectory(Libraries/Networking)
add_subdirectory(Libraries/JobSystem)
add_subdirectory(Applications/Server)
add_subdirectory(Applications/Client)

add_executable(
    Forge
    src/main.cpp
)

target_link_libraries(Forge
    PRIVATE
        Core
        Networking 
	JobSystem
)