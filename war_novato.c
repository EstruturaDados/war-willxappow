#include <stdio.h>
#include <string.h>
//Novato
// ---Constantes Globais ---
#define NUM_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Definição da Estrutura (Struct) ---
// --- Definindo uma estrutura do tipo Territorio
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Definição do Cabeçalho Entrada do Jogo ---
void cabecalho_entrada(){
    printf("================================\n");
    printf("===== INICIO DO JOGO - WAR =====\n");
    printf("================================\n");
}

// --- Definição do Cabeçalho Saída do Jogo ---
void cabecalho_saida(){
    printf("\n====================================\n");
    printf("==== LISTA FINAL DE TERRITÓRIOS ====\n");
    printf("====================================\n");
}

// --- Função Limpar Buffer de Entrada ---
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Inicio do Programa ---
int main(){

    //Declarando um vetor para cadastrar até 5 territórios[NUM_TERRITORIOS = 5]
    
    struct Territorio territorios[NUM_TERRITORIOS];

    //Chamando função cabeçalho de entrada do Jogo
    cabecalho_entrada();

    //Entrada de dados via teclado pelo usuário
    //Irá fazer o cadastro de até 5 Territorios, onde foi setado NUM_TERRITORIOS = 5
    for(int i = 0; i < NUM_TERRITORIOS; i++){

        //Titulo - Cadastrando Territorios
        printf("\n=== Cadastrando Território %d ===\n\n", i + 1);

        //Entrada Nome do Territorio
        printf("--- Nome do Território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        //Entrada Cor do Exercito      
        printf("--- Cor do Exército (ex: Azul, Verde): ");
        fgets(territorios[i].cor, TAM_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';        

        //Entrada Numero de Tropas
        printf("--- Número de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        //Limpeza do Buffer
        limparBufferEntrada();

    }

    //Impressão dos Resultados
    //Chamando função cabeçalho de saida do Jogo
    cabecalho_saida();

    //Imprimindo os dados dos Territorios cadastrado via teclado pelo usuário.
    for(int i = 0; i < NUM_TERRITORIOS; i++){
        printf("\n===== TERRITÓRIO %d =====\n\n", i + 1);
        printf("--- Nome: %s\n", territorios[i].nome);
        printf("--- Cor do Exército: %s\n", territorios[i].cor);
        printf("--- Número de Tropas: %d\n", territorios[i].tropas);
    }
// --- Fim do Programa ---
return 0;
}