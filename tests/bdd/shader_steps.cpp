#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "ogl-learner/shader.hpp"
#include "ogl-learner/window.hpp"
#include <memory>

SCENARIO("Working with OpenGL shaders", "[shader]") {
  GIVEN("An OpenGL context") {
    auto window = std::make_unique<ogl_learner::Window>("Test Window", 800, 600);

    WHEN("Loading vertex and fragment shaders") {
      THEN("The shader program should be created successfully") {
        REQUIRE_NOTHROW(ogl_learner::Shader());
      }
    }

    WHEN("Setting uniform values") {
      ogl_learner::Shader shader;

      THEN("All uniform types should be set without errors") {
        CHECK_NOTHROW([&]() {
          shader.use();
          shader.setBool("testBool", true);
          shader.setInt("testInt", 42);
          shader.setFloat("testFloat", 3.14f);
          shader.setVec3("testVec3", glm::vec3(1.0f, 2.0f, 3.0f));
          shader.setMat4("testMat4", glm::mat4(1.0f));
        }());
      }
    }

    WHEN("Moving a shader object") {
      ogl_learner::Shader original;

      THEN("The shader should be movable") {
        CHECK_NOTHROW([&]() {
          ogl_learner::Shader moved = std::move(original);
          moved.use();  // Should work with moved object
        }());
      }
    }
  }
}
