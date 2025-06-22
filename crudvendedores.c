#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VENDEDORES 100
#define ARQUIVO_VENDEDORES "vendedores.txt"

typedef struct {
    char nome[50];
    int numero;
    float salario;
    float comissao;
} Vendedor;

void cadastrarVendedor() {
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "a+");
    if (arquivo == NULL) return;

    Vendedor v;
    int existe = 0;

    printf("Número do vendedor: ");
    scanf("%d", &v.numero);
    getchar();

    Vendedor temp;
    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", temp.nome, &temp.numero, &temp.salario, &temp.comissao) != EOF) {
        if (temp.numero == v.numero) {
            printf("Número já existente.\n");
            fclose(arquivo);
            return;
        }
    }

    printf("Nome do vendedor: ");
    fgets(v.nome, 50, stdin);
    v.nome[strcspn(v.nome, "\n")] = 0;

    printf("Salário fixo: ");
    scanf("%f", &v.salario);
    getchar();

    v.comissao = 0;

    fprintf(arquivo, "%s,%d,%.2f,%.2f\n", v.nome, v.numero, v.salario, v.comissao);
    fclose(arquivo);
    printf("Vendedor cadastrado.\n");
}

void listarVendedores() {
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return;

    Vendedor v;
    printf("\nLista de Vendedores:\n");
    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", v.nome, &v.numero, &v.salario, &v.comissao) != EOF) {
        printf("Nome: %s | Número: %d | Salário: %.2f | Comissão: %.2f\n", v.nome, v.numero, v.salario, v.comissao);
    }
    fclose(arquivo);
}

void alterarVendedor() {
    Vendedor lista[MAX_VENDEDORES];
    int total = 0, numero, encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return;

    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", lista[total].nome, &lista[total].numero, &lista[total].salario, &lista[total].comissao) != EOF) {
        total++;
    }
    fclose(arquivo);

    printf("Informe o número do vendedor a alterar: ");
    scanf("%d", &numero);
    getchar();

    for (int i = 0; i < total; i++) {
        if (lista[i].numero == numero) {
            printf("Novo nome: ");
            fgets(lista[i].nome, 50, stdin);
            lista[i].nome[strcspn(lista[i].nome, "\n")] = 0;
            printf("Novo salário: ");
            scanf("%f", &lista[i].salario);
            getchar();
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Vendedor não encontrado.\n");
        return;
    }

    arquivo = fopen(ARQUIVO_VENDEDORES, "w");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s,%d,%.2f,%.2f\n", lista[i].nome, lista[i].numero, lista[i].salario, lista[i].comissao);
    }
    fclose(arquivo);
    printf("Vendedor alterado.\n");
}

void excluirVendedor() {
    Vendedor lista[MAX_VENDEDORES];
    int total = 0, numero, encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return;

    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", lista[total].nome, &lista[total].numero, &lista[total].salario, &lista[total].comissao) != EOF) {
        total++;
    }
    fclose(arquivo);

    printf("Informe o número do vendedor a excluir: ");
    scanf("%d", &numero);
    getchar();

    arquivo = fopen(ARQUIVO_VENDEDORES, "w");
    for (int i = 0; i < total; i++) {
        if (lista[i].numero != numero) {
            fprintf(arquivo, "%s,%d,%.2f,%.2f\n", lista[i].nome, lista[i].numero, lista[i].salario, lista[i].comissao);
        } else {
            encontrado = 1;
        }
    }
    fclose(arquivo);

    if (encontrado)
        printf("Vendedor excluído.\n");
    else
        printf("Vendedor não encontrado.\n");
}

int main() {
    int opcao;
    do {
        printf("\n=== CRUD VENDEDORES ===\n");
        printf("1. Cadastrar\n2. Listar\n3. Alterar\n4. Excluir\n5. Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarVendedor(); break;
            case 2: listarVendedores(); break;
            case 3: alterarVendedor(); break;
            case 4: excluirVendedor(); break;
        }
    } while (opcao != 5);

    return 0;
}
