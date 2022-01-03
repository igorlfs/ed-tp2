#include "heap.hpp"
#include <iostream>

void Heap::build(Page *p, const int &n) const {
    int left = n / 2 + 1;
    while (left > 1) {
        left--;
        remake(left, n, p);
    }
}

void Heap::remake(const int &left, const int &right, Page *p) const {
    int i = left, j = i * 2;
    Page aux = p[i];

    while (j <= right) {
        if (j < right)
            if (p[j] < p[j + 1]) j++;
        if (aux >= p[j]) break;
        p[i] = p[j];
        i = j;
        j = i * 2;
    }
    p[i] = aux;
}

Page Heap::pop(Page *p, int &n) const {
    Page max;
    if (n < 1) {
        std::cerr << "cuuu\n";
        abort(); // tratar exceção
    }
    max = p[1];
    p[1] = p[n];
    n--;
    remake(1, n, p);
    return max;
}

void Heap::push(Page *p, const Page &q, int &n) const {
    n++;
    p[n] = q;
    remake(1, n, p);
}
