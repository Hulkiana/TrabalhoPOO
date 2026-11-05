#include "Fabrica.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

Fabrica::Fabrica(int nl, int nc) {
    linhas = (nl < 1) ? 1 : (nl > Settings::fabrica_max_linhas ? Settings::fabrica_max_linhas : nl);
    colunas = (nc < 1) ? 1 : (nc > Settings::fabrica_max_colunas ? Settings::fabrica_max_colunas : nc);

    // Inicialização dinâmica baseada estritamente nas regras e em Settings
    creditos = Settings::fabrica_creditos_iniciais;
    instanteAtual = 0;
    numMaquinas = 0;
    numEngenheiros = 0;
    ultimoInstanteResumo1 = "inicio da simulacao";
    ultimoInstanteResumo2 = "";

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            grelha[i][j].setTipo(VAZIO);
        }
    }

    inicializaAleatorio();
}

void Fabrica::inicializaAleatorio() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Colocar Crateras aleatoriamente de acordo com Settings
    int colocadasCrateras = 0;
    while (colocadasCrateras < Settings::fabrica_num_crateras) {
        int l = rand() % linhas;
        int c = rand() % colunas;
        if (grelha[l][c].getTipo() == VAZIO) {
            grelha[l][c].setTipo(CRATERA);
            colocadasCrateras++;
        }
    }

    // Colocar Depósitos de Ferro aleatoriamente de acordo com Settings
    int depFerro = 0;
    while (depFerro < Settings::fabrica_num_depositos_ferro) {
        int l = rand() % linhas;
        int c = rand() % colunas;
        if (grelha[l][c].getTipo() == VAZIO) {
            grelha[l][c].setTipo(DEPOSITO_FERRO);
            int qtd = Settings::deposito_quantidade_min + (rand() % (Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1));
            grelha[l][c].setQuantidade(qtd);
            depFerro++;
        }
    }

    // Colocar Depósitos de Silício aleatoriamente de acordo com Settings
    int depSilicio = 0;
    while (depSilicio < Settings::fabrica_num_depositos_silicio) {
        int l = rand() % linhas;
        int c = rand() % colunas;
        if (grelha[l][c].getTipo() == VAZIO) {
            grelha[l][c].setTipo(DEPOSITO_SILICIO);
            int qtd = Settings::deposito_quantidade_min + (rand() % (Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1));
            grelha[l][c].setQuantidade(qtd);
            depSilicio++;
        }
    }

    // Colocar Depósitos de Gelo aleatoriamente de acordo com Settings
    int depGelo = 0;
    while (depGelo < Settings::fabrica_num_depositos_gelo) {
        int l = rand() % linhas;
        int c = rand() % colunas;
        if (grelha[l][c].getTipo() == VAZIO) {
            grelha[l][c].setTipo(DEPOSITO_GELO);
            int qtd = Settings::deposito_quantidade_min + (rand() % (Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1));
            grelha[l][c].setQuantidade(qtd);
            depGelo++;
        }
    }
}

void Fabrica::desenhaNaEcra(Ecra &ecra) const {
    ecra.limpa();

    int alturaMoldura = linhas + 3;
    int larguraFabrica = colunas + 5; // Aumentado para acomodar perfeitamente a régua e o limite direito
    ecra.desenhaMoldura(0, 0, alturaMoldura, larguraFabrica);

    // Régua horizontal superior (A, B, C...) alinhada exatamente com as colunas da grelha (começa na coluna 3)
    ecra.posiciona(1, 3);
    for (int j = 0; j < colunas; j++) {
        char letraCol = 'A' + j;
        ecra.escreve(letraCol);
    }
    // Fechar a moldura superior corretamente após a régua
    ecra.posiciona(1, larguraFabrica - 1);
    ecra.escreve('|');

    // Régua vertical lateral (A, B, C...) e conteúdo da grelha
    for (int i = 0; i < linhas; i++) {
        ecra.posiciona(2 + i, 1);
        char letraLinha = 'A' + i;
        ecra.escreve(letraLinha);

        for (int j = 0; j < colunas; j++) {
            ecra.posiciona(2 + i, 3 + j);
            ecra.escreve(grelha[i][j].getCaraterVisual());
        }
    }

    // Painel de Estado à direita sem sobreposições
    int inicioPainelCol = larguraFabrica + 2;
    int larguraPainel = 34;
    ecra.desenhaMoldura(0, inicioPainelCol, alturaMoldura, larguraPainel);

    ecra.posiciona(1, inicioPainelCol + 2);
    ecra.escreve("Instante: " + to_string(instanteAtual));

    ecra.posiciona(2, inicioPainelCol + 2);
    ecra.escreve("Creditos: " + to_string(creditos));

    ecra.posiciona(3, inicioPainelCol + 2);
    ecra.escreve("Maquinas: " + to_string(numMaquinas));

    ecra.posiciona(4, inicioPainelCol + 2);
    ecra.escreve("Engenheiros: " + to_string(numEngenheiros));

    ecra.posiciona(6, inicioPainelCol + 2);
    ecra.escreve("No ultimo instante:");

    ecra.posiciona(7, inicioPainelCol + 2);
    ecra.escreve(ultimoInstanteResumo1);

    if (!ultimoInstanteResumo2.empty()) {
        ecra.posiciona(8, inicioPainelCol + 2);
        ecra.escreve(ultimoInstanteResumo2);
    }
}

string Fabrica::obtemInfoPosicao(int lStart, int cStart, int raio) const {
    stringstream ss;

    // Percorre o quadrado de raio centralizado em (lStart, cStart)
    for (int l = lStart - raio; l <= lStart + raio; ++l) {
        for (int c = cStart - raio; c <= cStart + raio; ++c) {
            if (l >= 0 && l < linhas && c >= 0 && c < colunas) {
                const Posicao &pos = grelha[l][c];
                char letraL = 'A' + l;
                char letraC = 'A' + c;

                ss << "Posicao " << letraL << letraC << ": ";

                switch (pos.getTipo()) {
                    case VAZIO: ss << "solo"; break;
                    case CRATERA: ss << "cratera"; break;
                    case DEPOSITO_FERRO: ss << "deposito de ferro (" << pos.getQuantidade() << " unidades)"; break;
                    case DEPOSITO_SILICIO: ss << "deposito de silicio (" << pos.getQuantidade() << " unidades)"; break;
                    case DEPOSITO_GELO: ss << "deposito de gelo (" << pos.getQuantidade() << " unidades)"; break;
                }
                ss << "\n";
            }
        }
    }
    return ss.str();
}

int Fabrica::getInstante() const { return instanteAtual; }
int Fabrica::getCreditos() const { return creditos; }