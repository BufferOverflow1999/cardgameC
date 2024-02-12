/*
by: Gabriel Tomaz

Projeto feito com base na estrutura TRUCO a onde as funções herdam todos os atributos de GAME_T e trabalham com elas
GAME_T [BARALHO ( CARTAS ) - CARTAS - JOGADORES ] 

Para facilitar o trabalho de saber que carta tem prioridade e outras não herdam a posição do baralho [ truco ] onde é estruturado
em ordem o privilégio das cartas, sendo assim, o menor é o maior, as manilhas por sua vez diminuem [ - 41 ] isso é extremamente
importante pois serão as menores de todas e não apenas isso pos o naipe delas também se materam na ordem fazendo assim o [ ♣ ]
se manter em primeiro.




CHECKLIST
[ ] OPÇÕES
[ ] MESA MAIS AMIGAVEL 
[ ] JOGO MACRO 




*/


#include<stdlib.h>
#include <time.h>

#include"baralho.h"

#define PLAYERS2 1
#define PLAYERS4 2

#define TIME1WINS 0
#define TIME2WINS 1

#define TRUCO_PC 1

#define DELETING 41

#define JUMP_TRUCO 1

#define FIRST_GAME 5

#define BACKWHITE "\033[1;107m"

#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define SRED "\033[1;93m"
#define BLUE "\033[1;34m"
#define GREEN "\033[0;32m"
#define RESET "\e[0m"


#define DRAW 5



typedef struct TRUCO {
    int mode;
    struct JOGADOR players[4];
    struct BARALHO truco;


    unsigned vencedor:2;
    struct CARTA manilha;
    struct CARTA mesa[4];

    int truco_point;
    unsigned jump_truco:2;
    char time_point;

    long long int seed;
    int speed;
}GAME_T;


int ACCEPT_COMPUTER(GAME_T *game){
    return 1;
   
}

int ACCEPT_TRUCO(GAME_T *game){
    int option;
    printf("\nACEITAR TRUCO (Y[1]/N[2]):\t");
    scanf("%d", &option);
    if(option == 1 ){
        printf("CONTINUE");
        return TRUCO_PC;
    }
    else{
        return 0;
    }
}

void TRUCO(GAME_T *game){
    switch (game->truco_point + 3)
    {
    case 3:
        printf(GREEN    "\n  /$$$$$$\n" 
                        " /$$__  $$\n"
                        "|__/  \\ $$\n"
                        "   /$$$$$/\n"
                        "  |___  $$\n"
                        " /$$  \\ $$\n"
                        "|  $$$$$$/\n"
                        " \\______/\n" RESET);
        break;
    
    case 6:
        printf(RED  "\n  /$$$$$$\n" 
                    " /$$__  $$\n"
                    "| $$  \\__/\n"
                    "| $$$$$$$\n" 
                    "| $$__  $$\n"
                    "| $$  \\ $$\n"
                    "|  $$$$$$/\n"
                    " \\______/\n" RESET);
        break;
    

    case 9:
        printf( BLUE
                    "\n  /$$$$$$ \n"
                    " /$$__  $$\n"
                    "| $$  \\ $$\n"
                    "|  $$$$$$$\n"
                    " \\____  $$\n"
                    " /$$  \\ $$\n"
                    "|  $$$$$$/\n"
                    " \\______/ \n"
               RESET );
        break;

    case 12:
        printf( SRED
                "\n   /$$    /$$$$$$\n" 
                " /$$$$   /$$__  $$\n"
                "|_  $$  |__/  \\ $$\n"
                "  | $$    /$$$$$$/\n"
                "  | $$   /$$____/ \n"
                "  | $$  | $$      \n"
                " /$$$$$$| $$$$$$$$\n"
                "|______/|________/\n"
                RESET);
        break;
    default:
        break;
    }
}




void ADD_CART_GAME_TRUCO (GAME_T *truco){
    char carts[] = {'3', '2', 'A', 'K', 'J', 'Q', '7', '6', '5', '4'};
    char naipes[] = {5, 3, 6, 4};

    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 4; k++){
            truco->truco.cartas[4 * i + k].simbolo = carts[i];
            truco->truco.cartas[4 * i + k].naipe = naipes[k];
            truco->truco.cartas[4 * i + k].pos = 4 * i + k;

        }
    }

}

