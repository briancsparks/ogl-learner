#include <gtest/gtest.h>
#include "ogl-learner/shader.hpp"
#include "ogl-learner/window.hpp"
#include <memory>

class ShaderTest : public ::testing::Test {
protected:
  void SetUp() override {
    // We need a valid OpenGL context for shader tests
    window = std::make_unique<ogl_learner::Window>("Test Window", 800, 600);
  }

  void TearDown() override {
    window.reset();
  }

  std::unique_ptr<ogl_learner::Window> window;
};

TEST_F(ShaderTest, LoadShader) {
  EXPECT_NO_THROW(ogl_learner::Shader shader);
}

TEST_F(ShaderTest, UniformOperations) {
  ogl_learner::Shader shader;

  // These operations should not throw
  EXPECT_NO_THROW({
    shader.use();
    shader.setBool("testBool", true);
    shader.setInt("testInt", 42);
    shader.setFloat("testFloat", 3.14f);
    shader.setVec3("testVec3", glm::vec3(1.0f, 2.0f, 3.0f));
    shader.setVec4("testVec4", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
    shader.setMat4("testMat4", glm::mat4(1.0f));
  });
}
