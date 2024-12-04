#include "../../includes/Article1/window.hpp"

Window::Window(int width, int height, std::string title) {
  mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(mWindow);
}
