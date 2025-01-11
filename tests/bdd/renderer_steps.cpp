#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "ogl-learner/renderer.hpp"
#include "ogl-learner/window.hpp"
#include <memory>

SCENARIO("Rendering a tetrahedron", "[renderer]") {
  GIVEN("A renderer with a window") {
    auto window = std::make_unique<ogl_learner::Window>("Test Window", 800, 600);
    auto renderer = std::make_unique<ogl_learner::Renderer>(std::move(window));

    WHEN("The renderer is initialized") {
      THEN("No exceptions should be thrown") {
        REQUIRE_NOTHROW(renderer->init());
      }

      AND_WHEN("A frame is rendered") {
        renderer->init();
        THEN("The frame should complete successfully") {
          REQUIRE_NOTHROW(renderer->render());
        }

        AND_THEN("The FPS should be calculated") {
          renderer->render();
          REQUIRE(renderer->getFPS() >= 0.0f);
        }
      }
    }
  }
}
