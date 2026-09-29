add_library(Core STATIC)

target_sources(Core
    PRIVATE
        src/Config.cpp
        src/user.cpp
        src/authentication.cpp
        src/usermanager.cpp
)

target_include_directories(Core
    PUBLIC
        include
)