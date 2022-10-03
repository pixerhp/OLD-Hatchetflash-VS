cmake_minimum_required(VERSION 3.0.0)
project(HATCHETFLASH VERSION 0.0.1)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(Headers)
include_directories(Libraries/include)
include_directories(/usr/local/include)

file(GLOB CPPSOURCES "src/*.cpp")
file(GLOB CSOURCES "src/*.c")
add_executable(HatchetFlash.x86_64 ${CPPSOURCES} ${CSOURCES})

set_property(TARGET HatchetFlash.x86_64 PROPERTY POSITION_INDEPENDENT_CODE TRUE)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(HatchetFlash.x86_64 glfw)
target_link_libraries(HatchetFlash.x86_64 dl)
target_link_libraries(HatchetFlash.x86_64 freetype)
