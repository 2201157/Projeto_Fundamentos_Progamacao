#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#define MAX_ESC 5
#define MAX_QUES 1000
#define MAX_QUES_ESC 200



struct Escolas {

    int id;
    char nome[50];
    char localidade[50];

};


struct Questionarios {

    int id;
    int escola;
    char data[20];
    char risco[20];
    int idade;
    char genero[20];
    char residencia[50];
    char concelho[50];
    char tipo[20];
    char contato[20];
    int sintomas[8];
    int doencas[8];
    float temperatura;

};

int getInt(char msg[],int min,int max); // Funcao para ler inteiro//

float getFloat(char msg[],int min, int max); //Funcao para ler float//

char getChar(char msg[]);//Funcao para ler Char//

void ler_string (char texto[], char str[], int max); //Funcao para ler string //

void clear_screen(); //Funcao para limpar ecra, baseado no sistema operativo//

void Menu(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]); // Funcao do menu principal//

void Menu_Escolas(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]); // Funcao do Menu escolas//

void Menu_Questionarios(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]);//Funcao do Menu questionario//

void Menu_Estatisticas(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]); // Funcao do Menu estatisticas//

int Registrar_Escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]); // Funcao para registar escola//

void Adicionar_Escola(struct Escolas escolas[], int id, char nome[], char localidade[], int conta_esc_ques[]); //Funcao para adicionar escola � struct das escolas//

int gera_id_escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]) ;// Funcao para gerar um id para a escola //

int verifica_nome_escola(struct Escolas escolas[], char nome[], int conta_esc_ques[]); // Verifica se o nome da escola introduzido j� existe//

int Consultar_Escolas(struct Escolas escolas[], int conta_esc_ques[]);//Funcao para consultar escolas//

void Iniciar_Ficheiros();//Funcao para inicalizar ficheiros//

FILE * openFile(char name_file[], char mode[]);//Funcao para manipular ficheiros, onde o "name_file" � o nome do ficheiro que vai ser manipulado, e o "mode" o modo para manipular: ler, escrever, etc//

void Gravar_Escolas(struct Escolas escolas[], int conta_esc_ques[]);// funcao para gravar no ficheiro das escolas//

void loadEscolas(struct Escolas escolas[], int conta_esc_ques[]);//Funcao para ler escolas do ficheiro//

int Registrar_Questionario(struct Questionarios questionarios[], struct Escolas escolas[], int conta_esc_ques[]); //Funcao para registar questionarios//

int atribuir_Escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[],int id);//Funcao para perguntar escola//

int verifica_escolas(struct Escolas escolas[], struct Questionarios questionarios[],int conta_esc_ques[]); // Funcao para verificar se existe escolas criadas, se sim, avan�a com o registro, se n�o ele volta para o menu questionario//

int gera_id_questionario(struct Questionarios questionarios[], struct Escolas escolas[], int conta_esc_ques[]); // Funcao que cria um id para o questionario //

int verifica_contador_escola(struct Questionarios questionarios[], int conta_esc_ques[],int id); // Funcao que verifica o contador de x escola j� chegou ao limite//

void atribuir_Data(char data[]);// Funcao que pergunta a data//

void atribuir_Genero(char genero[]); // Funcao para perguntar genero//

void atribuir_Tipo(char tipo []);//funcao para perguntar o tipo de participante//

void atribuir_Contato(char contacto[]);// funcao para perguntar o contacto//

void atribuir_Sintomas(int sintomas[]); //Funcao para perguntar sintomas//

int verifica_Sintoma( int sintomas[], int tamanho, int resposta);// Funcao para verificar sintomas//

void imprime_Sintoma(int sintomas[]);//Funcao para imprimir os sintomas nas respetivas strings//

void atribuir_Doenca(int doencas[]);// Funcao para perguntar doencas//

int verifica_Doencas( int doencas[], int tamanho, int resposta); // Funcao para verificar se existe doencas repetidas//

void imprime_Doenca(int doencas[]);//Funcao para imprimir as doencas nas respetivas strings//

void contagio(char contato[], int sintomas[], int doencas[], float temperatura,char risco []);//Funcao para determinar o nivel de contagio//

int conta_sintomas_doencas(int array[],int max);//Funcao que devolve quantos sintomas ou doen�as foram registados//

void Adicionar_Questionario(struct Questionarios questionarios[], int id, int escola, char data[], char risco[], int idade, char genero[], char residencia[], char tipo[], char contato[], int sintomas[], int doencas[], float temperatura, int conta_esc_ques[],char concelho[]);// Funcao que adiciona todo o conteudo pedido ao utilizador na struct questionarios//

void adicionar_sintomas_doencas_na_Struct(int array[],struct Questionarios questionarios[],int max,int indice,int valida); // Funcao para passar os sintomas ou doencas registados para a struct questionarios//

void Gravar_Questionarios(struct Questionarios questionarios[], int conta_esc_ques[]);//Funcao que grava questionarios no ficheiro//

void Consultar_Questionarios(struct Questionarios questionarios[], int conta_esc_ques[]);//Funcao para visualizar questionarios//

