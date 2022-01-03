#include "heap.hpp"
#include "msgassert.hpp"

std::ifstream inf;
std::ofstream ouf;
int ro = 0; // Round tracker

int init(int argc, char *argv[]);
void finish();

int main(int argc, char *argv[]) {
    int n = init(argc, argv);

    Page *p = new (std::nothrow) Page[n];
    erroAssert(p, "Erro ao alocar memória para leitura de páginas");
    Fita F;

    do {
        F.read(p, n);
        F.quickSort(p, n);
        if (n > 0) F.write(p, n);
    } while (inf.good());

    delete[] p;

    Page q[ro + 1]; // q[0] é indefinido (não tem problema no heap)
    std::ifstream roInf[ro + 1];
    for (int i = 1; i <= ro; ++i) {
        roInf[i].open("rodada-" + std::to_string(i) + ".txt");
        erroAssert(roInf[i].is_open(), "Erro ao abrir arquivo de rodada");
        roInf[i] >> q[i].URL >> q[i].visits;
        erroAssert(!roInf[i].bad(), "Erro ao escrever arquivo de rodada");
        q[i].round = i;
    }

    Heap H;
    H.build(q, ro);
    while (ro > 0) {
        Page x = H.pop(q, ro);
        ouf << x.URL << ' ' << x.visits << '\n';
        int origin = x.round;
        if (!roInf[origin].eof()) {
            Page y;
            roInf[origin] >> y.URL >> y.visits;
            erroAssert(!roInf[origin].bad(),
                       "Erro ao escrever arquivo de rodada");
            y.round = origin;
            if (!y.URL.empty()) H.push(q, y, ro);
        } else {
            roInf[origin].close();
            erroAssert(!roInf[origin].is_open(),
                       "Erro ao fechar arquivo de rodada");
        }
    }

    finish();

    return 0;
}

int init(int argc, char *argv[]) {
    erroAssert(argc > 3,
               "Passe os arquivos e número de páginas como parâmetros");

    inf.open(argv[1]);
    erroAssert(inf.is_open(), "Erro ao abrir arquivo de entrada");
    ouf.open(argv[2]);
    erroAssert(ouf.is_open(), "Erro ao abrir arquivo de saída");

    return atoi(argv[3]);
}

void finish() {
    inf.close();
    erroAssert(!inf.is_open(), "Erro ao fechar arquivo de entrada");
    ouf.close();
    erroAssert(!ouf.is_open(), "Erro ao fechar arquivo de saída");
}
