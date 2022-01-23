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
    Page aux = this->pages[i];

    while (j <= right) {
        if (j < right)
            if (this->pages[j] < this->pages[j + 1]) j++;
        if (aux >= this->pages[j]) break;
        this->pages[i] = this->pages[j];
        i = j;
        j = i * 2;
    }
    this->pages[i] = aux;
}

Page Heap::pop() {
    erroAssert(this->size >= 1, "Heap vazio, não é possível remover");
    Page max = this->pages[1];
    this->pages[1] = this->pages[this->size];
    this->size--;
    remake(1, this->size);
    return max;
}

void Heap::push(const Page &q) {
    this->size++;
    this->pages[this->size] = q;
    build(this->size);
}

void Heap::intercalate(std::ifstream *roundInputFile) {
    while (this->size > 0) {
        Page x = pop();
        int origin = x.round;

        outputFile << x.URL << ' ' << x.visits << '\n';
        erroAssert(!outputFile.bad(), "Erro ao escrever arquivo de rodada");
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
