cmake_minimum_required(VERSION 3.10)
project(Client-Server-Model)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories
include_directories(include)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find cppzmq
find_package(cppzmq)

include_directories(${cppzmq_INCLUDE_DIR})

include_directories("/usr/local/include/msgpack_util/include/")
include_directories("/usr/local/include/boost_util/")
# Add threading library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Client src/client.cpp src/framepack.cpp include/framepack.hpp include/client.hpp)
add_executable(Server src/server.cpp src/framepack.cpp include/framepack.hpp include/server.hpp)
add_executable(Subscriber src/subscriber.cpp src/framepack.cpp include/framepack.hpp include/subscriber.hpp)
# Target Link Libraries
target_link_libraries(Client ${OpenCV_LIBS} ${cppzmq_LIBRARY} Threads::Threads)
target_link_libraries(Server ${OpenCV_LIBS} ${cppzmq_LIBRARY} Threads::Threads)
target_link_libraries(Subscriber ${OpenCV_LIBS} ${cppzmq_LIBRARY} Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_library(ZMQ_LIBRARY NAMES zmq PATHS /usr/local/lib)
if(ZMQ_LIBRARY)
    target_link_libraries(Client ${ZMQ_LIBRARY})
    target_link_libraries(Server ${ZMQ_LIBRARY})
    target_link_libraries(Subscriber ${ZMQ_LIBRARY})
else()
    message(FATAL_ERROR "ZMQ library not found")
endif()