void loadQuestionarios(struct Questionarios questionarios[], int conta_esc_ques[]);//Funcao para ler questionarios do ficheiro//

void faz_contadores(int conta_esc_ques[], struct Questionarios questionarios[],struct Escolas escolas[]);//Funcao para fazer contadores//

void mostra_contadores(int conta_esc_ques[], struct Escolas escolas[], int conta1, int conta2, int conta3, int conta4, int conta5);//Funcao para dar print dos contadores//

void questionarios_por_genero(struct Questionarios questionarios[], int cont_esc_ques[]);//Funcao para mostrar questionarios por genero//

void questionarios_por_idade(struct Questionarios questionarios[], int cont_esc_ques[]);//Funcao para fazer contadores por faixa etaria//

void mostra_contadores_de_idade(int conta1, int conta2, int conta3, int conta4,int conta5, int conta6); //Funcao para mostrar contadores de faixas etarias//

void questionarios_por_contagio(struct Questionarios questionarios[], int cont_esc_ques[]);//Funcao para fazer contadores por nivel de contagio//

void pede_residencia(char concelho[]);//ENTREGA 2//

void sintomas_menos_frequente(struct Questionarios questionarios[], int cont_esc_ques[]);//ENTREGA 2//

void mostrar_sintoma_menos_frequente(int contador []);//ENTREGA 2//

void imprime_Sintoma_menos_frequente(int sintoma);//ENTREGA 2 //


//M A I N //
int main(){


    struct Escolas escolas[MAX_ESC];

    struct Questionarios questionarios[MAX_QUES];

    int conta_esc_ques[2]= {0,0}; // [0] � o contador de escolas e o [1] o  contador total dos questionarios

    Iniciar_Ficheiros();

    loadEscolas(escolas,conta_esc_ques);

    loadQuestionarios(questionarios, conta_esc_ques);

    Menu(escolas,questionarios,conta_esc_ques);

    return 0;
}


//Funcao para inicializar ficheiros//
void Iniciar_Ficheiros() {
    FILE * file;

    file = openFile("Escolas.bin", "ab");
    fclose(file);

    file = openFile("Questionarios.bin", "ab");
    fclose(file);
}



// Funcao para ler inteiro//
int getInt(char msg[],int min,int max) {

    int inteiro;

    printf("%s", msg);
    do {
        printf("--> ");
        fflush(stdin);
        scanf("%d",&inteiro);
    }
    while(inteiro < min || inteiro > max);

    return inteiro;
}


//Funcao para ler float//
float getFloat(char msg[],int min,int max) {
    float decimal;

    printf("%s", msg);
    do
    {

        printf("->");
        fflush(stdin);
        scanf("%f",&decimal);

    }
    while(decimal < min || decimal > max);

    return decimal;
}

//Funcao para ler Char
char getChar(char msg[]) {
    char character;



    printf("%s", msg);
    fflush(stdin);
    scanf("%c",&character);


    return character;
}


//Funcao para ler string //

void ler_string (char texto[], char string[], int max) {
    do {

        printf("%s", texto);
        fflush(stdin);
        fgets(string, max, stdin);

        int tamanho = strlen(string);

        if(string[tamanho-1] == '\n'){
            string[tamanho-1] = '\0';
        }
        clear_screen();

    }
    while(strlen(string) == 0);
}

//Funcao para limpar ecra, baseado no sistema operativo
void clear_screen() {

system("@cls || clear");

}

//Funcao para fazer os contadores//
void faz_contadores(int conta_esc_ques[], struct Questionarios questionarios[],struct Escolas escolas[MAX_ESC]){

    int indice = 0,contador_1 = 0, contador_2 = 0,contador_3 = 0,contador_4 = 0, contador_5 = 0;

    while (indice < conta_esc_ques[1]){

        if(questionarios[indice].escola == 1){
            contador_1++;
        }

        else if(questionarios[indice].escola == 2){
            contador_2++;
        }

        else if(questionarios[indice].escola == 3){
            contador_3++;
        }

        else if(questionarios[indice].escola == 4){
            contador_4++;
        }

        else if(questionarios[indice].escola == 5){
            contador_5++;
        }
        indice++;
    }
    mostra_contadores(conta_esc_ques,escolas,contador_1,contador_2,contador_3,contador_4,contador_5);

}

//Funcao para mostrar contadores no menu//
void mostra_contadores(int conta_esc_ques[], struct Escolas escolas[], int conta1, int conta2, int conta3,int conta4, int conta5){

    int indice;

    printf("Total : %i",conta_esc_ques[1]);

    for(indice = 0; indice < conta_esc_ques[0]; indice++){

        if(indice == 0){
            printf("\t %s : %i",escolas[indice].nome,conta1);
        }

        else if (indice == 1){
            printf("\t %s : %i",escolas[indice].nome,conta2);
        }

        else if (indice == 2){
            printf("\t %s : %i",escolas[indice].nome,conta3);
        }

        else if (indice == 3){
            printf("\t %s : %i",escolas[indice].nome,conta4);
        }

        else if (indice == 4){
            printf("\t %s : %i",escolas[indice].nome,conta5);
        }

    }

}

