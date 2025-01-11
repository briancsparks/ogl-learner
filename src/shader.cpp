#include "ogl-learner/shader.hpp"
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

namespace ogl_learner {

// ----- vertex shader -----
const char* vShaderCode = R"(
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  ourColor = aColor;
})";

// ----- fragment shader -----
const char* fShaderCode = R"(
#version 410 core

in vec3 ourColor;
out vec4 FragColor;

void main() {
  FragColor = vec4(ourColor, 1.0);
})";


Shader::Shader(/*const char* vertexPath, const char* fragmentPath*/) : m_programId(0) {

  GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  m_programId = glCreateProgram();
  glAttachShader(m_programId, vertex);
  glAttachShader(m_programId, fragment);
  glLinkProgram(m_programId);
  checkCompileErrors(m_programId, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() {
  if (m_programId) {
    glDeleteProgram(m_programId);
  }
}

Shader::Shader(Shader&& other) noexcept : m_programId(other.m_programId) {
  other.m_programId = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
  if (this != &other) {
    if (m_programId) {
      glDeleteProgram(m_programId);
    }
    m_programId = other.m_programId;
    other.m_programId = 0;
  }
  return *this;
}

void Shader::use() const {
  glUseProgram(m_programId);
}

void Shader::setBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
  glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
  glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
  glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
  int success;
  char infoLog[1024];

  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      spdlog::error("Shader compilation error of type {}: {}", type, infoLog);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      spdlog::error("Program linking error of type {}: {}", type, infoLog);
    }
  }
}

} // namespace ogl_learner
