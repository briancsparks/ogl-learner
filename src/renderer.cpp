#include "ogl-learner/renderer.hpp"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>
//#include <tracy/Tracy.hpp>

namespace ogl_learner {

Renderer::Renderer(std::unique_ptr<Window> window)
  : m_window(std::move(window))
  , m_shader(nullptr)
  , m_tetrahedron(nullptr)
  , m_lastFrame(0.0f)
  , m_deltaTime(0.0f)
  , m_currentFPS(0.0f)
  , m_fpsUpdateTimer(0.0f) {
}

Renderer::~Renderer() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

Renderer::Renderer(Renderer&& other) noexcept
  : m_window(std::move(other.m_window))
  , m_shader(std::move(other.m_shader))
  , m_tetrahedron(std::move(other.m_tetrahedron))
  , m_lastFrame(other.m_lastFrame)
  , m_deltaTime(other.m_deltaTime)
  , m_currentFPS(other.m_currentFPS)
  , m_fpsUpdateTimer(other.m_fpsUpdateTimer) {
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
  if (this != &other) {
    m_window = std::move(other.m_window);
    m_shader = std::move(other.m_shader);
    m_tetrahedron = std::move(other.m_tetrahedron);
    m_lastFrame = other.m_lastFrame;
    m_deltaTime = other.m_deltaTime;
    m_currentFPS = other.m_currentFPS;
    m_fpsUpdateTimer = other.m_fpsUpdateTimer;
  }
  return *this;
}

void Renderer::init() {
  // Initialize shader
  m_shader = std::make_unique<Shader>();

  // Initialize tetrahedron
  m_tetrahedron = std::make_unique<Tetrahedron>();

  // Initialize ImGui
  setupImGui();

  // Set up view and projection matrices
  glm::mat4 view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 5.0f),  // Camera position
    glm::vec3(0.0f, 0.0f, 0.0f),  // Look at point
    glm::vec3(0.0f, 1.0f, 0.0f)   // Up vector
  );

  glm::mat4 projection = glm::perspective(
    glm::radians(45.0f),
    float(m_window->getWidth()) / float(m_window->getHeight()),
    0.1f,
    100.0f
  );

  m_shader->use();
  m_shader->setMat4("view", view);
  m_shader->setMat4("projection", projection);
}

void Renderer::setupImGui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(m_window->getSDLWindow(), m_window->getGLContext());
  ImGui_ImplOpenGL3_Init("#version 410");
}

void Renderer::render() {
//  ZoneScoped;  // Tracy profiling scope

  float currentFrame = SDL_GetTicks() / 1000.0f;
  m_deltaTime = currentFrame - m_lastFrame;
  m_lastFrame = currentFrame;

  updateFPS();

  // Clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rotate the tetrahedron
  m_tetrahedron->rotate(50.0f * m_deltaTime, glm::vec3(0.5f, 1.0f, 0.0f));

  // Draw the tetrahedron
  m_tetrahedron->draw(*m_shader);

  // Render ImGui overlay
  renderImGui();

  m_window->swapBuffers();
  m_window->pollEvents();
}

void Renderer::updateFPS() {
  m_fpsUpdateTimer += m_deltaTime;

  if (m_fpsUpdateTimer >= 1.0f) {
    m_currentFPS = 1.0f / m_deltaTime;
    m_fpsUpdateTimer = 0.0f;
  }
}

void Renderer::renderImGui() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(200, 80), ImGuiCond_FirstUseEver);
  ImGui::Begin("Statistics", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  ImGui::Text("FPS: %.1f", m_currentFPS);
  ImGui::Text("Frame Time: %.3f ms", m_deltaTime * 1000.0f);

  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Renderer::shouldClose() const {
  return m_window->shouldClose();
}

float Renderer::getFPS() const {
  return m_currentFPS;
}

} // namespace ogl_learner
