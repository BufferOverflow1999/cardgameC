#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


#define RED "\033[1;31m"
#define SRED "\033[1;93m"
#define BLUE "\033[1;34m"
#define GREEN "\033[0;32m"
#define RESET "\e[0m"

#define DRAW 2
#define WINS_COMPUTER 1
#define WINS_PLAYER 0

//STATUS
#define DRAW_GAME 'D'
#define FINISH 'F'
#define CONTINUE 'C'


enum nipe {
    trevo,
    coracao, 
    valete,
    ouro
};


typedef struct CARTA {
    char valor;
    char naipe;
    int pos;
}CARTA;



typedef struct GAME {
    int player;
    int computer;


    unsigned last_win:2;
    char status;
    
    char manilha;
    int manilha_pos;

    int pontos; //Pontos ganho por jogador

    int vitoriaPlayer;
    int vitoriaComputer;
}GAME;
/*CARTAS*/


void TRUCO_WALPAPER(int valor ){
    switch (valor)
    {
    case 3:
        printf(GREEN    "  /$$$$$$\n" 
                        " /$$__  $$\n"
                        "|__/  \\ $$\n"
                        "   /$$$$$/\n"
                        "  |___  $$\n"
                        " /$$  \\ $$\n"
                        "|  $$$$$$/\n"
                        " \\______/\n" RESET);
        break;
    
    case 6:
        printf(RED  "  /$$$$$$\n" 
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
                    "  /$$$$$$ \n"
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
                "   /$$    /$$$$$$\n" 
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

void add_carts_and_nipes(CARTA truco[]){
    char carts[] = {'3', '2', 'A', 'K', 'J', 'Q', '7', '6', '5', '4'};
    char naipes[] = {'\5', '\3', '\6', '\4'};

    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 4; k++){
            truco[4 * i + k].valor = carts[i];
            truco[4 * i + k].naipe = naipes[k];
            truco[4 * i + k].pos = (4 * i + k) + 1; //nunca tenha uma posição de 0
        }
    }

}

void print_carts(CARTA truco[]){
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 4; k++){
            printf("%c%c",
            truco[4 * i + k].valor, truco[4 * i + k].naipe);
        }
        printf("\n");
    }
}



void distribute_carts(CARTA game[], CARTA player[], CARTA computer[], GAME *ingame){
    for(int i = 0; i < 3; i++){
        player[i] = game[rand() % 40];
        computer[i] = game[rand() % 40];
    }
    int pos = rand() % 40;
    ingame->manilha = game[pos].valor;
    ingame->manilha_pos =  ( game[pos].pos ) / 4;
}

void print_carts_player(CARTA player[]){
    for(int i = 0; i < 3; i++){
        printf("\t%c %c\t", player[i].valor, player[i].naipe);
    }
}


void show_in_table(char player, char player_n, char computer, char computer_n, GAME *ingame){
    printf("\n\n\t\tM: %c\n\n"
    "\t\t" BLUE  "%c %c" RESET "\t" RED "%c %c" RESET 
    "\n\n\n"
    "Player points: %d\t\tComputer points: %d",ingame->manilha, player, player_n, computer, computer_n, ingame->player, ingame->computer);
}

int card_wins(int player, int computer, GAME *ingame){
    //VERIFICAÇÃO DE EMPATE
    if(player/4 == computer/4){
        printf("\n------%d %d-----\n", player/4, computer/4);
        return DRAW;
    }
    else {
        if(player/4 == ingame->manilha_pos){
            return  WINS_PLAYER;
        }
        else if(computer/4 == ingame->manilha_pos){
            return WINS_COMPUTER;
        }
        else if(computer > player){
            return WINS_PLAYER;
        } else {
            return WINS_COMPUTER;
        }
    }
}

void delete_cart(CARTA jogador[], int option){
    jogador[option].valor = ' ';
    jogador[option].naipe = ' ';
    jogador[option].pos = 400;
}

int Pc_Truco(CARTA computer[]){
    int k;
    for(k = 0; k < 3; k++){
        if(computer[k].valor  > 15){
            break;
        }
    }
    //90%
    if(k == 3){
       if(rand() % 10 > 0){
         return 1;
       }
    }

    for(k = 0; k < 3; k++){
        if(computer[k].valor  > 25){
            break;
        }
    }
    //50%
    if(k == 3){
       if(rand() % 10 > 4){
         return 1;
     }
    }
    

    for(k = 0; k < 3; k++){
        if(computer[k].valor  > 30){
            break;
        }
    } 
    //10%
    if(k == 3){
       if(rand() % 10 == 0){
         return 1;
        }
    }

    return 0;
}

int Pc_comparative(CARTA player[], CARTA computer[], int position){
    int beast = 0;
    for(int k = 0; k < 3; k++){
        if ( player[position].pos > computer[k].pos ){
            beast = k;
        }
    }

    if(beast == 0){
        beast = 40;
        for(int k = 0; k < 3; k++){
            if(computer[k].pos < beast){
                beast = k;
            }
        }
    }

    return beast;
}

int Pc_game(CARTA computer[]){
        int beast = 40;
        for(int k = 0; k < 3; k++){
            if(computer[k].pos < beast){
                beast = k;
            }
        }
}

