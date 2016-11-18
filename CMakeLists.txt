cmake_minimum_required(VERSION 3.2)
project(Sombra)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# Set default build type explicitly to Release
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

if(NOT SFML_ROOT)
  set(SFML_ROOT CACHE "" FORCE)
endif()
if(NOT THOR_ROOT)
  set(THOR_ROOT CACHE "" FORCE)
endif()
if(NOT SFGUI_ROOT)
  set(SFGUI_ROOT CACHE "" FORCE)
endif()

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

if(NOT SFML_FOUND)
  message(FATAL_ERROR "SFML couldn't be located!")
endif()

# Find Thor
set(THOR_STATIC_LIBRARIES TRUE)
find_package(Thor REQUIRED)

if(NOT THOR_FOUND)
  message(FATAL_ERROR "Thor couldn't be located!")
endif()

# Find SFGUI
set(SFGUI_STATIC_LIBRARIES TRUE)
find_package(SFGUI REQUIRED)

if(NOT SFGUI_FOUND)
  message(FATAL_ERROR "SFGUI couldn't be located!")
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${THOR_INCLUDE_DIR})
include_directories(${SFGUI_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES
  src/main.cpp
  src/Application.cpp
  src/Animation.cpp
  src/Console.cpp
  src/ConsoleScreen.cpp
  src/State.cpp
  src/GameState.cpp
)

add_executable(Sombra ${SOURCE_FILES})

target_link_libraries(Sombra ${THOR_LIBRARY} ${SFGUI_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Install executable
install(TARGETS Sombra
  RUNTIME DESTINATION .
)

# Install game data
install(DIRECTORY bin/res
  DESTINATION .
)
