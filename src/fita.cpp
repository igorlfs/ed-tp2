#include "fita.hpp"
#include "msgassert.hpp"
#include <sstream>

void Fita::read(Page *p, int &n) const {
    for (int i = 0; i < n; ++i) {
        string line;
        std::getline(inputFile, line);
        std::stringstream ss(line);
        // Tome cuidado para não chegar ao final do arquivo sem completar o laço
        if (inputFile.eof()) n = i;
        ss >> p[i].URL >> p[i].visits;
    }
    erroAssert(!inputFile.bad(), "Erro na leitura de rodadas");
}

void Fita::write(Page *p, const int &n) const {
    roundTracker++;
    std::ofstream roundOutputFile;
    roundOutputFile.open("rodada-" + std::to_string(roundTracker) + ".txt");
    erroAssert(roundOutputFile.is_open(), "Erro ao abrir arquivo de rodada");

    for (int i = 0; i < n; ++i)
        roundOutputFile << p[i].URL << ' ' << p[i].visits << '\n';

    erroAssert(!roundOutputFile.bad(), "Erro na escrita de rodadas");
    roundOutputFile.close();
    erroAssert(!roundOutputFile.is_open(), "Erro ao fechar arquivo de rodada");
}

void Fita::sortFitas(int &n) {
    Page *p = new (std::nothrow) Page[n];
    erroAssert(p, "Erro ao alocar memória para leitura de páginas");

    do {
        read(p, n);
        quickSort(p, n);
        if (n > 0) write(p, n);
    } while (inputFile.good());

    delete[] p;
}

void Fita::sort(const int &left, const int &right, Page *p) const {
    int i, j;

    partition(left, right, &i, &j, p);

    if (right - left <= 25) {
        insertionSort(p, left, right);
    } else {
        if (left < j) sort(left, j, p);
        if (i < right) sort(i, right, p);
    }
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
            std::swap(p[*i], p[*j]);

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

Page Fita::choosePivot(const Page &a, const Page &b, const Page &c) const {
    if ((a < b) ^ (a > c)) return a;
    else if ((b < a) ^ (b < c)) return b;
    else return c;
}

void Fita::insertionSort(Page *p, const int low, const int &n) const {
    for (int i = low; i <= n; ++i) {
        Page aux = p[i];
        int j = i - 1;
        while ((j >= low) && (aux > p[j])) {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = aux;
    }
}
