#include "heap.hpp"
#include "msgassert.hpp"

std::ifstream inputFile;
std::ofstream outputFile;
int roundTracker = 0;

int init(int argc, char *argv[]);
void finish();

int main(int argc, char *argv[]) {
    int n = init(argc, argv);
    Fita F;
    F.sortFitas(n);

    Page P[roundTracker + 1]; // q[0] é indefinido (não tem problema no heap)
    std::ifstream roundInputFile[roundTracker + 1];
    Heap H(roundTracker);
    H.read(roundInputFile);
    H.build(roundTracker);
    H.intercalate(roundInputFile);

    finish();

    return 0;
}

int init(int argc, char *argv[]) {
    erroAssert(argc > 3,
               "Passe os arquivos e número de páginas como parâmetros");

    inputFile.open(argv[1]);
    erroAssert(inputFile.is_open(), "Erro ao abrir arquivo de entrada");
    outputFile.open(argv[2]);
    erroAssert(outputFile.is_open(), "Erro ao abrir arquivo de saída");

    return atoi(argv[3]);
}

void finish() {
    inputFile.close();
    erroAssert(!inputFile.is_open(), "Erro ao fechar arquivo de entrada");
    outputFile.close();
    erroAssert(!outputFile.is_open(), "Erro ao fechar arquivo de saída");
}