int  computer_start(CARTA jogador[], CARTA computer[], GAME * ingame){
    int position_pc = Pc_game(computer);
    int option;

    show_in_table(' ', ' ', computer[position_pc].valor, computer[position_pc].naipe, ingame);

    print_carts_player(jogador);
    
    printf("\nSelecione sua Carta: ");

    do{
        scanf("%d", &option);
        if(jogador[option].valor != ' ' && option < 3 && option >= 0){
            printf("|%c|", jogador[option].valor);
            break;
        }
        printf("OPCAO INVALIDA (0 , 1 , 2)");

    }while(1);


    show_in_table(jogador[option].valor, jogador[option].naipe, computer[position_pc].valor, computer[position_pc].naipe, ingame);

     switch(card_wins(jogador[option].pos, computer[position_pc].pos, ingame))
    {
        
        case DRAW:

            if(ingame->status == DRAW){
            if(computer[position_pc].pos > jogador[option].pos){
                    ingame->player += ingame->pontos;
                    return 0;
                } else {
                    ingame->computer += ingame->pontos;
                    return 0;
                    }
            }        
            ingame->status = DRAW;
            delete_cart(computer, position_pc);
            delete_cart(jogador, option);
        break;
        case WINS_PLAYER:
                ingame->vitoriaPlayer += 1;
                delete_cart(computer, position_pc);
                delete_cart(jogador, option);
                return 0;
            break;
        
        case WINS_COMPUTER:
            ingame->vitoriaComputer += 1;
            delete_cart(computer, position_pc);
            delete_cart(jogador, option);
            return 0;
            break;

    }

}


int player_start(CARTA jogador[], CARTA computer[], GAME *ingame) {
    if(ingame->vitoriaComputer == 2){
        ingame->computer += ingame->pontos;
        ingame->status = FINISH;

    }
    else if( ingame->vitoriaPlayer == 2){
        ingame->player += ingame->pontos;
        ingame->status = FINISH;
    }
    else{ 

    int option = 0;
    int position_pc;
    print_carts_player(jogador);
    
    printf("\nSelecione sua Carta: ");

    do{
        scanf("%d", &option);
        if(jogador[option].valor != ' ' && option < 3 && option >= 0){
            printf("|%c|", jogador[option].valor);
            break;
        }
        printf("OPCAO INVALIDA (0 , 1 , 2)");

    }while(1);

    show_in_table(jogador[option].valor, jogador[option].naipe, ' ', ' ', ingame);

    //Computer_START |  |  |  |
    position_pc = Pc_comparative(jogador, computer, option);

    show_in_table(jogador[option].valor, jogador[option].naipe, computer[position_pc].valor, computer[position_pc].naipe, ingame);


    switch(card_wins(jogador[option].pos, computer[position_pc].pos, ingame))
    {
        
        case DRAW:

            if(ingame->status == DRAW){
            if(computer[position_pc].pos > jogador[option].pos){
                    ingame->player += ingame->pontos;
                    return 0;
                } else {
                    ingame->computer += ingame->pontos;
                    return 0;
                    }
            }        
            ingame->status = DRAW;
            delete_cart(computer, position_pc);
            delete_cart(jogador, option);
            player_start(jogador, computer, ingame);
        break;
        case WINS_PLAYER:
                ingame->vitoriaPlayer += 1;
                ingame->last_win = 1;
                delete_cart(computer, position_pc);
                delete_cart(jogador, option);
                return 0;
            break;
        
        case WINS_COMPUTER:
            ingame->last_win = 0;
            ingame->vitoriaComputer += 1;
            delete_cart(computer, position_pc);
            delete_cart(jogador, option);
            return 0;
            break;

    }

    
    

    }

}


void start(CARTA jogador[], CARTA computer[], CARTA Baralho[]){
    /*Ingame é o partidade 3 cartas para cada jogador até finalizar as cartas
    Game é no geral que vai até 12 pontos*/
    GAME *ingame;

    ingame = malloc(sizeof(GAME));
    ingame->computer = 0;
    ingame->player = 0;
    ingame->status = CONTINUE;
    ingame->vitoriaComputer = 0;
    ingame->vitoriaPlayer = 0;


    system("cls");
    printf("\e[34m" "\n\t\tTRUCO GAME 9.0" "\e[0m" "\n");
    ingame->last_win = rand() % 2;
    
    //CARTAS
    distribute_carts(Baralho, jogador, computer, ingame);
    ingame->pontos = 1;

    //RODADA 
    //3 VEZES NO MAXÍMO 2 NO MÍNIMO
    while(ingame->status != FINISH){
    if(ingame->last_win == 1){
            player_start(jogador, computer, ingame);
        }   
        else {
            computer_start(jogador, computer, ingame);
        }
    }

    show_in_table('K', '\4', 'J', '\6', ingame);
    
}


int main(){ 
    
    CARTA truco[40];
    CARTA jogador[3];
    CARTA Computador[3];

    add_carts_and_nipes(truco);
    //#     print_carts(truco);
   
    start(jogador, Computador, truco);
    print_carts_player(Computador);


    

    return 0;

}