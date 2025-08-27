#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Funções Auxiliares ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cabecalhoEntrada() {
    printf("================================\n");
    printf("==== JOGO WAR - ESTRUTURADO ====\n");
    printf("================================\n");
}

void cabecalhoSaida() {
    printf("\n==================================\n");
    printf("=== MAPA DO MUNDO - MAPA ATUAL ===\n");
    printf("==================================\n");
}

void tituloCadastroInicial() {
    printf("\n======================================\n");
    printf("=== CADASTRO INICIAL - TERRITORIOS ===\n");
    printf("======================================\n");
}

int rolarDado() {
    return rand() % 6 + 1;
}

// --- Exibir Territórios ---
void exibirTerritorios(Territorio* territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d] %s - Exército: %s - Tropas: %d\n",
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
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


// --- Cadastro de Territórios ---
void cadastrarTerritorios(Territorio* territorios, int n) {
    tituloCadastroInicial();
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastrando Território %d ===\n", i + 1);

        printf("--- Nome do Território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("--- Cor do Exército (ex: Azul, Verde): ");
        fgets(territorios[i].cor, TAM_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0;

        printf("--- Número de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
    }
}

// --- Loop Principal do Jogo ---
void jogar(Territorio* territorios, int n) {
    int continuar = 1;
    while (continuar) {
        cabecalhoSaida();
        exibirTerritorios(territorios, n);

        int atacanteIndex, defensorIndex;

        printf("\n=== ESCOLHA DO ATAQUE ===\n");
        printf("Escolha o território atacante (1 a %d, ou 0 para sair): ", n);
        scanf("%d", &atacanteIndex);
        limparBufferEntrada();
        if (atacanteIndex == 0) break;
        atacanteIndex--;

        if (atacanteIndex < 0 || atacanteIndex >= n) {
            printf("Índice de atacante inválido! Tente novamente.\n");
            continue;
        }

        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &defensorIndex);
        limparBufferEntrada();
        defensorIndex--;

        if (defensorIndex < 0 || defensorIndex >= n) {
            printf("Índice de defensor inválido! Tente novamente.\n");
            continue;
        }

        if (strcmp(territorios[atacanteIndex].cor, territorios[defensorIndex].cor) == 0) {
            printf("\nNão pode atacar território da mesma cor!\n");
            continue;
        }

        atacar(&territorios[atacanteIndex], &territorios[defensorIndex]);

        printf("\nPressione Enter para continuar para o próximo turno...");
        getchar();
    }
}

// --- Função Principal ---
int main() {
    //Inicialização da randomizacao do dado
    srand(time(NULL));
    cabecalhoEntrada(); // Chama cabeçalho de Entrada
    //Alocação dos territorios
    Territorio* territorios = (Territorio*) malloc(NUM_TERRITORIOS * sizeof(Territorio));
    //Verifica a alocacao
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(territorios, NUM_TERRITORIOS);//Chama a função para Cadastrar Territorios
    jogar(territorios, NUM_TERRITORIOS);
    //Libera a alocacao
    free(territorios);
    printf("\n👋 Jogo encerrado!\n");
    return 0;
}
