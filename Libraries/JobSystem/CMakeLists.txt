add_library(JobSystem STATIC)

target_sources(JobSystem
   PRIVATE
     src/job.cpp
     src/jobqueue.cpp
     src/jobmanager.cpp
)

target_include_directories(JobSystem
PUBLIC
    include
)