// Funcao do menu principal//
void Menu(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]){

    int op;

    do{
        faz_contadores(conta_esc_ques,questionarios,escolas);
        printf("\n\n\tMenu Principal\n\n\t1. Escolas\n\t2. Questionarios\n\t3. Estatisticas\n\t0. Sair\n\n\tOpcao ");
        op = getInt("",0,3);
        clear_screen();

        switch(op){

        case 1:
            clear_screen();
            Menu_Escolas(escolas, questionarios, conta_esc_ques);
            break;

        case 2:
            clear_screen();
            Menu_Questionarios(escolas, questionarios, conta_esc_ques);
            break;

        case 3:
            clear_screen();
            Menu_Estatisticas(escolas, questionarios, conta_esc_ques);
            break;

        case 0:

            printf("Programa encerrado.\n\n");
            exit(0);
        }

    }
    while(op != 0);

    exit(0);
}




// Funcao do menu escolas//
void Menu_Escolas(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]){

    int op;

    do {
        printf("\n\tMenu - Escolas\n\n\t1. Registrar\n\t2. Consultar\n\t0. Voltar\n\n\tOpcao ");
        op = getInt("",0,2);

        switch(op){

        case 1:
            clear_screen();
            Registrar_Escola(escolas, questionarios, conta_esc_ques);
            break;

        case 2:
            clear_screen();
            Consultar_Escolas(escolas, conta_esc_ques);
            break;

        case 0:

            break;

        }
    }
    while(op != 0);
    clear_screen();
}


// Funcao para registar escola//
int Registrar_Escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]){

    int id = gera_id_escola(escolas, questionarios, conta_esc_ques);

    if (id == -1) {
    return -1;
    }

    char nome[50], localidade[50];

    ler_string( "Nome: ",nome,50);

    if(verifica_nome_escola(escolas, nome, conta_esc_ques) == 0){

        ler_string("Localidade: ",localidade,50);

        Adicionar_Escola(escolas, id, nome, localidade, conta_esc_ques);

        Gravar_Escolas(escolas, conta_esc_ques);
    } else {
        printf("Erro, o nome introduzido ja existe!\n");
    }

    return 0;
}

//Funcao para Adicionar escola � struct das escolas
void Adicionar_Escola(struct Escolas escolas[], int id, char nome[50], char localidade[50], int conta_esc_ques[]) {
    int indice = 0;

    while(indice < conta_esc_ques[0]){
        indice++;
    }

    if(indice != MAX_ESC){
        escolas[indice].id = id;
        strcpy(escolas[indice].nome, nome);
        strcpy(escolas[indice].localidade, localidade);

        conta_esc_ques[0]++;
    } else {

    }
}


//Funcao para atribuir id � escola //
int gera_id_escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]) {

    int indice = 0;

    while(indice < conta_esc_ques[0]) {

        indice++;
    }
    if(indice == MAX_ESC) {

        printf("\n\nErro! Capacidade maxima de Escolas atingido.\n");
        sleep(1);
        clear_screen();
        return -1;

    } else if (indice == 0) {

        return 1;

    } else {

    return (escolas[indice-1].id + 1);
    }
    return 0;
}

// Funcao para verificar se o nome da escola inserido j� existe//
int verifica_nome_escola(struct Escolas escolas[], char nome[50], int conta_esc_ques[]) {
    int indice = 0;
    while(indice < conta_esc_ques[0]){
        if(strcasecmp(escolas[indice].nome, nome) == 0){
            return 1;
            break;
        }
        indice++;
    }
    return 0;
}

// Funcao para consultar escolas//
int Consultar_Escolas(struct Escolas escolas[], int conta_esc_ques[]) {
    int indice = 0,sair = 0;

    while(indice < conta_esc_ques[0]) {
        printf("Escola %d\nNome: %s\nLocalidade: %s\n\n", escolas[indice].id, escolas[indice].nome, escolas[indice].localidade);
        indice++;
    }

    if(indice == 0) {
        puts("\nFicheiro vazio! Nenhuma escola foi inserida.\n");
        sleep(1);
    }
    sair = getInt("Digite 1 para sair\n",1,1);

    if( sair == 1) {
        clear_screen();
        return 0;
    }

    return 0;
}


//Funcao para manipular ficheiros, onde o "name_file" � o nome do ficheiro que vai ser manipulado, e o "mode" o modo para manipular: ler, escrever, etc//
FILE * openFile(char name_file[], char mode[]) {

    FILE * file = fopen(name_file,mode);

    if(file == NULL){
        puts("Erro ao abrir ficheiro!");
        exit(1);
    }

    return file;
}


//Funcao para gravar escolas no ficheiro
void Gravar_Escolas(struct Escolas escolas[], int conta_esc_ques[]) {

    FILE * file = openFile("Escolas.bin","wb");

    fwrite(&conta_esc_ques[0], sizeof(conta_esc_ques[0]), 1, file);
    fwrite(escolas, sizeof(struct Escolas), conta_esc_ques[0], file);

    fclose(file);
}


