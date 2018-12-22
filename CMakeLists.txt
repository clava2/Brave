cmake_minimum_required(VERSION 3.0.0)
project(Brave VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Brave code/Game/CGame.cpp code/main/main.cpp code/Timer/CTimer.cpp)

link_directories("/usr/local/lib")
target_link_libraries(Brave SDL2 SDL2_image SDL2_mixer log4cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
