#ifndef OGL_LEARNER_WINDOW_HPP
#define OGL_LEARNER_WINDOW_HPP

#include <string>
#include <SDL3/SDL.h>
#include <glad/glad.h>

namespace ogl_learner {

class Window {
public:
  Window(const std::string& title, int width, int height);
  ~Window();

  // Delete copy constructor and assignment operator
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  // Move constructor and assignment operator
  Window(Window&& other) noexcept;
  Window& operator=(Window&& other) noexcept;

  bool shouldClose() const;
  void swapBuffers();
  void pollEvents();
  void setVSync(bool enabled);
  
  // Getters
  SDL_Window* getSDLWindow() const { return m_window; }
  SDL_GLContext getGLContext() const { return m_glContext; }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  SDL_Window* m_window;
  SDL_GLContext m_glContext;
  int m_width;
  int m_height;
  bool m_shouldClose;
};

} // namespace ogl_learner

#endif // OGL_LEARNER_WINDOW_HPP