//Funcao para ler escolas do ficheiro
void loadEscolas(struct Escolas escolas[], int conta_esc_ques[]){

    FILE * file = openFile("Escolas.bin", "rb");

    fread(&conta_esc_ques[0], sizeof(conta_esc_ques[0]), 1, file);
    fread(escolas, sizeof(struct Escolas), conta_esc_ques[0], file);

    fclose(file);
}



// Funcao do Menu questionarios//
void Menu_Questionarios(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]){

    int op;
    do{
        printf("\n\tMenu - Questionarios\n\n\t1. Registrar\n\t2. Consultar\n\t0. Voltar\n\n\tOpcao ");

        op = getInt("",0,2);

        switch(op){

        case 1:
            clear_screen();
            verifica_escolas(escolas,questionarios,conta_esc_ques);

            break;

        case 2:
            Consultar_Questionarios(questionarios, conta_esc_ques);

            break;

        case 0:

            break;

        }

    } while(op != 0);

    clear_screen();
}


//Funcao que gera um id para o questionario //
int gera_id_questionario(struct Questionarios questionarios[], struct Escolas escolas[], int conta_esc_ques[]) {
    int indice = 0;

    while(indice < conta_esc_ques[1]) {
        indice++;

    }
    if(indice == MAX_QUES) {
        clear_screen();
        printf("\n\nErro, a capacidade maxima de questionarios foi atingida!\n");
        Menu_Questionarios(escolas, questionarios, conta_esc_ques);

    } else if (indice == 0) {
        return 1;

    } else {
        return (questionarios[indice-1].id + 1);

    }
    return 0;
}


//Funcao que regista questionarios//
int Registrar_Questionario(struct Questionarios questionarios[], struct Escolas escolas[], int conta_esc_ques[]) {

    int id = gera_id_questionario(questionarios, escolas, conta_esc_ques),escola = 0,idade = 0,sintomas[7],doencas[8];
    char  data[20], risco[20], genero[20], residencia[50], tipo[20], contato[20],concelho [50];
    float temperatura;

    escola = atribuir_Escola(escolas, questionarios, conta_esc_ques,id);

    if (escola == -1) {
        return -1;
    }

    atribuir_Data(data);


    idade = getInt("Idade: ",18,150);

    clear_screen();

    atribuir_Genero(genero);

    ler_string("Residencia: ",residencia,50);

    pede_residencia(concelho); //ENTREGA 2 //

    atribuir_Tipo(tipo);

    atribuir_Contato(contato);

    atribuir_Sintomas(sintomas);

    atribuir_Doenca(doencas);

    temperatura = getFloat("Temperatura medida\n",20,42);

    clear_screen();

    contagio(contato,sintomas,doencas,temperatura,risco);

    Adicionar_Questionario(questionarios, id, escola, data, risco, idade, genero, residencia, tipo, contato, sintomas, doencas, temperatura, conta_esc_ques,concelho);

    Gravar_Questionarios(questionarios, conta_esc_ques);

    return 0;
}

//Funcao que verifica se existe alguma escola criada, se existir, faz o questionario, se n�o, volta para o menu dos questionarios
int verifica_escolas(struct Escolas escolas[], struct Questionarios questionarios[],int conta_esc_ques[]) {

    if (conta_esc_ques[0] == 0) {
        printf("\nNenhuma escola criada!\n");
        sleep(1);
        clear_screen();
        return 0;

    } else {
        Registrar_Questionario(questionarios,escolas,conta_esc_ques);

    }
    clear_screen();
    return 0;
}

//Funcao para verificar se o contador de x escola j� atingiu o limite
int verifica_contador_escola(struct Questionarios questionarios[], int conta_esc_ques[],int id){
    int indice = 0, contador = 0;

    while (indice < conta_esc_ques[1]) {

        if(questionarios[indice].escola == questionarios[id].escola ){
            contador++;

        }
        indice++;
    }
    return contador;

}



//Funcao que pergunta a  escola//
int atribuir_Escola(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[], int id) {

    int i, escolas_atuais =conta_esc_ques[0],escola = 0, contador = 0;
    do {
    for( i = 0; i < escolas_atuais; i++) {
        printf("%i. %s\n",i+1,escolas[i].nome);
    }
        printf("\nPressione 0 para voltar\n");

        escola = getInt("\nInsira o digito correspondente a escola desejada\n",0,escolas_atuais);

    if (escola == 0) {
        return -1;
    }

        contador = verifica_contador_escola(questionarios,conta_esc_ques,id);

        if(contador == MAX_QUES_ESC){
            clear_screen();
            printf("\nMaximo de escolas atingido\nEscolha outra escola!\n\n");
        } else {
            clear_screen();
            return escola;
        }

    } while(contador == MAX_QUES_ESC || escola == 0);

    return 0;
}

