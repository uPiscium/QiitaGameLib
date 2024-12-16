#ifndef __INIT_HPP__
#define __INIT_HPP__

#include <glad/gl.h>

#include <GLFW/glfw3.h>

class OpenGLContext {
private:
  static bool sGLFWInitialized;
  static bool sGLADInitialized;

public:
  OpenGLContext(unsigned major, unsigned minor);
  ~OpenGLContext();

public:
  static void InitGLAD();
};

#endif // __INIT_HPP__
