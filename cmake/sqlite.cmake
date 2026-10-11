include(FetchContent)

# Official SQLite amalgamation (sqlite3.c / sqlite3.h). Hash from sqlite.org/download.html.
FetchContent_Declare(sqlite3
    URL      https://www.sqlite.org/2026/sqlite-amalgamation-3540000.zip
    URL_HASH SHA3_256=7b670a62fdfbd672b75fef004cb703c8a3e87d3a5cc7d675b4a08337004a2d93
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(sqlite3)

add_library(sqlite3 STATIC
    ${sqlite3_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3
    PUBLIC
        ${sqlite3_SOURCE_DIR}
)

target_compile_definitions(sqlite3
    PRIVATE
        SQLITE_DQS=0
        SQLITE_OMIT_LOAD_EXTENSION
)
