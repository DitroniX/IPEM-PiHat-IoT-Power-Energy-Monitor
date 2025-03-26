cmake_minimum_required (VERSION 3.8)

set(PROJECTNAME "testctread")

project ("testctread")

file(GLOB driver_src ${PROJECT_SOURCE_DIR}/driver/*.c)
file(GLOB device_src ${PROJECT_SOURCE_DIR}/device/*.c)

include_directories(${PROJECT_SOURCE_DIR}/driver)
include_directories(${PROJECT_SOURCE_DIR}/device)

add_executable (testctread "main.c" "main.h" ${driver_src} ${device_src})
