#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "../../includes/Article2/buffer.hpp"
#include "../../includes/Article2/init.hpp"
#include "../../includes/Article2/window.hpp"

// 関数宣言
void framebuffer_size_callback(Window *window, int width, int height);
unsigned int createShaderProgram(const char *vertexSource,
                                 const char *fragmentSource);

// 頂点シェーダーのソースコード
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

// フラグメントシェーダーのソースコード
const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

int main() {
  // GLFWの初期化
  OpenGLContext context(3, 3);

  // ウィンドウの作成
  Window window(800, 600, "OpenGL");

  // ビューポートの設定
  glViewport(0, 0, 800, 600);
  window.SetFramebufferSizeCallback(framebuffer_size_callback);

  // シェーダープログラムの作成
  unsigned int shaderProgram =
      createShaderProgram(vertexShaderSource, fragmentShaderSource);

  // 三角形の頂点データ
  std::vector<float> vertices = {
      0.0f,  0.5f,  0.0f, // 上
      -0.5f, -0.5f, 0.0f, // 左下
      0.5f,  -0.5f, 0.0f  // 右下
  };

  Buffer buffer(GL_STATIC_DRAW);
  buffer.SetBuffer(vertices);   // データをバッファにセット
  buffer.AddAttribute(0, 3, 0); // 頂点属性を追加
  buffer.SetIndices({0, 1, 2}); // インデックスをセット

  // メインループ
  while (!window.IsClosed()) {
    // 入力処理
    if (window.IsPressed(GLFW_KEY_ESCAPE)) {
      window.Close();
    }

    // 背景色の設定とクリア
    window.Fill(0.2f, 0.2f, 0.2f, 1.0f);

    // シェーダープログラムの使用
    glUseProgram(shaderProgram);

    // 三角形の描画
    buffer.Draw(GL_TRIANGLES);

    // バッファのスワップとイベントのポーリング
    window.Update();
  }

  return 0;
}

// ウィンドウサイズが変更されたときのコールバック関数
void framebuffer_size_callback(Window *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// シェーダープログラムの作成関数
unsigned int createShaderProgram(const char *vertexSource,
                                 const char *fragmentSource) {
  // 頂点シェーダーのコンパイル
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);

  // コンパイルエラーチェック
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // フラグメントシェーダーのコンパイル
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);

  // コンパイルエラーチェック
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // シェーダープログラムのリンク
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // リンクエラーチェック
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  // シェーダーオブジェクトの削除
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}
