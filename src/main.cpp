#include "heap.hpp"
#include "msgassert.hpp"

std::ifstream inf;
std::ofstream ouf;
int ro = 0; // Round tracker

int init(int argc, char *argv[]);
void finish();

int main(int argc, char *argv[]) {
    int n = init(argc, argv);
    Fita F;
    F.sortFitas(n);

    Page q[ro + 1]; // q[0] é indefinido (não tem problema no heap)
    std::ifstream roInf[ro + 1];

    Heap H;
    H.read(roInf, q);

    H.build(q, ro);
    while (ro > 0) {
        Page x = H.pop(q, ro);
        int origin = x.round;

        ouf << x.URL << ' ' << x.visits << '\n';
        if (!roInf[origin].eof()) {
            Page y;

            y.round = origin;
            roInf[origin] >> y.URL >> y.visits;
            erroAssert(!roInf[origin].bad(),
                       "Erro ao escrever arquivo de rodada");
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
