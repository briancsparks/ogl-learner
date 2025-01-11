cmake_minimum_required(VERSION 3.15)
project(ogl-learner VERSION 0.1.0 LANGUAGES C CXX)

# Include our cmake modules
include(cmake/compiler-options.cmake)
include(cmake/dependencies.cmake)

# Create ImGui library target
add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
  ${SDL3_INCLUDE_DIRS}
)

# Add stb_image header path
include_directories(${stb_SOURCE_DIR})

# Main library target
add_library(${PROJECT_NAME} SHARED
  src/renderer.cpp
  src/shader.cpp
  src/tetrahedron.cpp
  src/window.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    ENABLE_EXPORTS ON
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/src/include
  ${OPENGL_INCLUDE_DIR}
  ${glad_BINARY_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  ${OPENGL_LIBRARIES}
  SDL3::SDL3
  glad
  glm::glm
  imgui
  spdlog::spdlog
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(${PROJECT_NAME} PUBLIC Tracy::TracyClient)
endif()

# Example executable
add_executable(tetrahedron_example
  src/examples/tetrahedron_example.cpp
)

target_link_libraries(tetrahedron_example PRIVATE
  ${PROJECT_NAME}
)

# Main executable
add_executable(${PROJECT_NAME}_cli
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}_cli PRIVATE
  ${PROJECT_NAME}
  CLI11::CLI11
)

# Testing
enable_testing()

# GTest based tests
add_executable(unit_tests
  tests/unit/renderer_test.cpp
  tests/unit/shader_test.cpp
)

target_link_libraries(unit_tests PRIVATE
  ${PROJECT_NAME}
  GTest::gtest_main
)

add_test(NAME unit_tests COMMAND unit_tests)

# Catch2 based tests
add_executable(bdd_tests
  tests/bdd/renderer_steps.cpp
  tests/bdd/shader_steps.cpp
)

target_link_libraries(bdd_tests PRIVATE
  ${PROJECT_NAME}
  Catch2::Catch2WithMain
)

add_test(NAME bdd_tests COMMAND bdd_tests)

# Install rules
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/include/
  DESTINATION include
)
