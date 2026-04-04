cmake_minimum_required(VERSION 3.10)
project(ex1)

# C++ standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Set MOOS root directory - change this single line to match your installation
set(MOOS_ROOT "/home/ryne/moos-ivp")

# Where to find MOOS headers
include_directories(
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/Utils/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/App/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/Comms/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/DB/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/AppCasting/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/PocoBits/include
    ${MOOS_ROOT}/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/getpot/include
)

# Where to find MOOS libraries
link_directories(
    ${MOOS_ROOT}/build/MOOS/MOOSCore/lib
)

# Define the executable
add_executable(ex1
    main.cpp
    simple_app.cpp
)

# Link against MOOS library
target_link_libraries(ex1
    MOOS
    pthread
)
