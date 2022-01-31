#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

long double avg(long double *array, const int &size) {
    long double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / size;
}

int main() {
    constexpr int TESTS = 10;
    long double time[2][TESTS];

    for (int i = 0; i < TESTS; ++i) {
        string line;
        getline(cin, line); // Ignore a linha com o tempo inicial
        getline(cin, line); // Pegue a linha com o tempo das rodadas

        stringstream ss(line);
        char c = 'M', d = '2';
        ss >> c >> d >> time[0][i];

        getline(cin, line); // Pegue a linha com o tempo final
        stringstream st(line);
        c = 'F', d = '3';
        st >> c >> d >> time[1][i];
    }

    long double rodadas[TESTS], inter[TESTS], total[TESTS];

    for (int i = 0; i < TESTS; ++i) {
        rodadas[i] = time[0][i];
        total[i] = time[1][i];
        inter[i] = time[1][i] - time[0][i];
    }

    cout << fixed << setprecision(9) << avg(rodadas, TESTS) << ' '
         << avg(inter, TESTS) << ' ' << avg(total, TESTS) << endl;

    return 0;
}
