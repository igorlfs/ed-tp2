#pragma once

#include "fita.hpp"

class Heap {
  public:
    Heap(const int &size);
    ~Heap() { delete[] pages; }
    void read(std::ifstream *roInf);
    void build(const int &n);
    void intercalate(std::ifstream *roInf);

  private:
    void remake(const int &left, const int &right);
    Page pop();
    void push(const Page &q);

    Page *pages;
    int size;
};
