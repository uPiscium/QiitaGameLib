#include "../../includes/Article2/init.hpp"

#include <stdexcept>

bool OpenGLContext::sGLFWInitialized = false;
bool OpenGLContext::sGLADInitialized = false;

OpenGLContext::OpenGLContext(unsigned major, unsigned minor) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

OpenGLContext::~OpenGLContext() {
  if (OpenGLContext::sGLADInitialized) {
    glfwTerminate();
  }
}

void OpenGLContext::InitGLAD() {
  if (!OpenGLContext::sGLADInitialized) {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed to initialize GLAD");
    }
    OpenGLContext::sGLADInitialized = true;
  }
}
