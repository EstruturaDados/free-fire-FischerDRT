#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constante para o tamanho máximo da mochila
#define CAPACIDADE_MOCHILA 10

// Definição da struct Item
// Armazena as informações essenciais de um item coletado.
typedef struct {
    char nome[30];      // Nome do item (máx. 29 caracteres)
    char tipo[20];      // Tipo do item (ex: arma, municao, cura) (máx. 19 caractere)
    int quantidade;     // Quantidade do item
} Item;

// Variáveis globais para o inventário
Item mochila[CAPACIDADE_MOCHILA];
int totalItens = 0; // Contador de itens na mochila

// Protótipos das funções
void menu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------------------------------------------------------------------
// 1. INSERIR ITEM
// Permite ao usuário cadastrar um novo item na mochila.
// -------------------------------------------------------------------
void inserirItem() {
    if (totalItens >= CAPACIDADE_MOCHILA) {
        printf("\n[ERRO] Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Cadastro de Novo Item ---\n");

    // 1. Entrada do Nome
    printf("Nome do Item (máx. 29 caracteres): ");
    limparBuffer(); // Limpa o buffer antes de ler a string
    if (fgets(mochila[totalItens].nome, 30, stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do nome.\n");
        return;
    }
    // Remove o '\n' adicionado pelo fgets
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0;

    // 2. Entrada do Tipo
    printf("Tipo do Item (ex: arma, municao, cura) (máx. 19 caracteres): ");
    if (fgets(mochila[totalItens].tipo, 20, stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do tipo.\n");
        return;
    }
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0;

    // 3. Entrada da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &mochila[totalItens].quantidade) != 1) {
        fprintf(stderr, "Erro na leitura da quantidade. Operação cancelada.\n");
        limparBuffer();
        return;
    }

    totalItens++;
    printf("\n[SUCESSO] Item '%s' adicionado à mochila.\n", mochila[totalItens - 1].nome);
    listarItens();
}

// -------------------------------------------------------------------
// 2. REMOVER ITEM
// Permite ao usuário remover um item da mochila pelo nome.
// -------------------------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\n[INFO] A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    int i, encontrado = -1;

    printf("\n--- Remoção de Item ---\n");
    printf("Digite o NOME do item que deseja remover: ");
    limparBuffer();
    if (fgets(nomeBusca, 30, stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do nome.\n");
        return;
    }
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Busca sequencial para encontrar o item
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Move os itens subsequentes uma posição para trás para preencher o espaço
        for (i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\n[SUCESSO] Item '%s' removido da mochila.\n", nomeBusca);
    } else {
        printf("\n[INFO] Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
    listarItens();
}

// -------------------------------------------------------------------
// 3. LISTAR ITENS
// Exibe todos os itens atualmente na mochila.
// -------------------------------------------------------------------
void listarItens() {
    printf("\n--- Inventário da Mochila (%d/%d) ---\n", totalItens, CAPACIDADE_MOCHILA);

    if (totalItens == 0) {
        printf("[INFO] A mochila está vazia.\n");
        return;
    }

    printf("+----+------------------------------+--------------------+----------+\n");
    printf("| #  | Nome                         | Tipo               | Quant.   |\n");
    printf("+----+------------------------------+--------------------+----------+\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-2d | %-28s | %-18s | %-8d |\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("+----+------------------------------+--------------------+----------+\n");
}

// -------------------------------------------------------------------
// 4. BUSCAR ITEM
// Implementa a busca sequencial por nome e exibe os dados do item.
// -------------------------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[INFO] A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    int i, encontrado = 0;

    printf("\n--- Busca de Item ---\n");
    printf("Digite o NOME do item que deseja buscar: ");
    limparBuffer();
    if (fgets(nomeBusca, 30, stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do nome.\n");
        return;
    }
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Busca sequencial
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[SUCESSO] Item encontrado:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n[INFO] Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// -------------------------------------------------------------------
// FUNÇÃO PRINCIPAL E MENU
// -------------------------------------------------------------------
void menu() {
    printf("\n==================================================\n");
    printf("         SISTEMA DE INVENTÁRIO (MOCHILA)          \n");
    printf("==================================================\n");
    printf("1. Cadastrar Novo Item\n");
    printf("2. Remover Item (por nome)\n");
    printf("3. Listar Todos os Itens\n");
    printf("4. Buscar Item (por nome)\n");
    printf("5. Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            fprintf(stderr, "\n[ERRO] Entrada inválida. Tente novamente.\n");
            limparBuffer(); // Limpa o buffer para evitar loop infinito
            opcao = 0; // Define uma opção inválida para continuar o loop
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nSaindo do sistema. Inventário salvo.\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida. Por favor, escolha uma opção de 1 a 5.\n");
        }
    } while (opcao != 5);

return 0;
}