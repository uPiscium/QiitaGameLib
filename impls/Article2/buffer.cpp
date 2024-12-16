#include <stdexcept>

#include "../../includes/Article2/buffer.hpp"

Buffer::Buffer(int bufferType) {
  // VAO, VBO, IBOの生成
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mIBO);

  glBindVertexArray(mVAO); // VAOをバインド
  // VBOをバインド(バインドされているVAOにVBOを紐付け)
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  // IBOをバインド(バインドされているVAOにIBOを紐付け)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

  mIndexCount = 0;
  mSize = 0;
  mBufferType = bufferType;

  // バインドを解除
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Buffer::~Buffer() {
  // バッファの削除
  glDeleteVertexArrays(1, &mVAO);
  glDeleteBuffers(1, &mVBO);
  glDeleteBuffers(1, &mIBO);
}

void Buffer::SetBuffer(std::vector<float> data) {
  mSize = data.size();

  // バッファをバインド
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  // データをVBOに転送
  glBufferData(GL_ARRAY_BUFFER, mSize * sizeof(float), data.data(),
               mBufferType);

  // バインドを解除
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::SetIndices(std::vector<unsigned> indices) {
  mIndexCount = indices.size();

  // バッファをバインド
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

  // データをIBOに転送
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof(unsigned),
               indices.data(), mBufferType);

  // バインドを解除
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::AddAttribute(int loc, int comps, int offset) {
  // バッファをバインド
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  // 頂点属性の設定
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, comps, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void *>(offset));

  // バインドを解除
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::ReloadBuffer(std::vector<float> data) {
  if (data.size() !=
      mSize) { // データサイズがバッファサイズと一致しない場合はエラー
    throw std::runtime_error("Data size does not match buffer size");
  }

  // バッファをバインド
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  // データをVBOに転送
  glBufferSubData(GL_ARRAY_BUFFER, 0, mSize * sizeof(float), data.data());

  // バインドを解除
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::Draw(int drawmode) {
  if (mIndexCount == 0) {
    throw std::runtime_error("No indices to draw");
  }

  glBindVertexArray(mVAO); // VAOをバインド
  // バッファを描画(VAOにIBOが紐付いているのでIBOの情報を使って描画)
  glDrawElements(drawmode, mIndexCount, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0); // VAOのバインドを解除
}
