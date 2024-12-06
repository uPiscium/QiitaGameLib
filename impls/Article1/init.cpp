#include "../../includes/Article1/init.hpp"

#include <stdexcept>

bool sGLADLoaded = false;

void InitGLAD() {
  if (!sGLADLoaded) {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed to initialize GLAD");
    }
    sGLADLoaded = true;
  }
}
