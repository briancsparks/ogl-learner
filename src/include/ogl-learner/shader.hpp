#ifndef OGL_LEARNER_SHADER_HPP
#define OGL_LEARNER_SHADER_HPP

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace ogl_learner {

class Shader {
public:
  Shader();
  ~Shader();

  // Delete copy constructor and assignment operator
  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  // Move constructor and assignment operator
  Shader(Shader&& other) noexcept;
  Shader& operator=(Shader&& other) noexcept;

  void use() const;

  // Uniform setters
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setVec3(const std::string& name, const glm::vec3& value) const;
  void setVec4(const std::string& name, const glm::vec4& value) const;
  void setMat4(const std::string& name, const glm::mat4& value) const;

private:
  GLuint m_programId;
  void checkCompileErrors(GLuint shader, const std::string& type);
};

} // namespace ogl_learner

#endif // OGL_LEARNER_SHADER_HPP
