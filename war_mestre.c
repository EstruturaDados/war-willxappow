#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 5

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Prototipos das Funções - Declarações das Funções
void cabecalhoEntrada();
void cabecalhoSaida();
void tituloCadastroInicial();
void cadastrarTerritorios(Territorio* mapa);
void exibirTerritorios(Territorio* mapa, int n);
void menuAcoes(Territorio* mapa, char* missaoJogador, const char* corJogador);
void escolherCorJogador(char* corJogador);
void atacar(Territorio* atacante, Territorio* defensor);
int rolarDado();
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador);
void mostrarMissao(char* missao);
void atribuirMissao(char* missao);
char* criarMissao(int tamanho);
void limparBufferEntrada();
void liberarMemoria(Territorio* mapa, char* missaoJogador);

// Alocações de Memoria
Territorio* criarMapa(int tamanho) {
    Territorio* mapa = (Territorio*) malloc(tamanho * sizeof(Territorio));
    if (!mapa) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    return mapa;
}

// --- Função Principal ---
int main() {

    srand(time(NULL));
    cabecalhoEntrada();
    
    Territorio* mapa = criarMapa(NUM_TERRITORIOS);
    char* missaoJogador = criarMissao(100);//100 char de espaço
    cadastrarTerritorios(mapa);
    atribuirMissao(missaoJogador);
    mostrarMissao(missaoJogador);

    char corJogador[TAM_COR];
    escolherCorJogador(corJogador);

    menuAcoes(mapa, missaoJogador, corJogador);

    liberarMemoria(mapa, missaoJogador);

    printf("\nJogo encerrado!\n");
    return 0;
}


