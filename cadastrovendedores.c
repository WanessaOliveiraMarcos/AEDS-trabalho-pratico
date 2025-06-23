#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO_VENDEDORES 100

typedef struct {
    char nome[50];
    int numero;
    float salario;
    float comissao;
} Vendedor;

// Função para verificar se o número já existe no arquivo de vendedores
int numeroExiste(int numero) {
    FILE *arquivo = fopen("dados_vendedores.txt", "r");
    if (arquivo == NULL) return 0; // arquivo não existe ainda, número não existe

    Vendedor temp;
    while (fscanf(arquivo, "Nome: %[^\n]\nNumero: %d\nSalario: %f\nComissao: %f\n-------------------\n",
                  temp.nome, &temp.numero, &temp.salario, &temp.comissao) == 4) {
        if (temp.numero == numero) {
            fclose(arquivo);
            return 1; // encontrou número repetido
        }
    }
    fclose(arquivo);
    return 0;
}

int main() {
    FILE *arquivo = fopen("dados_vendedores.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de vendedores");
        return 1;
    }

    Vendedor vendedor;
    int resposta = 1, count = 0;

    while (resposta == 1 && count < MAX_TAMANHO_VENDEDORES) {
        printf("\n=== CADASTRO DE VENDEDOR %d ===\n", count + 1);

        do {
            printf("Digite o número do vendedor: ");
            scanf("%d", &vendedor.numero);
            getchar(); // limpa buffer

            if (numeroExiste(vendedor.numero)) {
                printf("Número já cadastrado. Tente outro.\n");
            } else {
                break;
            }
        } while (1);

        printf("Digite o nome do vendedor: ");
        fgets(vendedor.nome, 50, stdin);
        vendedor.nome[strcspn(vendedor.nome, "\n")] = 0; // remove \n do fgets

        printf("Digite o salário fixo do vendedor: ");
        scanf("%f", &vendedor.salario);
        getchar(); // limpa buffer

        vendedor.comissao = 0.0f;

        // grava no arquivo
        fprintf(arquivo, "Nome: %s\n", vendedor.nome);
        fprintf(arquivo, "Numero: %d\n", vendedor.numero);
        fprintf(arquivo, "Salario: %.2f\n", vendedor.salario);
        fprintf(arquivo, "Comissao: %.2f\n", vendedor.comissao);
        fprintf(arquivo, "-------------------\n");

        count++;

        if (count >= MAX_TAMANHO_VENDEDORES) {
            printf("Limite de vendedores atingido.\n");
            break;
        }

        printf("\nQuer cadastrar mais vendedores? SIM=1 NAO=2: ");
        scanf("%d", &resposta);
        getchar(); // limpa buffer
    }

    fclose(arquivo);

    return 0;
}
