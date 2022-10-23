#pragma once

#include <exception>
#include <stdexcept>
#include <utility>

class Slice {
 public:
  Slice();
  Slice(const size_t &begin, const size_t &end, const int &step = 1);
  size_t Begin() const;
  size_t End() const;
  int Step() const;

 private:
  size_t begin_;
  size_t end_;
  int step_;
};