// --- Funções Auxiliares ---
// Limpeza do Buffer - Entradas com Scanf
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
// Cabeçalho Inicio do jogo
void cabecalhoEntrada() {
    printf("=================================\n");
    printf("==== JOGO WAR - NIVEL MESTRE ====\n");
    printf("=================================\n");
} 
// Cabeçalho Saida do jogo
void cabecalhoSaida() {
    printf("\n================================\n");
    printf("=== MAPA DO MUNDO - MAPA ATUAL ===\n");
    printf("==================================\n");
} 
// Cabeçalho Cadastro dos Territorios
void tituloCadastroInicial(){
    printf("======================================\n");
    printf("=== CADASTRO INICIAL - TERRITORIOS ===\n");
    printf("======================================\n");
}
// Cadastrar Territorios
void cadastrarTerritorios(Territorio* mapa){
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n=== Cadastrando Território %d ===\n", i + 1);

        printf("--- Nome do Território: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("--- Cor do Exército (Azul, Verde, Vermelho): ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("--- Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}
// --- Exibir Territórios ---
void exibirTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d] %s - Exército: %s - Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}
// --- Função de Ataque ---
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 0) {
        printf("\nO território %s não tem tropas para atacar!\n", atacante->nome);
        return;
    }

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();

    printf("\n==============================================================\n");
    printf("%s (%s) com %d tropas - atacando %s (%s) com %d tropas\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);
    printf("Atacante [%s] tirou: %d | Defensor [%s] tirou: %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        int tropasTransferidas = atacante->tropas / 2; // metade das tropas
        defensor->tropas += tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);

        printf("CONQUISTA! Território %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);
        printf("%d tropas transferidas do atacante %s para o defensor %s\n",
               tropasTransferidas, atacante->nome, defensor->nome);
    } else {
        // Atacante perde
        atacante->tropas--;
        printf("VITÓRIA DO DEFENSOR! O atacante %s perdeu 1 tropa (restam %d)\n",
               atacante->nome, atacante->tropas);
    }
}
// --- Mostrar Missão sorteada para o Usuario ---
void mostrarMissao(char* missao) {
    printf("\nSua missão foi sorteada:\n%s\n", missao);
}
// --- Sortear a Missao
void atribuirMissao(char* missao) {
    char* missoes[NUM_MISSOES] = {
        "Conquistar todos os territorios de cor Azul",
        "Reduzir o numero de tropas de um inimigo a 0",
        "Ter pelo menos 2 territorios de cor Verde",
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha"
    };
    int index = rand() % NUM_MISSOES;
    strcpy(missao, missoes[index]);
}
char* criarMissao(int tamanho) {
    char* missao = (char*) malloc(tamanho* sizeof(char)); 
    if (!missao) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    return missao;
}
// --- Funções de verificar a Missao ---
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    if (strcmp(missao, "Conquistar todos os territorios de cor Azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") != 0) return 0;
        }
        return 1;
    }
    else if (strcmp(missao, "Reduzir o numero de tropas de um inimigo a 0") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0 && mapa[i].tropas == 0) return 1;
        }
        return 0;
    }
    else if (strcmp(missao, "Ter pelo menos 2 territorios de cor Verde") == 0) {
    int verdes = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, "Verde") == 0)
            verdes++;
    }
    return verdes >= 2;
    }
    else if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        // Lógica simples: se 3 territórios tiverem a mesma cor do jogador
        int count=0;
        for(int i=0;i<tamanho;i++){
            if(strcmp(mapa[i].cor,corJogador)==0) count++;
        }
        return count>=3;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for(int i=0;i<tamanho;i++){
            if(strcmp(mapa[i].cor,"Vermelho")==0 && mapa[i].tropas>0) return 0;
        }
        return 1;
    }
    return 0;
}
// --- Liberar memória da alocação dinamica ---
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
    printf("\nMemoria Liberada com Sucesso!\n");
}
// --- Função menu Atacar ---
void menuAcoes(Territorio* mapa, char* missaoJogador, const char* corJogador){
     int acao;
    while(1){
        cabecalhoSaida();
        exibirTerritorios(mapa, NUM_TERRITORIOS);

        printf("\n--- MENU DE ACOES (Exercito %s) ---\n", corJogador);
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d",&acao);
        limparBufferEntrada();

        if(acao==0) break;
        else if(acao==1){
            int atacanteIndex, defensorIndex;
            printf("\n--- FASE DE ATAQUE ---\n");
            printf("Escolha territorio atacante (1 a %d): ", NUM_TERRITORIOS);
            scanf("%d",&atacanteIndex);
            limparBufferEntrada();
            atacanteIndex--;

            printf("Escolha territorio defensor (1 a %d): ", NUM_TERRITORIOS);
            scanf("%d",&defensorIndex);
            limparBufferEntrada();
            defensorIndex--;

            if(atacanteIndex>=0 && atacanteIndex<NUM_TERRITORIOS &&
               defensorIndex>=0 && defensorIndex<NUM_TERRITORIOS &&
               strcmp(mapa[atacanteIndex].cor,mapa[defensorIndex].cor)!=0){
                atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);
            } else {
                printf("Escolha inválida!\n");
            }

            // Verificação automática da missão
            if(verificarMissao(missaoJogador, mapa, NUM_TERRITORIOS, corJogador)){
                printf("\nParabéns! Você completou sua missão e venceu o jogo!\n");
                break;
            }

            printf("\nPressione Enter para continuar...");
            getchar();
        }
        else if(acao==2){
             if(verificarMissao(missaoJogador, mapa, NUM_TERRITORIOS, corJogador)){
        printf("\nMissão concluída! Você venceu!\n");
        break; // encerra o jogo
    } else {
        printf("\nMissão ainda não concluída.\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar();
        }
        else{
            printf("Opcao invalida!\n");
        }
    }
}
// --- Escolher cor do Jogador ---
void escolherCorJogador(char* corJogador) {
    printf("\nInforme sua cor: ");
    fgets(corJogador, TAM_COR, stdin);
    corJogador[strcspn(corJogador, "\n")] = 0;
}
// --- Rolar o Dado ---
int rolarDado() {
    return rand() % 6 + 1; // número de 1 a 6
}