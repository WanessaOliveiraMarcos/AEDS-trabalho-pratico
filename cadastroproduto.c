#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_TAMANHO_PRODUTOS 100

typedef struct Produtos{
    char nome[50];
    int codigo;
    int quantidadeEstoque;
    float preco;

}Produtos;
// Declarando funções
bool verificarCodigo(int codigo, Produtos *produtos) {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    int i = 0;

    while (!feof(arquivo)) {
        fscanf(arquivo, "%s %d %d %f", produtos->nome, &produtos->codigo,&produtos->quantidadeEstoque, &produtos->preco);
        if (produtos->codigo == codigo) {
            printf("Código %d encontrado na posição %d\n", codigo, i);
            printf("Produto: %s, Preço: %.2f, Estoque: %d\n",
                   produtos->nome, produtos->preco, produtos->quantidadeEstoque);
            fclose(arquivo);
            return true;
        }
        i++;
    }
    fclose(arquivo);
    return false;
}
int CodigoAleatorio()
{
    srand(time(0));
    int codigo = rand();
    return codigo;
}
int main()
{ int resposta = 0, codigo;
     bool verificaCodigo = false;
    FILE *arquivo;
    Produtos produtos[MAX_TAMANHO_PRODUTOS];
    arquivo = fopen("dados_produtos.txt", "a");
    int i = 0, count = 0;
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    //inserindo dados
    do {
        printf("\n=== CADASTRO DE PRODUTO %d ===\n", i+1);

        printf("Digite o nome do produto: ");
        scanf("%s", produtos[i].nome);

        printf("Digite a quantidade do produto no estoque: ");
        scanf("%d", &produtos[i].quantidadeEstoque);

        printf("Digite o valor do produto: R$ ");
        scanf("%f", &produtos[i].preco);
        // verifica se o código gerado já está cadastrado
        do {
            codigo = CodigoAleatorio();
            verificaCodigo = verificarCodigo(codigo, produtos);
        }while(verificaCodigo == true);

        produtos[i].codigo = codigo;

        // Escreve os dados no arquivo
        fprintf(arquivo, "Nome: %s\n", produtos[i].nome);
        fprintf(arquivo, "Codigo: %d\n", produtos[i].codigo);
        fprintf(arquivo, "Quantidade: %d\n", produtos[i].quantidadeEstoque);
        fprintf(arquivo, "Preco: %.2f\n", produtos[i].preco);
        fprintf(arquivo, "-------------------\n");

        count++;
        i++;

        // Escolher se quer continuar
        printf("\nQuer cadastrar mais produtos? SIM=1 NAO=2: ");
        scanf("%d", &resposta);
    }while(resposta == 1 && i <= MAX_TAMANHO_PRODUTOS);

    if(i > MAX_TAMANHO_PRODUTOS){
        printf("O numero de produtos cadastrados excedeu o limite de %d", MAX_TAMANHO_PRODUTOS);
        return 1;
    }

    // Fecha o arquivo
    fclose(arquivo);
    return 0;
}