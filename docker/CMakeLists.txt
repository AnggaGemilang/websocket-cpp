cmake_minimum_required(VERSION 3.31.0)
project(1-1-ws VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include_directories(
    "/home/vcpkg/installed/x64-linux/include"
)
link_directories(
    "/home/vcpkg/installed/x64-linux/lib"
)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc src/*.h src/*.hpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp)

find_package(Boost REQUIRED COMPONENTS thread)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::thread)
target_link_libraries(${PROJECT_NAME} PRIVATE uSockets uv z)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
