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
    Heap H(ro);
    H.read(roInf);
    H.build(ro);
    H.intercalate(roInf);

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
