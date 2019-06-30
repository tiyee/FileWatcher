cmake_minimum_required(VERSION 2.8)
project(FileWatcher)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -stdlib=libc++")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -m64 -O2")
if (CMAKE_HOST_APPLE)
    add_definitions(-DOS_MACOSX)
elseif (CMAKE_HOST_UNIX)
    add_definitions(-DOS_LINUX)
else (CMAKE_HOST_APPLE)
    message(FATAL_ERROR "Platform not supported")
endif (CMAKE_HOST_APPLE)

if (CMAKE_HOST_APPLE)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -stdlib=libc++")
elseif (CMAKE_HOST_UNIX)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
else (CMAKE_HOST_APPLE)
    message(FATAL_ERROR "Platform not supported")
endif (CMAKE_HOST_APPLE)



MESSAGE("++++++++++++++Start Build+++++++++++++++++")


aux_source_directory(./src DIR_SRCS)
add_executable(${PROJECT_NAME} src/main.cpp )


if (CMAKE_HOST_APPLE)
add_library (Loop src/loop_impl.h src/mac_loop.h src/mac_loop.cpp)
elseif (CMAKE_HOST_UNIX)
   add_library (Loop  src/linux_loop.h src/linux_loop.cpp)
else (CMAKE_HOST_APPLE)
    message(FATAL_ERROR "Platform not supported")
endif (CMAKE_HOST_APPLE)

   add_library (Acceptor  src/loop_impl.h  src/mac_acceptor.h src/mac_acceptor.cpp)
   target_link_libraries(Acceptor Loop )
target_link_libraries(${PROJECT_NAME} Loop  Acceptor)




