#ifndef TRABALHO_ECRA_H
#define TRABALHO_ECRA_H
#include <string>

#include <string>
#include "Settings.h"

using namespace std;

#include <string>
#include "Settings.h"

using namespace std;

class Ecra {
private:
    char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas];
    int cursorLinha;
    int cursorColuna;

public:
    Ecra();
    void limpa();
    void posiciona(int linha, int coluna);
    void escreve(char c);
    void escreve(int linha, int coluna, char c);
    void escreve(const string &s);
    void escreve(int linha, int coluna, const string &s);
    void desenhaMoldura(int linha, int coluna, int altura, int largura);
    void mostra() const;
};

#endif //TRABALHO_ECRA_H