void PRINT_CART_GAME_TRUCO(GAME_T *truco){
      for(int i = 0; i < 10; i++){
        for(int k = 0; k < 4; k++){
           printf("%c %c %d\n", truco->truco.cartas[4 * i + k].simbolo, 
            truco->truco.cartas[4 * i + k].naipe,
            truco->truco.cartas[4 * i + k].pos );
        }
        printf("\n");
    }
}

void DELETE_CARDS(struct CARTA *delete){
    delete->pos = 41;
    delete->naipe = '\0';
    delete->simbolo = '\0';
}


void POWER_MANILHA(struct CARTA *manilha){
    manilha->pos = manilha->pos - 41;
}

void DISTRIBUTE_CARTS(GAME_T *game){
    int pos = rand() % 40;
    game->manilha = game->truco.cartas[pos];

    for(int i = 0; i < 2 * game->mode; i++){

        for(int k = 0; k < 3; k++){

        int random = rand() % 40;
        game->players[i].mao[k] = game->truco.cartas[random];

        printf("%c %c P:%d\n", game->players[i].mao[k].naipe, game->players[i].mao[k].simbolo, i);
        while(game->truco.cartas[random].simbolo ==  '\0'){
            random = rand() % 40;
            game->players[i].mao[k] = game->truco.cartas[random];
            

            printf("E %c %c P:%d\n", game->players[i].mao[k].naipe, game->players[i].mao[k].simbolo, i);
        }
            printf("%c %c P:%d\n", game->players[i].mao[k].naipe, game->players[i].mao[k].simbolo, i);
        if(game->players[i].mao[k].simbolo == game->manilha.simbolo){
            POWER_MANILHA(&game->players[i].mao[k]);
        }

        DELETE_CARDS(&game->truco.cartas[random]);

        }

    }

}

int WINS_CART(GAME_T *game){ 
    int player_wins = 0;
    for(int i = 1; i < 2 * game->mode; i++){
            if(game->mesa[ i ].pos < game->mesa[player_wins].pos){
                player_wins = i;
            } 
            else if(game->mesa[player_wins].pos > 0 && game->mesa[player_wins].pos/4 == game->mesa[i].pos/4){
                printf("\n\n\t\tEMPATE\n\n");
                return DRAW;
            }
    }
    printf("\n\n\tO Jogador %d Venceu\n", player_wins);
    
    return player_wins;
}

char FIRST_WIN(int pointx, int pointy, char ponto){
    if(pointx == 0 && pointy == 0){
        return ponto;
    }
}



void CARTS_PLAYER(GAME_T *game){
        printf("\n\nSUAS CARTAS:\n");
    for(int k = 0; k < 3; k++){
        if((((game->players[0].mao[k].pos % 4) + 2 ) % 2) == 0){
            printf(BACKWHITE BLACK "|%c%c|\t" RESET, game->players[0].mao[k].simbolo, game->players[0].mao[k].naipe);
        }
        else{
            printf(BACKWHITE RED "|%c%c|\t" RESET, game->players[0].mao[k].simbolo, game->players[0].mao[k].naipe);
        }
    }
        printf("\n");
   
}


void PLAYER_PLAY(GAME_T *game){
    int option;
    CARTS_PLAYER(game);
    printf("\nSelecione sua Carta [0 , 1 , 2 ] ou TRUCO [ 3 ]\n\n[CARD GAME TRUCO]=>");
    scanf("%d", &option);
    if(option >= 0 && option < 3){
        game->mesa[0] = game->players[0].mao[option];
        DELETE_CARDS(&game->players[0].mao[option]);
    }
    else{
        TRUCO(game);
        if(ACCEPT_COMPUTER(game)){
            game->truco_point += 3;
            CARTS_PLAYER(game);
            printf("\n[ACEITO PELO COMPUTADOR]=>");
            while(!(option <= 2  && option >= 0))
                scanf("%d", &option);
            game->mesa[0] = game->players[0].mao[option];
            DELETE_CARDS(&game->players[0].mao[option]);
        }
        else {
            printf("[RECUSADO]");
            game->jump_truco = JUMP_TRUCO;
            game->time_point = 'X';
        }
    }

}

int TRUCO_RANDOM(GAME_T *game, int random){
    if(random == 1){
        TRUCO(game);
        return TRUCO_PC;
    }
    return 0;
}

