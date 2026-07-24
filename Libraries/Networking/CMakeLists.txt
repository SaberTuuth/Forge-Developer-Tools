add_library(Networking STATIC)

target_sources(Networking
PRIVATE
    src/NetworkEndpoint.cpp
    src/Packet.cpp
    src/TcpServer.cpp
    src/TcpClient.cpp 
)

target_include_directories(Networking
PUBLIC
    include
)

target_link_libraries(Networking
PUBLIC
    Core
    Ws2_32
)