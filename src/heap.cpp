#include "heap.hpp"
#include "msgassert.hpp"
#include <iostream>

Heap::Heap(const int &size) {
    this->size = size;
    this->pages = new (std::nothrow) Page[size + 1];
    erroAssert(this->pages, "Falha ao alocar dinamicamente a célula.");
}

void Heap::read(std::ifstream *roundInputFile) {
    for (int i = 1; i <= roundTracker; ++i) {
        roundInputFile[i].open("rodada-" + std::to_string(i) + ".txt");
        erroAssert(roundInputFile[i].is_open(),
                   "Erro ao abrir arquivo de rodada: " << i);
        roundInputFile[i] >> this->pages[i].URL >> this->pages[i].visits;
        erroAssert(!roundInputFile[i].bad(),
                   "Erro ao ler arquivo de rodada para construir heap");
        this->pages[i].round = i;
    }
}

void Heap::build(const int &n) {
    int left = n / 2 + 1;
    while (left > 1) {
        left--;
        remake(left, n);
    }
}

void Heap::remake(const int &left, const int &right) {
    int i = left, j = i * 2;
    Page aux = pages[i];

    while (j <= right) {
        if (j < right)
            if (pages[j] < pages[j + 1]) j++;
        if (aux >= pages[j]) break;
        pages[i] = pages[j];
        i = j;
        j = i * 2;
    }
    pages[i] = aux;
}

Page Heap::pop() {
    Page max;
    erroAssert(size >= 1, "Heap vazio, não é possível remover");
    max = this->pages[1];
    this->pages[1] = this->pages[size];
    this->size--;
    remake(1, this->size);
    return max;
}

void Heap::push(const Page &q) {
    size++;
    pages[size] = q;
    remake(1, size);
}

void Heap::intercalate(std::ifstream *roundInputFile) {
    while (this->size > 0) {
        Page x = pop();
        int origin = x.round;

        outputFile << x.URL << ' ' << x.visits << '\n';
        if (!roundInputFile[origin].eof()) {
            Page y;

            y.round = origin;
            roundInputFile[origin] >> y.URL >> y.visits;
            erroAssert(!roundInputFile[origin].bad(),
                       "Erro ao escrever arquivo de rodada");
            // Algumas URLs ficam vazias, mas é fácil contornar isso:
            if (!y.URL.empty()) push(y);
        } else {
            roundInputFile[origin].close();
            erroAssert(!roundInputFile[origin].is_open(),
                       "Erro ao fechar arquivo de rodada");
        }
    }
}
