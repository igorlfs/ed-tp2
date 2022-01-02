#pragma once

#include <fstream>
#include <string>

using std::string;

struct Page {
    int visits;
    string URL;
};

class Fita {
  public:
    void read(Page *p, int &n) const;
    void quickSort(Page *p, const int &n) { sort(0, n - 1, p); }
    void write(Page *p, const int &n) const;

  private:
    void sort(const int &left, const int &right, Page *p) const;
    void partition(const int &left, const int &right, int *i, int *j,
                   Page *p) const;
};

extern std::ifstream inf;
extern std::ofstream ouf;
extern int ro;
