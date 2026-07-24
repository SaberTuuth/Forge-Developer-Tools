add_library(Core STATIC)

target_sources(Core
    PRIVATE
        src/Config.cpp
)

target_include_directories(Core
    PUBLIC
        include
)