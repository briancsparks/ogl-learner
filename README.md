# OpenGL Learner Project

A simple OpenGL project demonstrating basic 3D rendering with a rotating tetrahedron. This project serves as a learning foundation for OpenGL development.

## Features

- OpenGL 4.1 rendering
- Rotating tetrahedron with colored faces
- Real-time FPS counter using Dear ImGui
- Cross-platform support (Windows, Linux, macOS)
- Modern CMake build system

## Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler
- OpenGL 4.1 capable graphics driver

## Building

```bash
# Clone the repository
git clone https://github.com/yourusername/ogl-learner.git
cd ogl-learner

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .
```

## Running the Examples

After building, you can run the tetrahedron example:

```bash
./tetrahedron_example
```

## Project Structure

- `src/` - Source files
  - `include/ogl-learner/` - Public headers
  - `shaders/` - GLSL shader files
  - `examples/` - Example applications
- `tests/` - Test files
  - `unit/` - GTest-based unit tests
  - `bdd/` - Catch2-based BDD tests
- `cmake/` - CMake configuration files

## Dependencies

- SDL3 - Window management and OpenGL context
- GLAD - OpenGL function loader
- GLM - Mathematics library
- Dear ImGui - UI elements
- spdlog - Logging
- Tracy - Performance profiling (Debug builds only)
- stb_image - Image loading
- {Assimp - 3D model loading} (commented out for future use)

## License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.
