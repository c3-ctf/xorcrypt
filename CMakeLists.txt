project(xorcrypt)
set(CMAKE_CXX_STANDARD 17)
add_executable(xorcrypt main.c)
install(TARGETS xorcrypt RUNTIME DESTINATION bin)
