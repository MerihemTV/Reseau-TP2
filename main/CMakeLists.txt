cmake_minimum_required(VERSION 3.10)

set(replication_sources src/main.cpp
                        src/game_object.cpp
                        src/streams.cpp
						src/enemy.cpp
						src/player.cpp
						src/linking_context.cpp
						src/server.cpp
						src/client.cpp)

include_directories(include)
set(replication_headers include/game_object.hpp
                        include/utils.hpp
                        include/streams.hpp
						include/enemy.hpp
						include/player.hpp
						include/linking_context.hpp
						include/server.hpp
						include/classRegistry.hpp
						include/replicationManager.hpp
						include/client.hpp)

add_executable(tp2 ${replication_sources} ${replication_headers})
target_link_libraries(tp2 PUBLIC uvw_interface GSL)