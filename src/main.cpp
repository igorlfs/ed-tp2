#include "fita.hpp"
#include "msgassert.hpp"

std::ifstream inf;
std::ofstream ouf;
int ro = 0; // Round tracker

int init(int argc, char *argv[]);
void finish();

int main(int argc, char *argv[]) {
    int n = init(argc, argv);

    Page *p = new Page[n];
    Fita F;

    do {
        F.read(p, n);
        F.quickSort(p, n);
        if (n > 0) F.write(p, n);
    } while (inf.good());

    delete[] p;

    // PERF: Não consigo inserir essas URLs pós quicksort?
    Page q[ro - 2];
    for (int i = 0; i < ro - 2; ++i) {
        std::ifstream roInf;
        roInf.open("rodada-" + std::to_string(i + 1) + ".txt");
        roInf >> q[i].URL >> q[i].visits;
        std::cout << i << ' ' << q[i].visits << '\n';
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
