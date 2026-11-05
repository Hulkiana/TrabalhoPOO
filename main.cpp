#include <iostream>
#include <string>
#include "Ecra.h"
#include "Fabrica.h"

using namespace std;

int main() {
    Ecra ecra;

    cout << "Criar fabrica:\n";
    cout << "  1 - De forma Aleatoria\n";
    cout << "  2 - Pelo ficheiro\n";
    cout << "Escolha uma opcao (1 ou 2): ";
    int opcao;
    cin >> opcao;

    Fabrica fabrica(10, 10);
    fabrica.desenhaNaEcra(ecra);
    ecra.mostra();

    string input;
    while (true) {
        cout << "\nPosicao (escreve, por exemplo: aa ou aa 3) ou fim: ";
        cin >> input;
        if (input == "fim") break;

        char linhaChar = input[0];
        char colChar = input[1];

        int l = toupper(linhaChar) - 'A';
        int c = toupper(colChar) - 'A';

        int raio = 0;
        if (cin.peek() != '\n' && cin.peek() != EOF) {
            cin >> raio;
        }

        cout << "\n" << fabrica.obtemInfoPosicao(l, c, raio);
    }

    return 0;
}