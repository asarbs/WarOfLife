cmake_minimum_required(VERSION 3.13.4)
project(WarOfLife)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(WarOfLif_Lib src/GameMain.cpp src/Node.cpp src/brush/Brush.cpp src/brush/Brush.h src/brush/GosperGliderGun.cpp src/brush/GosperGliderGun.h src/PlayerColor.h src/brush/Dot.cpp src/brush/Dot.h)

add_executable(${PROJECT_NAME} src/main.cpp src/brush/Glider.cpp src/brush/Glider.h)
target_link_libraries(${PROJECT_NAME} WarOfLif_Lib ${CONAN_LIBS})