int VERIFY_TRUCO(GAME_T *game, int N_computer){
        int sum, random;
        for(int k = 0; k < 3; k++){
            sum += game->players[N_computer].mao[k].pos;
        }

        if(sum < 15){
            random = 2;
        }
        else if(sum < 25){
            random = 4;
        }
        else if(sum < 30){
            random = 5;
        } else {
            random = 10;
        }
        return TRUCO_RANDOM(game, rand() % random);
    }

int COMPUTER_PLAY(GAME_T *game, int N_computer){
    int card = -1;

    for(int i = 0; i < game->mode; i++){
        for(int k = 0; k < 3; k++){
            if(game->players[N_computer].mao[k].pos <= game->mesa[0 + (i * 2)].pos && game->mesa[0 + (i * 2)].pos != DELETING) {
                card = k;
            }
        }
    }

    if(card == -1){
        card = 0;
         for(int k = 1; k < 3; k++){
            if(game->players[N_computer].mao[k].pos >= game->players[N_computer].mao[card].pos && game->players[N_computer].mao[k].pos  != DELETING ){
                card = k;
            }
            else{
                if(game->players[N_computer].mao[k].pos != DELETING){
                    card = k;
                }
            }
        }
    }

    if(N_computer != 2){
        if(VERIFY_TRUCO(game, N_computer)){
            if(!ACCEPT_TRUCO(game)){
                game->jump_truco = JUMP_TRUCO;
                game->time_point = 'Y';
            }
            else {
                game->truco_point += 3;
            }
        }
    }
 
    game->mesa[N_computer] = game->players[N_computer].mao[card];
    DELETE_CARDS(&game->players[N_computer].mao[card]);

}
void LIMPAR_MESA(GAME_T *game){
    for(int i = 0; i < 4; i++){
        game->mesa[i].naipe = '\0';
        game->mesa[i].simbolo = '\0';
        game->mesa[i].pos = DELETING;
    }
}

void MOST_CARTS(GAME_T *game, int positon){

        printf("\n\n\n\t\t");
        if(game->mode == 2){
             for(int i = 0; i < 3; i++){
                if(game->players[positon * 2].mao[i].simbolo != '\0'){
                    printf("%c ", 219);
                }
                else{
                    printf("  "); // TWO SPACES
                }
            }
            printf("\t\t\t");
            for(int i = 0; i < 3; i++){
                if(game->players[ positon * 2 + 1].mao[i].simbolo != '\0'){
                    //printf("%d Position %d", positon, positon * 2 + 1);
                    printf("%c ", 219);
                }
                else{
                    printf("  "); // TWO SPACES
                }
            }
            
        }else{
        printf("\t\t");
        for(int i = 0; i < 3; i++){
                if(game->players[positon].mao[i].simbolo != '\0'){
                    printf("%c ", 219);
                }
                else{
                    printf("  "); // TWO SPACES
                }
            }
        }
        
        printf("\n\n\n\n");
}


void MOST_TABLE(GAME_T *game, int pointX, int pointY){
         //system("cls");
        MOST_CARTS(game, 0);

        printf("\n\n\n\n"
        "\t\t\t| %c  %c |\t\t\t\t\n\t\t",game->manilha.simbolo, game->manilha.naipe);

        for(int  k = 0; k < 2 * game->mode; k++){
            if(game->mesa[k].simbolo != '\0'){
                if(((game->mesa[k].pos % 4) + 2) % 2 == 0){
                    printf(BACKWHITE BLACK "| %c %c |\t" RESET, game->mesa[k].simbolo, game->mesa[k].naipe);
                }
                else{
                    printf(BACKWHITE RED "| %c %c |\t" RESET, game->mesa[k].simbolo, game->mesa[k].naipe);
                }
                }
            else {
                 printf(BACKWHITE RED "|  %d  |\t" RESET, k);
            }
        }
        printf("\n\t\tTIME X %d\t TIME Y: %d\n\n", pointX, pointY);

        MOST_CARTS(game, 1);


    /*   printf(     "                                           █ █ █                                                  \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                             |    |                                                \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                       |       |    |      |    |       |   |        |                            \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                                                                                    \n"
                      "                                           █ █ █                                                  \n") 
                    */

}

