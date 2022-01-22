#include "heap.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

memlog ml;
std::ifstream inputFile;
std::ofstream outputFile;
int roundTracker = 0;

int init(int argc, char *argv[]);
void finish();

int main(int argc, char *argv[]) {
    int numPages = init(argc, argv);
    Fita F;
    ml.ativaMemLog();
    F.sortFitas(numPages);

    Page P[roundTracker + 1]; // q[0] é indefinido (não tem problema no heap)
    std::ifstream roundInputFile[roundTracker + 1];
    Heap H(roundTracker);
    H.read(roundInputFile);
    H.build(roundTracker);
    H.intercalate(roundInputFile);

    finish();
    return ml.finalizaMemLog();
}

int init(int argc, char *argv[]) {
    erroAssert(argc > 3,
               "Passe os arquivos e número de páginas como parâmetros");

    string inputName = argv[1];
    string logName = "log-" + inputName;
    ml.iniciaMemLog(logName);

    inputFile.open(argv[1]);
    erroAssert(inputFile.is_open(), "Erro ao abrir arquivo de entrada");
    outputFile.open(argv[2]);
    erroAssert(outputFile.is_open(), "Erro ao abrir arquivo de saída");

    int n = atoi(argv[3]);
    erroAssert(n > 0, "O número de páginas deve ser positivo");

    return n;
}

void finish() {
    inputFile.close();
    erroAssert(!inputFile.is_open(), "Erro ao fechar arquivo de entrada");
    outputFile.close();
    erroAssert(!outputFile.is_open(), "Erro ao fechar arquivo de saída");
}
