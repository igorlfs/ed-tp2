#include "fita.hpp"
#include "msgassert.hpp"

void Fita::read(Page *p, int &n) const {
    for (int i = 0; i < n; ++i) {
        inf >> p[i].URL >> p[i].visits;

        // Tome cuidado para não chegar ao final do arquivo sem completar o laço
        // WARNING: por enquanto não sei se isso é necessário
        if (inf.eof()) n = i;
    }
}

void Fita::write(Page *p, const int &n) const {
    if (n <= 0) return; // Não escreva arquivos vazios
    std::ofstream roundRo;
    roundRo.open("rodada-" + std::to_string(ro) + ".txt");
    erroAssert(roundRo.is_open(), "Erro ao abrir arquivo de rodada");

    for (int i = 0; i < n; ++i)
        roundRo << p[i].URL << ' ' << p[i].visits << '\n';

    roundRo.close();
    erroAssert(!roundRo.is_open(), "Erro ao fechar arquivo de rodada");
}

void Fita::sort(int left, int right, Page *p) {
    int i, j;

    partition(left, right, &i, &j, p);

    if (left < j) sort(left, j, p);
    if (i < right) sort(i, right, p);
}

void Fita::partition(int left, int right, int *i, int *j, Page *p) {
    *i = left;
    *j = right;

    int pBeg = p[*i].visits;
    int pMid = p[(*i + *j) / 2].visits;
    int pEnd = p[*j].visits;

    int pivot = choosePivot(pBeg, pMid, pEnd);

    do {
        while (pivot < p[*i].visits) (*i)++;
        while (pivot > p[*j].visits) (*j)--;

        if (*i <= *j) {
            // TODO: usar insertionSort para vetores pequenos
            std::swap(p[*i], p[*j]);

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

int Fita::choosePivot(const int a, const int b, const int c) {
    if (a < b) {
        if (a > c) return a;
        else if (b < c) return b;
        return c;
    } else {
        if (a < c) return a;
        if (b < c) return c;
        return b;
    }
}
