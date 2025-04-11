#include "deque.h"

Deque::Deque() {
  data_.resize(2);
  data_[0] = new int32_t[BUCKET_SIZE];
  data_[1] = new int32_t[BUCKET_SIZE];
  begin_ = 0;
  end_ = 1;
  first_ = BUCKET_SIZE - 1, last_ = 0;
}

Deque::Deque(const Deque &other) { this->copy(other); }

Deque &Deque::operator=(const Deque &other) {
  if (this != &other) {
    this->copy(other);
  }
  return *this;
}

Deque::Deque(std::initializer_list<int32_t> data) {
  data_.resize(std::max(2ul, data.size() / BUCKET_SIZE + 1));
  for (size_t i = 0; i < data_.size(); ++i) {
    data_[i] = new int32_t[BUCKET_SIZE];
  }
  begin_ = data_.size() / 2 - 1;
  end_ = data_.size() / 2;
  first_ = BUCKET_SIZE - 1, last_ = 0;
  for (const auto &val : data) {
    PushBack(val);
  }
}

Deque::~Deque() {
  for (auto ptr : data_) {
    if (ptr != nullptr)
      delete[] ptr;
  }
}

void Deque::Clear() {
  for (auto ptr : data_) {
    delete[] ptr;
  }
  data_.resize(2);
  data_[0] = new int32_t[BUCKET_SIZE];
  data_[1] = new int32_t[BUCKET_SIZE];
  begin_ = 0;
  end_ = 1;
  first_ = BUCKET_SIZE - 1, last_ = 0;
}

void Deque::PushBack(int32_t val) {
  if (last_ == BUCKET_SIZE) {
    end_ = (end_ + 1) % data_.size();
    last_ = 0;
    if (end_ == begin_) {
      this->resize();
    }
  }
  data_[end_][last_] = val;
  last_++;
}

void Deque::PushFront(int32_t val) {
  if (first_ == -1) {
    begin_ = (begin_ - 1 + data_.size()) % data_.size();
    first_ = BUCKET_SIZE - 1;
    if (end_ == begin_) {
      this->resize();
    }
  }
  data_[begin_][first_] = val;
  first_--;
}

void Deque::PopBack() {
  if (this->Size() == 0)
    return;
  if (last_ == 0) {
    last_ = BUCKET_SIZE - 1;
    end_ = (end_ - 1 + data_.size()) % data_.size();
  } else {
    last_--;
  }
}

void Deque::PopFront() {
  if (this->Size() == 0)
    return;
  if (first_ == BUCKET_SIZE - 1) {
    first_ = 0;
    begin_ = (begin_ + 1) % data_.size();
  } else {
    first_++;
  }
}
int32_t &Deque::operator[](size_t index) { return getElem(index); }

const int32_t &Deque::operator[](size_t index) const { return getElem(index); }

size_t Deque::Size() const {
  if (begin_ < end_ || (begin_ == end_ && first_ <= last_)) {
    return BUCKET_SIZE - first_ - 1 + (end_ - begin_ - 1) * BUCKET_SIZE + last_;
  } else {
    return BUCKET_SIZE - first_ - 1 +
           (data_.size() - (begin_ - end_ + 1)) * BUCKET_SIZE + last_;
  }
}
void Deque::Swap(Deque &other) {
  std::swap(data_, other.data_);
  std::swap(begin_, other.begin_);
  std::swap(end_, other.end_);
  std::swap(first_, other.first_);
  std::swap(last_, other.last_);
}

void Deque::resize() {
  std::vector<int32_t *> tmp(2 * data_.size(), 0);
  for (size_t i = 0; i < data_.size() / 2; ++i) {
    tmp[i] = new int32_t[BUCKET_SIZE];
  }
  for (auto i = data_.size() + data_.size() / 2; i < tmp.size(); ++i) {
    tmp[i] = new int32_t[BUCKET_SIZE];
  }
  auto j = data_.size() / 2;
  for (auto i = begin_; i != end_ || j == data_.size() / 2;
       i = (i + 1) % data_.size()) {
    tmp[j++] = data_[i];
  }
  begin_ = data_.size() / 2;
  end_ = j;
  data_ = std::move(tmp);
}
int32_t &Deque::getElem(size_t index) const {
  if (index < BUCKET_SIZE - first_ - 1) {
    return data_[begin_][first_ + 1 + index];
  } else {
    auto first_not_empty = BUCKET_SIZE - first_ - 1;
    auto diff = index - first_not_empty;
    auto quot = diff / BUCKET_SIZE;
    auto rmd = diff % BUCKET_SIZE;
    return data_[(begin_ + quot + 1) % data_.size()][rmd];
  }
}

void Deque::copy(const Deque &other) {
  data_.resize(other.data_.size());
  for (size_t i = 0; i < data_.size(); ++i) {
    delete[] data_[i];
    data_[i] = new int32_t[BUCKET_SIZE];
  }
  begin_ = other.begin_;
  end_ = other.end_;
  first_ = other.first_;
  last_ = other.last_;
  for (size_t i = 0; i < data_.size(); ++i) {
    std::copy(other.data_[i], other.data_[i] + BUCKET_SIZE, data_[i]);
  }
}
