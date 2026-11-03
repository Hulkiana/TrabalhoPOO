#include "Ecra.h"
#include <iostream>

using namespace std;

Ecra::Ecra() : cursorLinha(0), cursorColuna(0) {
    limpa();
}

void Ecra::limpa() {
    for (int i = 0; i < Settings::ecra_max_linhas; ++i) {
        for (int j = 0; j < Settings::ecra_max_colunas; ++j) {
            buffer[i][j] = ' ';
        }
    }
}

void Ecra::posiciona(int linha, int coluna) {
    if (linha >= 0 && linha < Settings::ecra_max_linhas) {
        cursorLinha = linha;
    }
    if (coluna >= 0 && coluna < Settings::ecra_max_colunas) {
        cursorColuna = coluna;
    }
}

void Ecra::escreve(char c) {
    if (cursorLinha >= 0 && cursorLinha < Settings::ecra_max_linhas &&
        cursorColuna >= 0 && cursorColuna < Settings::ecra_max_colunas) {
        if (c == '\n') {
            cursorColuna = 0;
            cursorLinha++;
        } else {
            buffer[cursorLinha][cursorColuna] = c;
            cursorColuna++;
            if (cursorColuna >= Settings::ecra_max_colunas) {
                cursorColuna = 0;
                cursorLinha++;
            }
        }
    }
}

void Ecra::escreve(int linha, int coluna, char c) {
    if (linha >= 0 && linha < Settings::ecra_max_linhas &&
        coluna >= 0 && coluna < Settings::ecra_max_colunas) {
        buffer[linha][coluna] = c;
    }
}

void Ecra::escreve(const string &s) {
    for (char c : s) {
        escreve(c);
    }
}

void Ecra::escreve(int linha, int coluna, const string &s) {
    posiciona(linha, coluna);
    escreve(s);
}

void Ecra::desenhaMoldura(int linha, int coluna, int altura, int largura) {
    if (altura <= 0 || largura <= 0) return;

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            int l = linha + i;
            int c = coluna + j;

            if (l >= 0 && l < Settings::ecra_max_linhas &&
                c >= 0 && c < Settings::ecra_max_colunas) {
                if (i == 0 || i == altura - 1) {
                    if (j == 0 || j == largura - 1) {
                        buffer[l][c] = '+';
                    } else {
                        buffer[l][c] = '-';
                    }
                } else if (j == 0 || j == largura - 1) {
                    buffer[l][c] = '|';
                }
            }
        }
    }
}

void Ecra::mostra() const {
    // Descobre dinamicamente a última linha preenchida para evitar imprimir as 40 linhas completas em branco
    int ultimaLinhaUtilizada = 0;
    for (int i = 0; i < Settings::ecra_max_linhas; ++i) {
        for (int j = 0; j < Settings::ecra_max_colunas; ++j) {
            if (buffer[i][j] != ' ') {
                ultimaLinhaUtilizada = i;
            }
        }
    }

    int linhasParaImprimir = ultimaLinhaUtilizada + 2;
    if (linhasParaImprimir > Settings::ecra_max_linhas) {
        linhasParaImprimir = Settings::ecra_max_linhas;
    }

    for (int i = 0; i < linhasParaImprimir; ++i) {
        for (int j = 0; j < Settings::ecra_max_colunas; ++j) {
            cout << buffer[i][j];
        }
        cout << '\n';
    }
}