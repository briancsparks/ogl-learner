include(FetchContent)

# Find OpenGL
find_package(OpenGL REQUIRED)

# SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
  message(STATUS "SDL3 not found via find_package, using FetchContent")
  FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main  # SDL3 is still in development
  )
  FetchContent_MakeAvailable(SDL3)
endif()

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG master
)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
  set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
  set(GLAD_API "gl=4.1" CACHE STRING "API type/version pairs")
  set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
  add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

# GLM
find_package(glm QUIET)
if(NOT glm_FOUND)
  FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(glm)
endif()

# Assimp (commented out as per request)
#find_package(assimp QUIET)
#if(NOT assimp_FOUND)
#  FetchContent_Declare(
#    assimp
#    GIT_REPOSITORY https://github.com/assimp/assimp.git
#    GIT_TAG master
#  )
#  set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#  set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
#  FetchContent_MakeAvailable(assimp)
#endif()

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG master
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)
  # ImGui is header-only, we'll create our own target in the main CMakeLists.txt
endif()

# spdlog
find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
  set(SPDLOG_BUILD_SHARED ON)
  set(SPDLOG_ENABLE_PCH OFF)
  set(SPDLOG_NO_TLS ON)

  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
  )
  FetchContent_MakeAvailable(spdlog)

  target_compile_definitions(spdlog PUBLIC
    SPDLOG_SHARED_LIB
    SPDLOG_COMPILED_LIB
    SPDLOG_NO_TLS
  )
endif()

# stb
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
  FetchContent_Populate(stb)
  # stb is header-only
endif()

# Tracy Profiler
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  FetchContent_Declare(
    tracy
    GIT_REPOSITORY https://github.com/wolfpld/tracy.git
    GIT_TAG master
  )
  set(TRACY_ENABLE ON)
  FetchContent_MakeAvailable(tracy)
endif()

# GoogleTest
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

# Catch2
find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG devel
  )
  FetchContent_MakeAvailable(Catch2)
endif()

# CLI11
find_package(CLI11 QUIET)
if(NOT CLI11_FOUND)
  FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG main
  )
  FetchContent_MakeAvailable(CLI11)
endif()
