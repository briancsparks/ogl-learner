#ifndef OGL_LEARNER_RENDERER_HPP
#define OGL_LEARNER_RENDERER_HPP

#include <memory>
#include "window.hpp"
#include "shader.hpp"
#include "tetrahedron.hpp"

namespace ogl_learner {

class Renderer {
public:
  explicit Renderer(std::unique_ptr<Window> window);
  ~Renderer();

  // Delete copy constructor and assignment operator
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;

  // Move constructor and assignment operator
  Renderer(Renderer&& other) noexcept;
  Renderer& operator=(Renderer&& other) noexcept;

  void init();
  void render();
  bool shouldClose() const;
  float getFPS() const;

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<Shader> m_shader;
  std::unique_ptr<Tetrahedron> m_tetrahedron;
  float m_lastFrame;
  float m_deltaTime;
  float m_currentFPS;
  float m_fpsUpdateTimer;
  
  void setupImGui();
  void updateFPS();
  void renderImGui();
};

} // namespace ogl_learner

#endif // OGL_LEARNER_RENDERER_HPP
