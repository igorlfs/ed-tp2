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
    void sort(int left, int right, Page *p);
    void partition(int left, int right, int *i, int *j, Page *p);
    int choosePivot(const int a, const int b, const int c);
};

extern std::ifstream inf;
extern std::ofstream ouf;
extern int ro;
