#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VENDAS 1000
#define ARQUIVO_VENDAS "vendas.txt"

typedef struct {
    int numeroVendedor;
    float valor;
    char data[11]; // "dd/mm/aaaa"
} Venda;

void cadastrarVenda() {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "a+");
    if (arquivo == NULL) return;

    Venda v;

    printf("Número do vendedor: ");
    scanf("%d", &v.numeroVendedor);
    getchar();

    printf("Valor da venda: ");
    scanf("%f", &v.valor);
    getchar();

    printf("Data da venda (dd/mm/aaaa): ");
    fgets(v.data, 11, stdin);
    v.data[strcspn(v.data, "\n")] = 0;

    fprintf(arquivo, "%d,%.2f,%s\n", v.numeroVendedor, v.valor, v.data);
    fclose(arquivo);
    printf("Venda registrada com sucesso.\n");
}

void listarVendas() {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) return;

    Venda v;
    printf("\nLista de Vendas:\n");
    while (fscanf(arquivo, "%d,%f,%10[^\n]\n", &v.numeroVendedor, &v.valor, v.data) != EOF) {
        printf("Vendedor Nº %d | Valor: R$ %.2f | Data: %s\n", v.numeroVendedor, v.valor, v.data);
    }
    fclose(arquivo);
}

void alterarVenda() {
    Venda lista[MAX_VENDAS];
    int total = 0, numero;
    char data[11];
    int encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) return;

    while (fscanf(arquivo, "%d,%f,%10[^\n]\n", &lista[total].numeroVendedor, &lista[total].valor, lista[total].data) != EOF) {
        total++;
    }
    fclose(arquivo);

    printf("Número do vendedor da venda a alterar: ");
    scanf("%d", &numero);
    getchar();

    printf("Data da venda a alterar (dd/mm/aaaa): ");
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (lista[i].numeroVendedor == numero && strcmp(lista[i].data, data) == 0) {
            printf("Novo valor da venda: ");
            scanf("%f", &lista[i].valor);
            getchar();
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Venda não encontrada.\n");
        return;
    }

    arquivo = fopen(ARQUIVO_VENDAS, "w");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,%.2f,%s\n", lista[i].numeroVendedor, lista[i].valor, lista[i].data);
    }
    fclose(arquivo);
    printf("Venda alterada com sucesso.\n");
}

void excluirVenda() {
    Venda lista[MAX_VENDAS];
    int total = 0, numero;
    char data[11];
    int encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) return;

    while (fscanf(arquivo, "%d,%f,%10[^\n]\n", &lista[total].numeroVendedor, &lista[total].valor, lista[total].data) != EOF) {
        total++;
    }
    fclose(arquivo);

    printf("Número do vendedor da venda a excluir: ");
    scanf("%d", &numero);
    getchar();

    printf("Data da venda a excluir (dd/mm/aaaa): ");
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = 0;

    arquivo = fopen(ARQUIVO_VENDAS, "w");
    for (int i = 0; i < total; i++) {
        if (lista[i].numeroVendedor != numero || strcmp(lista[i].data, data) != 0) {
            fprintf(arquivo, "%d,%.2f,%s\n", lista[i].numeroVendedor, lista[i].valor, lista[i].data);
        } else {
            encontrado = 1;
        }
    }
    fclose(arquivo);

    if (encontrado)
        printf("Venda excluída com sucesso.\n");
    else
        printf("Venda não encontrada.\n");
}

int main() {
    int opcao;
    do {
        printf("\n=== CRUD VENDAS ===\n");
        printf("1. Cadastrar Venda\n2. Listar Vendas\n3. Alterar Venda\n4. Excluir Venda\n5. Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarVenda(); break;
            case 2: listarVendas(); break;
            case 3: alterarVenda(); break;
            case 4: excluirVenda(); break;
        }
    } while (opcao != 5);

    return 0;
}
