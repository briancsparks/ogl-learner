#include "ogl-learner/renderer.hpp"
#include "ogl-learner/window.hpp"
#include <spdlog/spdlog.h>
//#include <tracy/Tracy.hpp>
#include <memory>
#include <stdexcept>

int main(int argc, char* argv[]) {
  try {
    // Initialize logging
    spdlog::set_level(spdlog::level::debug);

    // Create window
    auto window = std::make_unique<ogl_learner::Window>("OpenGL Tetrahedron", 800, 600);

    // Create renderer
    ogl_learner::Renderer renderer(std::move(window));
    renderer.init();

    // Main loop
    while (!renderer.shouldClose()) {
//      FrameMark;  // Tracy frame marker
      renderer.render();
    }

    return 0;
  }
  catch (const std::exception& e) {
    spdlog::error("Fatal error: {}", e.what());
    return 1;
  }
}
