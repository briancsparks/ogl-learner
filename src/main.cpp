#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <iostream>

int main(int argc, char** argv) {
  CLI::App app{"OpenGL Learner Project"};
  
  // Initialize logging
  spdlog::set_level(spdlog::level::debug);
  
  CLI11_PARSE(app, argc, argv);
  
  std::cout << "Hello, OpenGL Learner!" << std::endl;
  spdlog::info("Application started successfully");
  
  return 0;
}
