
#ifndef TRABALHO_FABRICA_H
#define TRABALHO_FABRICA_H

#include "Posicao.h"
#include "Ecra.h"
#include "Settings.h"
#include <string>

using namespace std;

class Fabrica {
private:
    int linhas;
    int colunas;
    int creditos;
    int instanteAtual;
    int numMaquinas;
    int numEngenheiros;
    string ultimoInstanteResumo1;
    string ultimoInstanteResumo2;
    Posicao grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

public:
    Fabrica(int nl, int nc);

    void inicializaAleatorio();
    void desenhaNaEcra(Ecra &ecra) const;

    string obtemInfoPosicao(int l, int c) const;

    int getInstante() const;
    int getCreditos() const;
};

#endif //TRABALHO_FABRICA_H
