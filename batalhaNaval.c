#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5      
#define NAVIOS 3       

void inicializaTabuleiro(int tab[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tab[i][j] = -1; 
        }
    }
}

void mostraTabuleiro(int tab[TAMANHO][TAMANHO]) {
    printf("\n   ");
    for (int c = 0; c < TAMANHO; c++)
        printf("%d ", c + 1);
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < TAMANHO; j++) {
            if (tab[i][j] == -1) printf("~ "); 
            else if (tab[i][j] == 0) printf("* ");  
            else printf("X ");  
        }
        printf("\n");
    }
}


void iniciaNavios(int nav[NAVIOS][2]) {
    srand(time(NULL));
    for (int n = 0; n < NAVIOS; n++) {
        int l, c;
        int repetido;
        do {
            repetido = 0;
            l = rand() % TAMANHO;
            c = rand() % TAMANHO;
            for (int k = 0; k < n; k++) {
                if (nav[k][0] == l && nav[k][1] == c) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);
        nav[n][0] = l;
        nav[n][1] = c;
    }
}

int acertou(int tiroL, int tiroC, int nav[NAVIOS][2]) {
    for (int n = 0; n < NAVIOS; n++) {
        if (nav[n][0] == tiroL && nav[n][1] == tiroC)
            return 1;
    }
    return 0;
}

void dica(int tiroL, int tiroC, int nav[NAVIOS][2]) {
    int contaL = 0, contaC = 0;
    for (int n = 0; n < NAVIOS; n++) {
        if (nav[n][0] == tiroL) contaL++;
        if (nav[n][1] == tiroC) contaC++;
    }
    printf("Dica: navios na mesma linha: %d, na mesma coluna: %d\n", contaL, contaC);
}

int main() {
    int tab[TAMANHO][TAMANHO];
    int nav[NAVIOS][2];
    int tiros = 0, acertos = 0;
    int linha, coluna;

    inicializaTabuleiro(tab);
    iniciaNavios(nav);

    printf("Jogo Batalha Naval - você precisa achar %d navios escondidos!\n", NAVIOS);

    while (acertos < NAVIOS) {
        mostraTabuleiro(tab);
        printf("Digite a linha e coluna (1 a %d): ", TAMANHO);
        scanf("%d %d", &linha, &coluna);
        linha--; coluna--;
        tiros++;

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
            printf("Tente novamente.\n");
            continue;
        }
        if (tab[linha][coluna] != -1) {
            printf("Você já atirou aí.\n");
            continue;
        }

        if (acertou(linha, coluna, nav)) {
            printf("Você afundou um navio!\n");
            tab[linha][coluna] = 1;
            acertos++;
        } else {
            printf("Água...\n");
            tab[linha][coluna] = 0;
            dica(linha, coluna, nav);
        }
    }

    printf("\nParabéns, Você afundou todos os navios em %d tiros.\n", tiros);
    mostraTabuleiro(tab);
    return 0;
}
