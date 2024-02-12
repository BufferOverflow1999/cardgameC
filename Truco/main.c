#include"truco.h"
#include<string.h>


void offline_game(){
    int select;
    srand(time(NULL));
    char frases[5][255];
    strcpy(frases[0], "PODE ACEITAR, TALVEZ SEU OPONENTE ESTEJA BLEFANDO");
    strcpy(frases[1], "TALVEZ SEJA BOM GUARDA AS CARTAS MELHORES NO FINAL");
    strcpy(frases[2], "LEMBRESSE NA MAO DE 11 NAO PODE PEDIR TRUCO");
    strcpy(frases[3], "O IMPORTANTE EH SE DIVERTIR A MENOS QUE ESTEJA APOSTANDO SUA CASA");

    printf("\nGAME SELECT\n"
    "[ 1 ] TRUCO\n"
    "[ 2 ] POCKER\n"
    "[%s]:", frases[rand() % 4]);

    scanf("%d", &select);

    switch (select)
    {
    case 1:
        PLAY_TRUCO();
        break;
    default:
        printf("Opcao Invalida");
    break;
    }
}


int _INIT_(){ 
system("cls");  
int option;
    printf(    RED       
"                              __       \n"
"                            .d$$b      \n"
"                          .' TO$;\\     \n"
"                         /  : TP._;    \n"
"                        / _.;  :Tb|    \n"
"                       /   /   ;j$j    \n"
"                   _.-\"       d$$$$    \n"
"                 .' ..       d$$$$;    \n"
"                /  /P'      d$$$$P. |\\ \n"
"               /   \"      .d$$$P' |\\^\"l\n"
"             .'           `T$P^\"\"\"\"\"  :\n"
"         ._.'      _.'                ;\n"
"      `-.-\".-'-' ._.       _.-\"    .-\" \n"
"    `.-\" _____  ._              .-\"    \n"
"   -(.g$$$$$$$b.              .'       \n"
"     ""^^T$$$P^)            .(:        \n"
"       _/  -\"  /.'         /:/;        \n"
"    ._.'-'`-'  \")/         /;/;        \n"
" `-.-\"..--\"\"   \" /         /  ;        \n"
".-\" ..--\"\"        -'          :        \n"
"..--\"\"--.-\"         (\\      .-(\\       \n"
"  ..--""              `-\\(\\/;`         \n"
"    _.                      :          \n"
"                            ;`-        \n"
"                           :\\          \n"
"                           ;       CARD GAME 1.0\n"

RESET

BLUE
"\t[ 1 ] OFFLINE\n"
"\t[ 2 ] ONLINE\n"
RESET
"[ by: Gabriel Tomaz | obs: O lobo nao ]: "
);

scanf("%d", &option);


switch (option)
    {
    case 1:
        offline_game();
        break;
    case 3:
    default:
        break;
    };

}




int main(){
    _INIT_();
  
}