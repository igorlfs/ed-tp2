#include "fita.hpp"
#include "msgassert.hpp"
#include <sstream>

void Fita::read(Page *p, int &n) const {
    for (int i = 0; i < n; ++i) {
        string line;
        std::getline(inf, line);
        std::stringstream ss(line);
        // Tome cuidado para não chegar ao final do arquivo sem completar o laço
        if (inf.eof()) n = i;
        ss >> p[i].URL >> p[i].visits;
    }
    erroAssert(!inf.bad(), "Erro na leitura de rodadas");
}

void Fita::write(Page *p, const int &n) const {
    ro++;
    std::ofstream roOuf;
    roOuf.open("rodada-" + std::to_string(ro) + ".txt");
    erroAssert(roOuf.is_open(), "Erro ao abrir arquivo de rodada");

    for (int i = 0; i < n; ++i)
        roOuf << p[i].URL << ' ' << p[i].visits << '\n';

    erroAssert(!roOuf.bad(), "Erro na escrita de rodadas");
    roOuf.close();
    erroAssert(!roOuf.is_open(), "Erro ao fechar arquivo de rodada");
}

void Fita::sortFitas(int &n) {
    Page *p = new (std::nothrow) Page[n];
    erroAssert(p, "Erro ao alocar memória para leitura de páginas");

    do {
        read(p, n);
        quickSort(p, n);
        if (n > 0) write(p, n);
    } while (inf.good());

    delete[] p;
}

void Fita::sort(const int &left, const int &right, Page *p) const {
    int i, j;

    partition(left, right, &i, &j, p);

    if (left < j) sort(left, j, p);
    if (i < right) sort(i, right, p);
}

void Fita::partition(const int &left, const int &right, int *i, int *j,
                     Page *p) const {
    *i = left;
    *j = right;

    Page pBeg = p[*i];
    Page pMid = p[(*i + *j) / 2];
    Page pEnd = p[*j];

    Page pivot = choosePivot(pBeg, pMid, pEnd);

    do {
        while (pivot < p[*i])
            (*i)++;
        while (pivot > p[*j])
            (*j)--;

        if (*i <= *j) {
            // TODO: usar insertionSort para vetores pequenos
            std::swap(p[*i], p[*j]);

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

Page Fita::choosePivot(const Page &a, const Page &b, const Page &c) const {
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