void FASE_CARDS(GAME_T *game, int point_x, int point_y, int last_win){
    int jogador; 
    if(last_win == FIRST_GAME){
        jogador = rand() % (2 * game->mode);
    }
    else {
        jogador = last_win;
    }
    
    LIMPAR_MESA(game);

    for(int i = 0; i < 2 * game->mode; i++){
        if(jogador >= 2 * game->mode)
            jogador = 0;
        printf("[ Vez do jogador %d ]", jogador);
        if(jogador ==  0){
            PLAYER_PLAY(game);
        }else {
            COMPUTER_PLAY(game, jogador);
            system("timeout 2 >> null");
        }
        MOST_TABLE(game, point_x, point_y);
        jogador++;
        if(game->jump_truco == JUMP_TRUCO)
            break;

    }

}



 

int TURN_CARTS(GAME_T *game){
    int  point_x = 0, point_y = 0, last_win = FIRST_GAME;
    char first;

    ADD_CART_GAME_TRUCO(game);
    DISTRIBUTE_CARTS(game);
    game->truco_point = 0;

    while(point_x != 2 && point_y != 2){
        FASE_CARDS(game, point_x, point_y, last_win);
        if(game->jump_truco == JUMP_TRUCO){
            break;
        }
        last_win = WINS_CART(game);
        switch(last_win){
            case 0:
            case 2:
            first = FIRST_WIN(point_x, point_y, 'X');
            point_x++;
            break;

            case 1:
            case 3:
            first = FIRST_WIN(point_x, point_y,  'Y');
            point_y++;
            break;

            case DRAW:
            if(point_x == 0 && point_y == 0){
                printf("%d %d", point_x, point_y);
                FASE_CARDS(game, point_x, point_y, last_win);
                return WINS_CART(game);
            }
            if(point_x > 0 || point_y <  0){
                if(first == 'Y'){
                    return TIME2WINS;
                }
                else {
                    return TIME1WINS;
                }
            } 
            break;
        }
    }
    if(point_x == 2){
        return TIME1WINS;
    }
    else{
        return TIME2WINS;
    }
}

void TURN_GAME(GAME_T *game){
    int totalx = 0, totaly = 0, ponto, ganhador;
    while(totalx < 12 && totaly < 12){
        ganhador = TURN_CARTS(game);
        if(game->truco_point == 0){
            ponto = 0;
        }
        else {
            ponto = game->truco_point;
        }
        if(ganhador == TIME1WINS){
            totalx += ponto;
        }
        else {
            totaly += ponto;
        }
        printf("\n\n\n\n\t%d\t\t%d\n\n\n\n", totalx, totaly);
    }
}


void NUMBER_BOTS(GAME_T *game){
    int option = 0;
    while(option != 1 && option != 2){
    printf("\nOPTIONS\n"
    "[ 1 ] DOIS JOGADORES\n"
    "[ 2 ] QUATRO JOGADORES\n"
    "[ 3 ] EXIT\n"
    "[CARD GAME]: ");

    scanf("%d", &option);

    switch (option)
    {
    case 1:
        game->mode = 1;
        break;
    case 2:
        game->mode = 2;
        break;
    default:
        printf("INVALIDO !!\n");
        break;
        }
    }
}

void MANUAL_SEED(GAME_T *game){
    long long int seed;
    printf(
        "\nOPTIONS\n"
        "SEED ATUAL %ld\n"
        "DIGITE A NOVA SEED:\t",
        game->seed
    );
    scanf("%lld", &seed);
    game->seed = seed;
}

void SPEED_GAME(GAME_T *game){
    int speed;
    printf("OPTION\n"
    "SPEED ATUAL %d\n"
    "DIGITE EM MILISEGUNDOS O TEMPO DE JOGO:\t",
    game->speed);

    scanf("%d", &speed);
    game->speed = speed;
}

void TRUCO_MAN(GAME_T *GAME_T){

}

