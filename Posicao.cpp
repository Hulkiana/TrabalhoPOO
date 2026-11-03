#include "Posicao.h"

Posicao::Posicao() {
    tipo = VAZIO;
    quantidadeMateriaPrima = 0;
}

TipoTerreno Posicao::getTipo() const {
    return tipo;
}

void Posicao::setTipo(TipoTerreno t) {
    tipo = t;
}

int Posicao::getQuantidade() const {
    return quantidadeMateriaPrima;
}

void Posicao::setQuantidade(int qtd) {
    quantidadeMateriaPrima = qtd;
}

char Posicao::getCaraterVisual() const {
    switch (tipo) {
        case VAZIO: return ' ';
        case CRATERA: return '#';
        case DEPOSITO_FERRO: return '%';
        case DEPOSITO_SILICIO: return '$';
        case DEPOSITO_GELO: return '~';
    }
    return ' ';
}