//funcao para perguntar a data//
void atribuir_Data(char data[]) {

    int ano, mes, dia, hora, minuto,veri = 2;
    do{
        printf("DATA\n");
        ano = getInt("ano: ",2020,2021);
        mes = getInt("mes: ",1,12);
        dia = getInt("dia: ",1,31);
        hora = getInt("horas: ",0,23);
        minuto = getInt("minutos: ",0,59);

        if((ano >= 2020 && ano <=2021 && ( ano % 4 == 0 && ano % 100 != 0 ) || (ano % 400 == 0))  && mes == 2 && dia > 0 && dia <= 29 && hora > 0 && hora <24 && minuto > 0 && minuto < 60){

            sprintf(data,"%d-%d-%d %d:%d", ano, mes, dia, hora, minuto);
            veri = 1;

        } else if(ano >= 2020 && ano <=2021 && mes == 2 && dia > 0 && dia < 29 && hora > 0 && hora <24 && minuto > 0 && minuto < 60){

            sprintf(data,"%d-%d-%d %d:%d", ano, mes, dia, hora, minuto);
            veri = 1;

        } else if(ano >= 2020 && ano <=2021 && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia > 0 && dia <= 31 && hora > 0 && hora <24 && minuto > 0 && minuto < 60){

            sprintf(data,"%d-%d-%d %d:%d", ano, mes, dia, hora, minuto);
            veri = 1;
        } else if(ano >= 2020 && ano <=2021 &&  (mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 0 && dia <= 30 && hora > 0 &&hora <24 && minuto > 0 && minuto < 60){

            sprintf(data,"%d-%d-%d %d:%d", ano, mes, dia, hora, minuto);
            veri = 1;
        } else {
            clear_screen();
            printf("Data invalida, tente novamente!\n\n");
        }
    } while(veri != 1);

}

//Funcao para pedir genero//
void atribuir_Genero(char genero[]) {

    char resposta;

    do {
        resposta = getChar("Genero?\n(M)asculino\n(F)eminino\nResposta - ");
        resposta = toupper(resposta);
        switch(resposta) {

        case 'F':
            strcpy( genero,"Feminino");
            break;

        case 'M':
            strcpy( genero,"Masculino");
            break;

        default:
            clear_screen();
            printf("Resposta invalida! Tente novamente.");
            break;

        }

    } while(resposta != 'M' && resposta != 'F');
    clear_screen();
}


//Funcao para perguntar o tipo de participante//
void atribuir_Tipo(char tipo []) {

    int resposta;

    resposta = getInt("Tipo de Participante?\n1. Docente\n2. Estudante\n3. Funcionario\n4. Investigador\nResposta  ",1,4);

    switch(resposta) {

    case 1:
        strcpy(tipo,"Docente");
        break;

    case 2:
        strcpy(tipo,"Estudante");
        break;

    case 3:
        strcpy(tipo,"Funcionario");
        break;

    case 4:
        strcpy(tipo,"Investigador");
        break;
    }
    clear_screen();
}


//Funcao para perguntar o contacto//
void atribuir_Contato(char contacto[]) {
    char resposta;

    do {
        resposta = getChar("Nos ultimos 15 dias esteve em contacto com pessoa infetada com COVID-19?\n(S)im\n(N)ao\n(D)esconhecido\nResposta - ");
        resposta = toupper(resposta);
        switch(resposta) {

        case 'S':
            strcpy(contacto,"Sim");
            break;

        case 'N':
            strcpy(contacto,"Nao");
            break;

        case 'D':
            strcpy(contacto,"Desconhecido");
            break;

        default:
            printf("Resposta invalida! Tente novamente.");
            clear_screen();
            break;

        }
    }
    while(resposta != 'S' && resposta != 'N' && resposta != 'D');
    clear_screen();
}


//Funcao para perguntar sintomas //
void atribuir_Sintomas(int sintomas[]) {

    int resposta = 0,  tamanho = 0;

    do{
        do{
            resposta = getInt("Que sintomas sente (0 para terminar)?\n1. Dificuldade respiratoria\n2. Dor muscular\n3. Fadiga\n4. Falta de paladar\n5. Nauseas\n6. Febre\n7. Tosse\n8. Dor de Garganta",0,8);

        }
        while(verifica_Sintoma(sintomas,tamanho,resposta) == 1);
        sintomas[tamanho] = resposta;
        tamanho++;
        clear_screen();
    }
    while(resposta != 0 && tamanho < 8);
    clear_screen();
}

//funcao que verifica se existe algum sintoma repetido//
int verifica_Sintoma( int sintomas[], int tamanho, int resposta) {

    int j;
    for(j = 0; j < tamanho; j++) {

        if( resposta == sintomas[j]) {
            clear_screen();
            printf("\nSintoma ja inserido!!\n\n");
            return 1;

        }
    }
    return 0;
}

//funcao que converte a opcao selecionada em string//
void imprime_Sintoma(int sintomas[]) {

    int index, max = conta_sintomas_doencas(sintomas,8);

    for(index = 0; index <= max; index++){


        if(sintomas[index] == 1){
            printf("Dificuldade respiratoria\n");

        } else if(sintomas[index] == 2){
            printf("Dor muscular\n");

        } else if(sintomas[index] == 3){
            printf("Fadiga\n");

        } else if(sintomas[index] == 4) {
            printf("Falta de paladar\n");

        } else if(sintomas[index] == 5){
            printf("Nauseas\n");

        } else if(sintomas[index] == 6){
            printf("Febre\n");

        } else if(sintomas[index] == 7){
            printf("Tosse\n");
            
         } else if(sintomas[index] == 8){
            printf("Dor de Garganta\n");
            
        } else if(sintomas[0]== 0){
            printf("Sem sintomas \n");
        }
    }
}


//Funcao para perguntar doencas//
void atribuir_Doenca(int doencas[]){

    int resposta = 0,  tamanho = 0;
    do {

        do{
            resposta = getInt("Que doencas tem (0 para terminar)?\n1. Autoimune\n2. Cancro\n3. Cardiovascular\n4. Diabetes\n5. Hipertensao\n6. Obesidade\n7. Renal\n8. Respiratoria\n",0,8);

        } while(verifica_Doencas(doencas,tamanho,resposta) == 1);
        doencas[tamanho] = resposta;
        tamanho++;
        clear_screen();
    } while(resposta != 0 && tamanho < 7);

    clear_screen();
}

//funcao que verifica se existe alguma doenca repetido//
int verifica_Doencas( int doencas[], int tamanho, int resposta){

    int j;

    for(j = 0; j < tamanho; j++){

        if( resposta == doencas[j]){
            clear_screen();
            printf("\nDoenca ja inserida!!\n\n");
            return 1;

        }
    }

    return 0;
}

//funcao que converte a opcao selecionada em string//
void imprime_Doenca(int doencas[]) {

    int index,max = conta_sintomas_doencas(doencas,8);

    for(index = 0; index <= max; index++){

        if(doencas[index] == 1){
            printf("Autoimune\n");

        } else if(doencas[index] == 2){
            printf("Cancro\n");

        } else if(doencas[index] == 3){
            printf("Cardiovascular\n");

        } else if(doencas[index] == 4){
            printf("Diabetes\n");

        } else if(doencas[index] == 5){
            printf("Hipertensao\n");

        } else if(doencas[index] == 6){
            printf("Obesidade\n");

        } else if(doencas[index] == 7) {
            printf("Renal\n");

        } else if(doencas[0]== 0) {
            printf("Sem doencas \n");

        } else if(doencas[index] == 8) {
            printf("Respiratoria\n");

        }
    }
}


//Funcao para determinar o nivel de contagio//
void contagio(char contato[], int sintomas[], int doencas[], float temperatura,char risco[]){

    int nr_sintomas, nr_doencas;

    nr_sintomas = conta_sintomas_doencas(sintomas,7);
    nr_doencas = conta_sintomas_doencas(doencas,8);

    if(temperatura < 36.5 || strcmp(contato, "Nao") == 0  || sintomas[0] == 0 || doencas[0] == 0){

        strcpy(risco,"Baixo");

    }else if((temperatura >= 36.5 && temperatura < 38.0)  || strcmp(contato, "Desconhecido") == 0 || nr_sintomas >= 2 || nr_doencas >= 1 ){

        strcpy(risco,"Medio");

    }else if(temperatura >= 38.0 || strcmp(contato, "Sim") == 0){

        strcpy(risco,"Alto");

    }
}

//Funcao que conta quantos sintomas ou doencas foram registrados//
int conta_sintomas_doencas(int array[],int max) {

    int index,contador = 0;

    for (index = 0; index < max; index++) {

        if ( array[index] != 0){

            contador++;
        } else {
            return contador;
        }
    }

    return 0;
}


//Funcao para adicionar todo o conteudo pedido ao utilizador na struct questionarios//
void Adicionar_Questionario(struct Questionarios questionarios[], int id, int escola, char data[], char risco[], int idade, char genero[], char residencia[], char tipo[], char contato[], int sintomas[], int doencas[], float temperatura, int conta_esc_ques[],char concelho[]){
    int indice = 0;

    while(indice < conta_esc_ques[1]){
        indice++;
    }
    if(indice != MAX_QUES) {

        questionarios[indice].id = id;
        questionarios[indice].escola = escola;
        strcpy(questionarios[indice].data, data);
        strcpy(questionarios[indice].risco, risco);
        questionarios[indice].idade = idade;
        strcpy(questionarios[indice].genero, genero);
        strcpy(questionarios[indice].residencia, residencia);
        strcpy(questionarios[indice].concelho,concelho);
        strcpy(questionarios[indice].tipo, tipo);
        strcpy(questionarios[indice].contato, contato);
        adicionar_sintomas_doencas_na_Struct(sintomas,questionarios,7,indice,1);
        adicionar_sintomas_doencas_na_Struct(doencas,questionarios,8,indice,0);
        questionarios[indice].temperatura = temperatura;

        conta_esc_ques[1]++;

    } else {
        clear_screen();
        printf("\n\nErro! Capacidade maxima de Questionarios atingido.\n");
    }
}


//Funcao para passar os sintomas inseridos para a struct//
void adicionar_sintomas_doencas_na_Struct(int array[],struct Questionarios questionarios[],int max,int indice,int valida){

    int index = 0;
    if(valida == 1){

        for(index = 0; index < max; index++){
            questionarios[indice].sintomas[index] = array[index];

        }
    }else{

        for(index = 0; index < max; index++){
            questionarios[indice].doencas[index] = array[index];

        }

    }
}

//Funcao que grava questionarios no ficheiro//
void Gravar_Questionarios(struct Questionarios questionarios[], int conta_esc_ques[]) {
    FILE * file;
    file = openFile("Questionarios.bin","wb");

    fwrite(&conta_esc_ques[1], sizeof(conta_esc_ques[1]), 1, file);
    fwrite(questionarios, sizeof(struct Questionarios), conta_esc_ques[1], file);

    fclose(file);
}


//Funcao para ler questionarios do ficheiro//
void loadQuestionarios(struct Questionarios questionarios[], int conta_esc_ques[]) {
    FILE * file = openFile("Questionarios.bin", "rb");

    fread(&conta_esc_ques[1], sizeof(conta_esc_ques[1]), 1, file);
    fread(questionarios, sizeof(struct Questionarios), conta_esc_ques[1], file);

    fclose(file);
}

//Funcao usada para consultar os questionarios//
void Consultar_Questionarios(struct Questionarios questionarios[], int conta_esc_ques[]) {
    int indice = 0, sair = 0;
    clear_screen();
    while(indice < conta_esc_ques[1]){

        printf("Questionario %d\n", questionarios[indice].id);
        printf("Escola: %d\n", questionarios[indice].escola);
        printf("Data: %s\n", questionarios[indice].data);
        printf("Risco de Contagio: %s\n", questionarios[indice].risco);
        printf("Idade: %d\n", questionarios[indice].idade);
        printf("Genero: %s\n", questionarios[indice].genero);
        printf("Residencia: %s\n", questionarios[indice].residencia);
        printf("Concelho: %s\n",questionarios[indice].concelho);
        printf("Tipo de participante: %s\n", questionarios[indice].tipo);
        printf("Contato com infetado: %s\n", questionarios[indice].contato);
        imprime_Sintoma(questionarios[indice].sintomas);
        imprime_Doenca(questionarios[indice].doencas);
        printf("Temperatura: %.1f\n\n", questionarios[indice].temperatura);

        indice++;
    }if(indice == 0){
        printf("Ficheiro vazio! Nenhum questionario foi inserido.\n");
    }

    sair = getInt("Digite 1 para sair\n",1,1);
    if( sair == 1) {
        clear_screen();

    }
}

//Funcao do menu das Estatisticas
void Menu_Estatisticas(struct Escolas escolas[], struct Questionarios questionarios[], int conta_esc_ques[]) {

    int op;
    do{
        printf("\n\tMenu - Estatisticas\n\n\t1. Total de questionarios por genero\n\t2. Total de questionarios por faixa etaria\n\t3. Percentagem de questionarios por nivel de contagio\n\t4 . Sintoma menos frequente\n\t0. Voltar\n\n\tOpcao ");

        op = getInt("",0,4);

        switch(op){

        case 1:
            clear_screen();
            questionarios_por_genero(questionarios,conta_esc_ques);

            break;

        case 2:
            clear_screen();
            questionarios_por_idade(questionarios, conta_esc_ques);
            break;

        case 3:
            clear_screen();
            questionarios_por_contagio(questionarios,conta_esc_ques);
            break;
        
        case 4:
        	sintomas_menos_frequente(questionarios,conta_esc_ques);
        	break;

        case 0:

            break;
        }

    } while(op != 0);

    clear_screen();

}

//Funcao para contar os questionarios por genero//
void questionarios_por_genero(struct Questionarios questionarios[], int cont_esc_ques[]) {

    int indice = 0,conta_M = 0,conta_F = 0,sair = 0;

    while (indice < cont_esc_ques[1]) {

        if(strcmp(questionarios[indice].genero,"Masculino")== 0) {

            conta_M++;

        }
        else if(strcmp(questionarios[indice].genero,"Feminino")== 0){

            conta_F++;
        }

        indice++;
    }

    printf("Questionarios Masculinos: %i \n",conta_M);
    printf("Questionarios Femininos: %i\n",conta_F);

    sair = getInt("\nDigite 1 para sair\n",1,1);
    if( sair == 1){
        clear_screen();
    }

}

//Funcao para contar os questionarios por faixa etaria//
void questionarios_por_idade(struct Questionarios questionarios[], int cont_esc_ques[]) {

    int indice = 0, conta_18_23 = 0, conta_24_30 = 0, conta_31_40 = 0, conta_41_50 = 0, conta_51_65 = 0, conta_66_mais = 0;

    while(indice < cont_esc_ques[1]) {

        if(questionarios[indice].idade >= 18 && questionarios[indice].idade <= 23 ) {
            conta_18_23++;

        } else if(questionarios[indice].idade >= 24 && questionarios[indice].idade <= 30 ) {
            conta_24_30++;

        } else if(questionarios[indice].idade >= 31 && questionarios[indice].idade <= 40 ) {
            conta_31_40++;

        } else if(questionarios[indice].idade >= 41 && questionarios[indice].idade <= 50 ) {
            conta_41_50++;

        } else if(questionarios[indice].idade >= 51 && questionarios[indice].idade <= 65 ) {

            conta_51_65++;

        } else if(questionarios[indice].idade >= 66  ) {

            conta_66_mais++;
        }
        indice++;

    }
    mostra_contadores_de_idade(conta_18_23,conta_24_30,conta_31_40,conta_41_50,conta_51_65,conta_66_mais);
}


//Funcao para dar print dos contadores por faixa etaria//
void mostra_contadores_de_idade(int conta1, int conta2, int conta3, int conta4,int conta5, int conta6) {

    int sair = 0;

    printf("Questionarios 18 - 23: %i\n",conta1);
    printf("Questionarios 24 - 30: %i\n",conta2);
    printf("Questionarios 31 - 40: %i\n",conta3);
    printf("Questionarios 41 - 50: %i\n",conta4);
    printf("Questionarios 51 - 65: %i\n",conta5);
    printf("Questionarios 66+: %i\n",conta6);

    sair = getInt("\nDigite 1 para sair\n",1,1);
    if( sair == 1) {
        clear_screen();
    }

}

//Funcao para fazer contador de questionarios por contagio//
void questionarios_por_contagio(struct Questionarios questionarios[], int cont_esc_ques[]) {

    int indice = 0;
    float conta_baixo = 0, conta_medio = 0, conta_alto = 0, sair = 0;

    while (indice < cont_esc_ques[1]) {

        if(strcmp(questionarios[indice].risco, "Baixo") == 0) {
            conta_baixo++;

        } else if(strcmp(questionarios[indice].risco, "Medio") == 0) {
            conta_medio++;

        } else if(strcmp(questionarios[indice].risco, "Alto") == 0) {
            conta_alto++;
        }
        indice++;
    }
    conta_baixo = (conta_baixo / cont_esc_ques[1]) * 100;
    conta_medio = (conta_medio / cont_esc_ques[1]) * 100;
    conta_alto = (conta_alto / cont_esc_ques[1]) * 100;

    printf("Questionarios Baixo : %.0f%%\n",conta_baixo);
    printf("Questionarios Medio : %.0f%%\n",conta_medio);
    printf("Questionarios Alto : %.0f%%\n",conta_alto);


    sair = getInt("\nDigite 1 para sair\n",1,1);
    if( sair == 1) {
        clear_screen();
    }
}

//ENTREGA 2//
void pede_residencia(char concelho[]){
	
	ler_string("Concelho: ",concelho,50);//ENTREGA 2
	
	
}


//ENTREGA 2//
void sintomas_menos_frequente(struct Questionarios questionarios[], int cont_esc_ques[]){
	
	int indice = 0,contador[8] = {0,0,0,0,0,0,0,0},j = 0;
	
	

	while(indice < cont_esc_ques[1]){
		
		for(j = 0; j < 8;j++){
			
			
			
			if(questionarios[indice].sintomas[j] == 1){
				
				contador[0]++;
			}else if(questionarios[indice].sintomas[j] == 2){
				
				contador[1]++;
				
			}else if(questionarios[indice].sintomas[j] == 3){
				
				contador[2]++;
			}else if(questionarios[indice].sintomas[j] == 4){
				
				contador[3]++;
			}else if(questionarios[indice].sintomas[j] == 5){
				
				contador[4]++;
				
			}else if(questionarios[indice].sintomas[j] == 6){
				
				contador[5]++;
			}else if(questionarios[indice].sintomas[j] == 7){
				
				contador[6]++;
			}else if(questionarios[indice].sintomas[j] == 8){
				
				contador[7]++;
			}
		
			
		}
		
		
		
		
		indice++;
	}
	
	mostrar_sintoma_menos_frequente(contador);//ENTREGA 2//
	
}
//ENTREGA 2//
void mostrar_sintoma_menos_frequente(int contador []){
	
	int index = 0, menor = 99999,guarda_index = 0;
	
	clear_screen();
	
	while(index < 8){
		
	
		
		if(contador[index] < menor){
			
			menor = contador[index];
			guarda_index = index+1;
			
		}
		
		
		
		index++;
	}
	
	

	imprime_Sintoma_menos_frequente(guarda_index);
	
	
}


//Entrega 2/
void imprime_Sintoma_menos_frequente(int sintomas) {

	int sair = 0;

        if(sintomas == 1){
            printf("Sintoma menos frequente : Dificuldade respiratoria\n");

        } else if(sintomas == 2){
            printf("Sintoma menos frequente : Dor muscular\n");

        } else if(sintomas == 3){
            printf("Sintoma menos frequente : Fadiga\n");

        } else if(sintomas == 4) {
            printf("Sintoma menos frequente : Falta de paladar\n");

        } else if(sintomas == 5){
            printf("Sintoma menos frequente : Nauseas\n");

        } else if(sintomas == 6){
            printf("Sintoma menos frequente : Febre\n");

        } else if(sintomas == 7){
            printf("Sintoma menos frequente : Tosse\n");
            
         } else if(sintomas == 8){
            printf("Sintoma menos frequente : Dor de Garganta\n");
            
        } else if(sintomas == 0){
            printf("Sintoma menos frequente : Sem sintomas \n");
        }
    
    sair = getInt("\nDigite 1 para sair\n",1,1);
    if( sair == 1) {
        clear_screen();
    }

}
