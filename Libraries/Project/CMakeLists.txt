add_library(Project STATIC)

target_sources(Project
   PRIVATE
     src/Project.cpp
     src/ProjectManager.cpp
)

target_include_directories(Project
PUBLIC
    include
)
