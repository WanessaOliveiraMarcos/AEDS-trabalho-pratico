#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int numero;
    float salario;
    float comissao;
} Vendedor;

Vendedor* vendedores = NULL;
int qtdVendedores = 0;      

void cadastrarVendedor() {
    Vendedor v;
    int numeroExiste;
    do {
        printf("Número do vendedor: ");
        scanf("%d", &v.numero);
        getchar();

        numeroExiste = 0;
        for (int i = 0; i < qtdVendedores; i++) {
            if (vendedores[i].numero == v.numero) {
                printf("Número já cadastrado, tente outro.\n");
                numeroExiste = 1;
                break;
            }
        }
    } while(numeroExiste);

    printf("Nome do vendedor: ");
    fgets(v.nome, 50, stdin);
    v.nome[strcspn(v.nome, "\n")] = 0;

    printf("Salário fixo: ");
    scanf("%f", &v.salario);
    getchar();

    v.comissao = 0;

    vendedores = realloc(vendedores, sizeof(Vendedor) * (qtdVendedores + 1));
    vendedores[qtdVendedores++] = v;

    printf("Vendedor cadastrado com sucesso!\n");
}
