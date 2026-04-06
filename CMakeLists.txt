cmake_minimum_required(VERSION 3.10)
project(MOOS-Learning-Lab)

# MOOS Learning Lab - Examples from "Introduction to Programming with MOOS"
# by Paul Newman. ex1 is the simple app, ex2 is the simulator.
# Run both together - ex2 publishes Heading and VehicleStatus,
# ex1 subscribes to and processes them.

add_subdirectory(ex1)
add_subdirectory(ex2)