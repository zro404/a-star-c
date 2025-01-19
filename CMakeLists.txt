cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(DEBUG_COMPILE_OPTIONS "$<$<CONFIG:Debug>:-g;-Wall;-Wextra;-Werror>")
set(RELEASE_COMPILE_OPTIONS "$<$<CONFIG:Release>:-O3>")
set(COMPILE_OPTIONS ${DEBUG_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})

set(DEBUG_LINK_LIBRARIES "$<$<CONFIG:Debug>:>")
set(RELEASE_LINK_LIBRARIES "$<$<CONFIG:Release>:>")
set(LINK_LIBRARIES ${DEBUG_LINK_LIBRARIES} ${RELEASE_LINK_LIBRARIES} SDL2main
                   SDL2)

project(aStarC)

add_executable(${PROJECT_NAME})

set(SOURCES src/main.c src/engine.c src/grid.c)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
