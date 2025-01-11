#ifndef OGL_LEARNER_TETRAHEDRON_HPP
#define OGL_LEARNER_TETRAHEDRON_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.hpp"

namespace ogl_learner {

class Tetrahedron {
public:
  Tetrahedron();
  ~Tetrahedron();

  // Delete copy constructor and assignment operator
  Tetrahedron(const Tetrahedron&) = delete;
  Tetrahedron& operator=(const Tetrahedron&) = delete;

  // Move constructor and assignment operator
  Tetrahedron(Tetrahedron&& other) noexcept;
  Tetrahedron& operator=(Tetrahedron&& other) noexcept;

  void draw(const Shader& shader);
  void rotate(float angle, const glm::vec3& axis);
  void setPosition(const glm::vec3& position);
  void setScale(const glm::vec3& scale);

private:
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ebo;
  glm::mat4 m_model;
  
  void setupMesh();
};

} // namespace ogl_learner

#endif // OGL_LEARNER_TETRAHEDRON_HPP
