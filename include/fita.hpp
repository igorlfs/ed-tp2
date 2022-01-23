#pragma once

#include <fstream>
#include <string>

using std::string;

struct Page {
    string URL;
    int visits;
    int round{0};
};

inline bool operator<(const Page &lhs, const Page &rhs) {
    if (lhs.visits < rhs.visits) return true;
    else if (lhs.visits == rhs.visits && lhs.URL > rhs.URL) return true;
    return false;
}

inline bool operator>(const Page &lhs, const Page &rhs) {
    return operator<(rhs, lhs);
}

inline bool operator>=(const Page &lhs, const Page &rhs) {
    return !operator<(lhs, rhs);
}

class Fita {
  public:
    void sortFitas(int &n);
    void quickSort(Page *p, const int &n) { sort(0, n - 1, p); }

  private:
    void read(Page *p, int &n) const;
    void write(Page *p, const int &n) const;
    void sort(const int &left, const int &right, Page *p) const;
    void partition(const int &left, const int &right, int *i, int *j,
                   Page *p) const;
    Page choosePivot(const Page &a, const Page &b, const Page &c) const;
    void insertionSort(Page *p, const int low, const int &n) const;
};

extern std::ifstream inputFile;
extern std::ofstream outputFile;
extern int roundTracker;
