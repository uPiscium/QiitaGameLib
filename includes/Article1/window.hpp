#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <string>

class Window {
private:
  GLFWwindow *mWindow;

public:
  Window(int width, int height, std::string title);

  void Update();
  void Fill(float r, float g, float b, float a);
};

#endif // __WINDOW_HPP__
