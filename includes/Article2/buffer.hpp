#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <vector>

class Buffer {
private:
  GLuint mVAO;
  GLuint mVBO;
  GLuint mIBO;
  GLuint mIndexCount; // インデックスの要素数
  unsigned mSize;
  int mBufferType;

public:
  Buffer(int bufferType);
  ~Buffer();

  unsigned const &GetSize() const { return mSize; }

  void SetBuffer(std::vector<float> data);
  void SetIndices(std::vector<unsigned> indices);

  void AddAttribute(int loc, int comps, int offset);

  void ReloadBuffer(std::vector<float> data);
  void Draw(int drawmode);
};
#endif // __BUFFER_HPP__
