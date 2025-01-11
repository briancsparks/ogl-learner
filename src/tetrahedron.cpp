#include "ogl-learner/tetrahedron.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ogl_learner {

Tetrahedron::Tetrahedron() : m_vao(0), m_vbo(0), m_ebo(0), m_model(1.0f) {
  setupMesh();
}

Tetrahedron::~Tetrahedron() {
  if (m_vao) glDeleteVertexArrays(1, &m_vao);
  if (m_vbo) glDeleteBuffers(1, &m_vbo);
  if (m_ebo) glDeleteBuffers(1, &m_ebo);
}

Tetrahedron::Tetrahedron(Tetrahedron&& other) noexcept
  : m_vao(other.m_vao)
  , m_vbo(other.m_vbo)
  , m_ebo(other.m_ebo)
  , m_model(std::move(other.m_model)) {
  other.m_vao = 0;
  other.m_vbo = 0;
  other.m_ebo = 0;
}

Tetrahedron& Tetrahedron::operator=(Tetrahedron&& other) noexcept {
  if (this != &other) {
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);

    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    m_model = std::move(other.m_model);

    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;
  }
  return *this;
}

void Tetrahedron::setupMesh() {
  // Vertices of a tetrahedron with position and color
  float vertices[] = {
    // Position           // Color
     0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  // 0: Top vertex (red)
    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,  // 1: Front-left vertex (green)
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // 2: Front-right vertex (blue)
     0.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f   // 3: Back vertex (yellow)
  };

  // Indices for the triangles
  unsigned int indices[] = {
    0, 1, 2,  // Front face
    0, 2, 3,  // Right face
    0, 3, 1,  // Left face
    1, 3, 2   // Bottom face
  };

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Tetrahedron::draw(const Shader& shader) {
  shader.use();
  shader.setMat4("model", m_model);

  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Tetrahedron::rotate(float angle, const glm::vec3& axis) {
  m_model = glm::rotate(m_model, glm::radians(angle), axis);
}

void Tetrahedron::setPosition(const glm::vec3& position) {
  m_model = glm::translate(glm::mat4(1.0f), position);
}

void Tetrahedron::setScale(const glm::vec3& scale) {
  m_model = glm::scale(m_model, scale);
}

} // namespace ogl_learner
