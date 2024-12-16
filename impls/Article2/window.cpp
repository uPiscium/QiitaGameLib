#include "../../includes/Article2/window.hpp"
#include "../../includes/Article2/init.hpp"

namespace callback {
void FramebufferSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window); // 紐付けたポインタ
  if (ptr->mFramebufferSizeCallback) { // コールバック関数が登録されている
    ptr->mFramebufferSizeCallback(ptr, width, height);
  }
}

void WindowPosCallbackWrapper(GLFWwindow *window, int x, int y) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  if (ptr->mWindowPosCallback) {
    ptr->mWindowPosCallback(ptr, x, y);
  }
}

void WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  if (ptr->mWindowSizeCallback) {
    ptr->mWindowSizeCallback(ptr, width, height);
  }
}

void CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  if (ptr->mCursorEnterCallback) {
    ptr->mCursorEnterCallback(ptr, entered);
  }
}

void CursorPosCallbackWrapper(GLFWwindow *window, double x, double y) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCursorPos = {x, y};
  if (ptr->mCursorPosCallback) {
    ptr->mCursorPosCallback(ptr, x, y);
  }
}

void ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mScroll = {xoffset, yoffset};
  if (ptr->mScrollCallback) {
    ptr->mScrollCallback(ptr, xoffset, yoffset);
  }
}
} // namespace callback

Window::Window(int width, int height, std::string title) {
  // ウィンドウの作成
  mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(mWindow);
  OpenGLContext::InitGLAD();

  glfwSetWindowUserPointer(mWindow, this); // 自分のポインタをGLFWwindowと紐付け
  // コールバックを登録
  glfwSetFramebufferSizeCallback(mWindow,
                                 callback::FramebufferSizeCallbackWrapper);
  glfwSetWindowPosCallback(mWindow, callback::WindowPosCallbackWrapper);
  glfwSetWindowSizeCallback(mWindow, callback::WindowSizeCallbackWrapper);
  glfwSetCursorEnterCallback(mWindow, callback::CursorEnterCallbackWrapper);
  glfwSetCursorPosCallback(mWindow, callback::CursorPosCallbackWrapper);
  glfwSetScrollCallback(mWindow, callback::ScrollCallbackWrapper);
}

void Window::Update() {
  // バッファのスワップとイベントのポーリング
  glfwSwapBuffers(mWindow);
  glfwPollEvents();
}

void Window::Fill(float r, float g, float b, float a) {
  // 背景色の設定とクリア
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}
