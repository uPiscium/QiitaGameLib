#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <functional>
#include <string>

class Window; // クラスの前方宣言

// コールバック関数の型
typedef std::function<void(Window *, int, int)> FramebufferSizeCallback;
typedef std::function<void(Window *, int, int)> WindowPosCallback;
typedef std::function<void(Window *, int, int)> WindowSizeCallback;
typedef std::function<void(Window *, int)> CursorEnterCallback;
typedef std::function<void(Window *, double, double)> CursorPosCallback;
typedef std::function<void(Window *, double, double)> ScrollCallback;

namespace callback {
// コールバック関数のラッパー
void FramebufferSizeCallbackWrapper(GLFWwindow *window, int width, int height);
void WindowPosCallbackWrapper(GLFWwindow *window, int x, int y);
void WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height);
void CursorEnterCallbackWrapper(GLFWwindow *window, int entered);
void CursorPosCallbackWrapper(GLFWwindow *window, double x, double y);
void ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset);
} // namespace callback

// ウィンドウクラス
class Window {
private:
  GLFWwindow *mWindow;
  std::pair<double, double> mCursorPos;
  std::pair<double, double> mScroll;
  FramebufferSizeCallback mFramebufferSizeCallback;
  WindowPosCallback mWindowPosCallback;
  WindowSizeCallback mWindowSizeCallback;
  CursorEnterCallback mCursorEnterCallback;
  CursorPosCallback mCursorPosCallback;
  ScrollCallback mScrollCallback;

  // コールバック関数のフレンド宣言
  friend void(callback::FramebufferSizeCallbackWrapper)(GLFWwindow *, int width,
                                                        int height);
  friend void(callback::WindowPosCallbackWrapper)(GLFWwindow *window, int x,
                                                  int y);
  friend void(callback::WindowSizeCallbackWrapper)(GLFWwindow *window,
                                                   int width, int height);
  friend void(callback::CursorEnterCallbackWrapper)(GLFWwindow *window,
                                                    int entered);
  friend void(callback::CursorPosCallbackWrapper)(GLFWwindow *window, double x,
                                                  double y);
  friend void(callback::ScrollCallbackWrapper)(GLFWwindow *window,
                                               double xoffset, double yoffset);

public:
  Window(int width, int height, std::string title);

  std::pair<double, double> GetCursorPos() const { return mCursorPos; }
  std::pair<double, double> GetScroll() const { return mScroll; }

  void SetFramebufferSizeCallback(FramebufferSizeCallback callback) {
    mFramebufferSizeCallback = callback;
  }
  void SetWindowPosCallback(WindowPosCallback callback) {
    mWindowPosCallback = callback;
  }
  void SetWindowSizeCallback(WindowSizeCallback callback) {
    mWindowSizeCallback = callback;
  }
  void SetCursorEnterCallback(CursorEnterCallback callback) {
    mCursorEnterCallback = callback;
  }
  void SetCursorPosCallback(CursorPosCallback callback) {
    mCursorPosCallback = callback;
  }
  void SetScrollCallback(ScrollCallback callback) {
    mScrollCallback = callback;
  }

  bool IsPressed(int key) const {
    return glfwGetKey(mWindow, key) == GLFW_PRESS;
  }
  bool IsClicked(int mousebutton) const {
    return glfwGetMouseButton(mWindow, mousebutton) == GLFW_PRESS;
  }
  bool IsClosed() const { return glfwWindowShouldClose(mWindow); }

  void Close() { glfwSetWindowShouldClose(mWindow, true); }
  void Update();
  void Fill(float r, float g, float b, float a);
};

#endif // __WINDOW_HPP__
