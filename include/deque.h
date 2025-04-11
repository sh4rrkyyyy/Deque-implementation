#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <vector>

inline constexpr size_t BUCKET_SIZE = 512;

class Deque {
public:
  Deque();
  Deque(const Deque &other);

  Deque &operator=(const Deque &other);
  Deque(std::initializer_list<int32_t> data);
  ~Deque();
  void Clear();
  void PushBack(int32_t val);
  void PushFront(int32_t val);

  void PopBack();
  void PopFront();
  int32_t &operator[](size_t index);
  const int32_t &operator[](size_t index) const;

  size_t Size() const;
  void Swap(Deque &other);

private:
  std::vector<int32_t *> data_;
  int32_t begin_, end_;
  int32_t first_, last_;

  void resize();
  int32_t &getElem(size_t index) const;
  void copy(const Deque &other);
};
