#pragma once

#include "fita.hpp"

class Heap {
  public:
    void read(std::ifstream *roInf, Page *p);
    void build(Page *p, const int &n) const;
    void remake(const int &left, const int &right, Page *p) const;
    Page pop(Page *p, int &n) const;
    void push(Page *p, const Page &q, int &n) const;
};
