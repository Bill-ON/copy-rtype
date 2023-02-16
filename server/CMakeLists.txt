cmake_minimum_required(VERSION 3.22)

set(VCPKG_ROOT "../vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "")
project(r-type_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use find_package() to trigger Vcpkg search for pkg
find_package(Boost REQUIRED COMPONENTS system thread regex)
find_package(SFML COMPONENTS system window graphics network audio
  CONFIG REQUIRED)

# Set project source code
set(SRCS
  src/main.cpp
)

# Set ECS source directories
set(ECS_LIB
  ../ecs/Camera.cpp
  ../ecs/events/Event.cpp
  ../ecs/helpers/sfml_dict.cpp
  ../ecs/helpers/sfml_bounding_box.cpp
  ../ecs/prefabs/Player.cpp
  # ../ecs/prefabs/Dobkeratops.cpp
  # ../ecs/prefabs/Bullet.cpp
  ../ecs/systems/movement_system.cpp
  ../ecs/systems/physics_system.cpp
  ../ecs/systems/draw_system.cpp
  ../ecs/systems/input_system.cpp
  ../ecs/systems/debug_system.cpp
  ../ecs/systems/collision_system.cpp
  ../ecs/systems/kill_system.cpp
)

# Set project headers directories
set(INCLUDE_DIRS
    include/
    src/
    ../NetCommon/include/
    ${Boost_INCLUDE_DIRS}
)

# Set ECS headers directories
set(ECS_INCLUDE_DIRS
  ../ecs
  ../ecs/components
  ../ecs/events
  ../ecs/helpers
  ../ecs/managers
  ../ecs/prefabs
  ../ecs/systems
)

# Create library from ECS source code
add_library(ecs_lib STATIC ${ECS_LIB})

# Create executable from source code
add_executable(${PROJECT_NAME} ${SRCS})

# Link ECS headers directories to project and ECS lib
target_include_directories(${PROJECT_NAME} PUBLIC ${ECS_INCLUDE_DIRS})
target_include_directories(ecs_lib PUBLIC ${ECS_INCLUDE_DIRS})

# Link smfl to ecs
target_link_libraries(ecs_lib PRIVATE
  sfml-system sfml-window sfml-graphics sfml-network sfml-audio
)

# Link header directories to project 
target_include_directories(${PROJECT_NAME} PUBLIC
  ${INCLUDE_DIRS}
)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${Boost_LIBRARIES}
  sfml-system sfml-window sfml-graphics sfml-network sfml-audio
  ecs_lib
)

# --------------------------------
# ------ COMPILER SELECTION ------
# --------------------------------

# This part detects the machine C++ compiler
# and add the appropriate compile options

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # g++ (Linux)
    list(APPEND COMPILE_OPTIONS "-std=c++17 -W -Wall -Wextra -g3")
	foreach(ITEM ${COMPILE_OPTIONS})
		set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in COMPILE_OPTIONS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") # msvc (Windows)
    list(APPEND COMPILE_OPTIONS "/std:c++17")
    foreach(ITEM ${COMPILE_OPTIONS})
        set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS ${ITEM})
    endforeach(ITEM in COMPILE_OPTIONS)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # clang (MacOs)
  target_link_libraries(${PROJECT_NAME} PRIVATE c++ "-framework OpenAl")
    list(APPEND COMPILE_OPTIONS "-std=c++17 -stdlib=libc++")
    foreach(ITEM ${COMPILE_OPTIONS})
        set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS ${ITEM})
    endforeach(ITEM in COMPILE_OPTIONS)
endif()