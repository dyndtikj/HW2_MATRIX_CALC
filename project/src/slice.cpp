#include "slice.h"

Slice::Slice() : begin_(0), end_(0), step_(0) {}

Slice::Slice(const size_t &begin, const size_t &end, const int &step)
    : begin_(begin), end_(end), step_(step) {}

size_t Slice::Begin() const { return begin_; }
size_t Slice::End() const { return end_; }
int Slice::Step() const { return step_; }
