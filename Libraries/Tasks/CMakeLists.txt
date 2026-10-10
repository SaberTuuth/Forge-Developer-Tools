add_library(Tasks STATIC)

target_sources(Tasks
	PRIVATE
		src/task.cpp
		src/taskmanager.cpp
)

target_include_directories(Tasks
	PUBLIC
		include
)
