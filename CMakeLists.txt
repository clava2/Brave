cmake_minimum_required(VERSION 3.0.0)
SET(CMAKE_C_COMPILER "/usr/bin/gcc-8")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++-8")

project(Brave VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Brave code/Game/CGame.cpp 
                    code/Main/main.cpp 
                    code/Timer/CTimer.cpp 
                    code/Board/CBoard.cpp 
                    code/GUI/CButton.cpp
                    code/CrossFile/CrossFile.cpp
                    code/Block/CBlock.cpp)

link_directories("/usr/local/lib")
target_link_libraries(Brave SDL2 SDL2_image SDL2_mixer SDL2_ttf log4cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
