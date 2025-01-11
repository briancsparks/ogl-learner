#include <gtest/gtest.h>
#include "ogl-learner/renderer.hpp"
#include "ogl-learner/window.hpp"
#include <memory>

class RendererTest : public ::testing::Test {
protected:
  void SetUp() override {
    window = std::make_unique<ogl_learner::Window>("Test Window", 800, 600);
    renderer = std::make_unique<ogl_learner::Renderer>(std::move(window));
  }

  void TearDown() override {
    renderer.reset();
  }

  std::unique_ptr<ogl_learner::Window> window;
  std::unique_ptr<ogl_learner::Renderer> renderer;
};

TEST_F(RendererTest, Initialization) {
  EXPECT_NO_THROW(renderer->init());
}

TEST_F(RendererTest, FPSCalculation) {
  renderer->init();
  EXPECT_GE(renderer->getFPS(), 0.0f);
}
