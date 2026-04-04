cmake_minimum_required(VERSION 3.10)
project(ex1)

# C++ standard
set(CMAKE_CXX_STANDARD 20)

# Where to find MOOS headers
include_directories(
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/Utils/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/App/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/Comms/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/DB/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/AppCasting/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/PocoBits/include
    /home/ryne/Projects/shared/moos-ivp/MOOS_Jul0519/MOOSCore/Core/libMOOS/Thirdparty/getpot/include
)

# Where to find MOOS libraries
link_directories(
    /home/ryne/Projects/shared/moos-ivp/build/MOOS/MOOSCore/lib
)

# Define the executable
add_executable(ex1
    main.cpp
    simple_app.cpp
)

# Link against MOOS library
target_link_libraries(ex1
    MOOS
)
