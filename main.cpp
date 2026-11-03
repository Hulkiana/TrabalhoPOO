#include <iostream>
#include "Ecra.h"
#include "Fabrica.h"

using namespace std;

int main() {
    Ecra ecra;

    // Simula a criação da fábrica com dimensões válidas (ex: 10 linhas, 20 colunas)
    Fabrica fabrica(10, 20);

    fabrica.desenhaNaEcra(ecra);
    ecra.mostra();

    cout << "\n--- Teste de informacao de posicao (lposicao) ---" << endl;
    cout << fabrica.obtemInfoPosicao(0, 0) << endl;
    cout << fabrica.obtemInfoPosicao(1, 2) << endl;

    return 0;
}