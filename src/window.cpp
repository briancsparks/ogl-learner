#include "ogl-learner/window.hpp"
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace ogl_learner {

Window::Window(const std::string& title, int width, int height)
  : m_window(nullptr), m_glContext(nullptr), m_width(width), m_height(height), m_shouldClose(false) {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  // Set OpenGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  m_window = SDL_CreateWindow(
    title.c_str(),
    width,
    height,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  );

  if (!m_window) {
    SDL_Quit();
    throw std::runtime_error(SDL_GetError());
  }

  m_glContext = SDL_GL_CreateContext(m_window);
  if (!m_glContext) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    throw std::runtime_error(SDL_GetError());
  }

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_GL_DestroyContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    throw std::runtime_error("Failed to initialize GLAD");
  }

  // Enable VSync by default
  setVSync(true);

  // Enable OpenGL features
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  spdlog::info("OpenGL Info:");
  spdlog::info("  Vendor: {}", (char const *)glGetString(GL_VENDOR));
  spdlog::info("  Renderer: {}", (char const *)glGetString(GL_RENDERER));
  spdlog::info("  Version: {}", (char const *)glGetString(GL_VERSION));
}

Window::~Window() {
  if (m_glContext) {
    SDL_GL_DestroyContext(m_glContext);
  }
  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
  SDL_Quit();
}

Window::Window(Window&& other) noexcept
  : m_window(other.m_window)
  , m_glContext(other.m_glContext)
  , m_width(other.m_width)
  , m_height(other.m_height)
  , m_shouldClose(other.m_shouldClose) {
  other.m_window = nullptr;
  other.m_glContext = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
  if (this != &other) {
    if (m_glContext) {
      SDL_GL_DestroyContext(m_glContext);
    }
    if (m_window) {
      SDL_DestroyWindow(m_window);
    }

    m_window = other.m_window;
    m_glContext = other.m_glContext;
    m_width = other.m_width;
    m_height = other.m_height;
    m_shouldClose = other.m_shouldClose;

    other.m_window = nullptr;
    other.m_glContext = nullptr;
  }
  return *this;
}

bool Window::shouldClose() const {
  return m_shouldClose;
}

void Window::swapBuffers() {
  SDL_GL_SwapWindow(m_window);
}

void Window::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_shouldClose = true;
    }
    else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
      m_width = event.window.data1;
      m_height = event.window.data2;
      glViewport(0, 0, m_width, m_height);
    }
  }
}

void Window::setVSync(bool enabled) {
  if (!SDL_GL_SetSwapInterval(enabled ? 1 : 0)) {
    spdlog::warn("Failed to set VSync: {}", SDL_GetError());
  }
}

} // namespace ogl_learner
