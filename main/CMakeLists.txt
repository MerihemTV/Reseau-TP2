cmake_minimum_required(VERSION 3.10)

set(replication_sources src/main.cpp
                        src/streams.cpp
                        src/game_object.cpp
						src/enemy.cpp
						src/player.cpp
						src/class_registry.cpp
						src/linking_context.cpp
						src/server.cpp
						src/client.cpp
						src/replication_manager.cpp)

include_directories(include)
set(replication_headers include/utils.hpp
                        include/streams.hpp
                        include/game_object.hpp
						include/enemy.hpp
						include/player.hpp
						include/class_registry.hpp
						include/linking_context.hpp
						include/server.hpp
						include/client.hpp
						include/replication_manager.hpp)

add_executable(tp2 ${replication_sources} ${replication_headers})
target_link_libraries(tp2 PUBLIC uvw_interface GSL)