#include<stdio.h>

struct CARTA {
    char simbolo;
    char naipe;
    int pos;
};

struct BARALHO {
    struct CARTA cartas[52];
};

struct JOGADOR {
    char name[255];
    struct CARTA mao[3];
    int Point;  
};