void OPTIONS(GAME_T *game){
    int option = 0;
    FILE *cfptr;
     if(!((cfptr = fopen("Config.cf", "r+")) == NULL)){
    while(option != 999){
        printf("\n"
        GREEN
    "  /$$$$$$  /$$$$$$$  /$$$$$$$$/$$$$$$  /$$$$$$  /$$   /$$  /$$$$$$ \n"
    " /$$__  $$| $$__  $$|__  $$__/_  $$_/ /$$__  $$| $$$ | $$ /$$__  $$\n"
    "| $$  \\ $$| $$  \\ $$   | $$    | $$  | $$  \\ $$| $$$$| $$| $$  \\__/\n"
    "| $$  | $$| $$$$$$$/   | $$    | $$  | $$  | $$| $$ $$ $$|  $$$$$$ \n"
    "| $$  | $$| $$____/    | $$    | $$  | $$  | $$| $$  $$$$ \\____  $$\n"
    "| $$  | $$| $$         | $$    | $$  | $$  | $$| $$\\  $$$ /$$  \\ $$\n"
    "|  $$$$$$/| $$         | $$   /$$$$$$|  $$$$$$/| $$ \\  $$|  $$$$$$/\n"
    " \\______/ |__/         |__/  |______/ \\______/ |__/  \\__/ \\______/ \n"
        RESET
    "[ 1 ] NUMBER BOTS\t" "[ 2 ] MANUAL SEED\t\t" "[ 3 ] SPEED GAME\n"
    "[ 4 ] TRUCO MAN\t\t[ 5 ] SALVAR MODIFICACOES\t[ 9 ] EXIT\n"
    "[SELECT]:");

    scanf("%d", &option);

    switch (option)
    {
        case 1:
            NUMBER_BOTS(game);
            break;
        case 2:
            MANUAL_SEED(game);
            break;
        case 3:
            SPEED_GAME(game);
            break;
        case 4:
            TRUCO_MAN(game);
            break;
        case 5:
             fwrite(game, sizeof(GAME_T), 1, cfptr);
             break;
        case 999:
            break;
        default:
            printf("INVALIDO!\n");
            break;
        }
    }
}

}

void MENU(GAME_T *game){
    int option;
    printf(
    RED
    "  @@@@@@@      @@@@@@@       @@@  @@@       @@@@@@@       @@@@@@ \n"
    "   @@!        @@!  @@@      @@!  @@@      !@@           @@!  @@@\n"
    "   @!!        @!@!!@!       @!@  !@!      !@!           @!@  !@!\n"
    "   !!:        !!: :!!       !!:  !!!      :!!           !!:  !!!\n"
    "    :          :   : :       :.:: :        :: :: :       : :. : \n"
    RESET
    "[ 1 ] START\n"
    "[ 2 ] OPTIONS\n"
    );

    scanf("%d", &option);

    switch (option)
    {
        case 1:
            break;
        case 2:
            OPTIONS(game);
        default:
            break;
    }

}

void APRESENTACAO(GAME_T *game){
    FILE *cfptr;
    if((cfptr = fopen("Config.cf", "r")) == NULL){
        printf("\n\nHELLO HELLO MORADORES DE TORRES TORTAS\n"
        "BEM-VINDO AO BRAZINNO 7777 O NOME MAIS ORIGINAL DO MUNDO\n"
        "MAS NAO ESTAMOS AQUI PARA FALAR SOBRE NOS, FALE SOBRE VOCE:\n"
        "QUAL EH O SEU NOME ?\n"
        "[NOME:\t");
        scanf("%s", game->players[0].name);

        printf("HMM, %s QUE NOME ESTRANHO MAS ELE MAL VAI APARECER NO JOGO MESMO HAHAHAHA\n"
        "RECOMENDAMOS VERIFICAR AS CONFIGURACOES, TALVEZ A ALGO QUE QUEIRA MUDAR\n\n", game->players[0].name);
        if( !((cfptr = fopen("Config.cf", "w")) == NULL)){
             fwrite(game, sizeof(GAME_T), 1, cfptr);
        }
    }
    else {
        printf("CARREGANDO JOGO SALVO...\n");
        fread(game, sizeof(GAME_T), 1, cfptr);
    }
    fclose(cfptr);
}




void PLAY_TRUCO(){ 
    system("TITLE BRAZINO 7777");
    GAME_T *truco;
    truco = (GAME_T *)malloc(sizeof(GAME_T));
    truco->jump_truco = 0;
    truco->mode = 1;
    truco->seed = (unsigned )time(NULL);
    truco->truco_point = 0;
    APRESENTACAO(truco);
    MENU(truco);
    srand(truco->seed);




    ADD_CART_GAME_TRUCO(truco);
    PRINT_CART_GAME_TRUCO(truco);


    TURN_GAME(truco);
    
  

}