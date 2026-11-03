
#ifndef TRABALHO_POSICAO_H
#define TRABALHO_POSICAO_H
enum TipoTerreno { VAZIO, CRATERA, DEPOSITO_FERRO, DEPOSITO_SILICIO, DEPOSITO_GELO };

class Posicao {
private:
    TipoTerreno tipo;
    int quantidadeMateriaPrima;

public:
    Posicao();

    TipoTerreno getTipo() const;
    void setTipo(TipoTerreno t);

    int getQuantidade() const;
    void setQuantidade(int qtd);

    char getCaraterVisual() const;
};

#endif //TRABALHO_POSICAO_H
