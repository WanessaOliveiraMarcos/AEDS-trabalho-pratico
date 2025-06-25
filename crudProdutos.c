#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_TAMANHO_PRODUTOS 100
#define SUCESSO 0

// Declaração dos Dados
typedef struct Produtos{
    char nome[50];
    int codigo;
    int quantidadeEstoque;
    float preco;
}Produtos;

// Declaração de Funções
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

int carregarProdutos(Produtos produtos[]) {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    int i = 0;

    if (arquivo == NULL) return 0;

    while (fscanf(arquivo, "Nome: %[^\n]\n", produtos[i].nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &produtos[i].codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &produtos[i].quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &produtos[i].preco) == 1) {
        i++;
        if (i >= MAX_TAMANHO_PRODUTOS){
          break;
        }
    }

    fclose(arquivo);
    return i; // número de produtos carregados
}

void excluirProduto(){
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int codigo, resposta = 0;
    bool produtoEncontrado = false;
    Produtos produto;
    Produtos tempProduto;
    do {
    printf("Digite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fscanf(arquivo, "Nome: %s\n", tempProduto.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &tempProduto.codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &tempProduto.quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &tempProduto.preco) == 1) {

        if (tempProduto.codigo != codigo) {
            // faz uma cópia do produto apenas dos produtos de codigo diferente do que deseja excluir
            fprintf(temp, "Nome: %s\n", tempProduto.nome);
            fprintf(temp, "Codigo: %d\n", tempProduto.codigo);
            fprintf(temp, "Quantidade: %d\n", tempProduto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", tempProduto.preco);
        }else{
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", tempProduto.nome);
            printf("Código: %d\n", tempProduto.codigo);
            printf("Quantidade: %d\n", tempProduto.quantidadeEstoque);
            printf("Preço: R$ %.2f\n", tempProduto.preco);
            produtoEncontrado = true;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (produtoEncontrado) {
        // substitui o arquivo original pelo arquivo temporário
        remove("dados_produtos.txt");
        rename("temp.txt", "dados_produtos.txt");
        printf("\nProduto excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
    // escolher se quer continuar
    printf("\nQuer excluir mais produtos? SIM=1 NAO=2: ");
    scanf("%d", &resposta);
    }while(resposta == 1);
}
void alterarProdutos() {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int codigo;
    bool produtoEncontrado = false;
    Produtos produto;
    Produtos tempProduto;

    printf("Digite o código do produto que deseja alterar: ");
    scanf("%d", &codigo);

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fscanf(arquivo, "Nome: %s\n", tempProduto.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &tempProduto.codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &tempProduto.quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &tempProduto.preco) == 1) {

        if (tempProduto.codigo == codigo) {
            produtoEncontrado = true;

            // mostrar dados atuais
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", tempProduto.nome);
            printf("Código: %d\n", tempProduto.codigo);
            printf("Quantidade: %d\n", tempProduto.quantidadeEstoque);
            printf("Preço: R$ %.2f\n", tempProduto.preco);

            // pega os novos dados do produto encontrado
            printf("\nDigite o novo nome do produto: ");
            scanf("%s", produto.nome);

            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &produto.quantidadeEstoque);

            printf("Digite o novo preço: R$ ");
            scanf("%f", &produto.preco);

            produto.codigo = codigo;

            // grava os dados atualizados no arquivo temporário
            fprintf(temp, "Nome: %s\n", produto.nome);
            fprintf(temp, "Codigo: %d\n", produto.codigo);
            fprintf(temp, "Quantidade: %d\n", produto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", produto.preco);

        } else {
            // faz uma cópia do Produto que não vai ser alterado
            fprintf(temp, "Nome: %s\n", tempProduto.nome);
            fprintf(temp, "Codigo: %d\n", tempProduto.codigo);
            fprintf(temp, "Quantidade: %d\n", tempProduto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", tempProduto.preco);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (produtoEncontrado) {
        // substitui o arquivo original pelo arquivo temporário
        remove("dados_produtos.txt");
        rename("temp.txt", "dados_produtos.txt");
        printf("\nProduto alterado com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
}
void consultarTodosProdutos(){
    char nome[50];
    int codigoArquivo, quantidade;
    float preco;

    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ;
    };
    // %[^\n] tudo menos o \n
     while (fscanf(arquivo, "Nome: %[^\n]\n", nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &codigoArquivo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &quantidade) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &preco) == 1) {

        printf("Nome: %s\n", nome);
        printf("Código: %d\n", codigoArquivo);
        printf("Quantidade em estoque: %d\n", quantidade);
        printf("Preço: R$ %.2f\n", preco);
        printf("---------------------------\n");
    }
    fclose(arquivo);
}
void consultarProdutoPorCodigo(){
    int codigo;
    bool produtoEncontrado = false;
    char nome[50];
    int codigoArquivo, quantidade;
    float preco;
    int encontrado = 0;
    printf("Digite o codigo do produto que deseja consultar:\n");
    scanf("%d", &codigo);

    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ;
    };
    while (fscanf(arquivo, "Nome: %s\n", nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &codigoArquivo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &quantidade) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &preco) == 1 ){

        if (codigoArquivo == codigo) {
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", nome);
            printf("Código: %d\n", codigoArquivo);
            printf("Quantidade em estoque: %d\n", quantidade);
            printf("Preço: R$ %.2f\n", preco);
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    if(produtoEncontrado == false){
      printf("Código %d não encontrado!\n", codigo);
    }
}

void cadastrarProdutos(){
    int resposta, codigo;
    bool verificaCodigo = false;
    FILE *arquivo;
    Produtos produtos[MAX_TAMANHO_PRODUTOS];
    arquivo = fopen("dados_produtos.txt", "a");
    int i = carregarProdutos(produtos);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    //inserindo dados
    do {
        printf("\n=== CADASTRO DE PRODUTO %d ===\n", i+1);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Digite o nome do produto: ");
        fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);

        // remove o '\n' se estiver presente
        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = 0;

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
        i++;

        printf("\nQuer cadastrar mais produtos? SIM=1 NAO=2: ");
        scanf("%d", &resposta);

    }while(resposta == 1 && i < MAX_TAMANHO_PRODUTOS);
    if(i >= MAX_TAMANHO_PRODUTOS){
        printf("O numero de produtos cadastrados excedeu o limite de %d", MAX_TAMANHO_PRODUTOS);
        return 1;
    }

    // fecha o arquivo
    fclose(arquivo);
}
// Função Principal
int main(int argc, char ** argv) {
    int opcao = 0;
    printf("----------------------------------\n");
    printf("|         MENU                    |\n");
    printf("| 1- Cadastrar Produtos           |\n");
    printf("| 2- Consultar Produtos Por Codigo|\n");
    printf("| 3- Consultar Produtos           |\n");
    printf("| 4- Alterar Produtos             |\n");
    printf("| 5- Excluir Produtos             |\n");
    printf("| 6- SAIR                         |\n");
    printf("----------------------------------\n");
    printf("Digite o numero da operacao que deseja realizar:\n");
    scanf("%d",&opcao);
    switch (opcao) {
            case 1:
                cadastrarProdutos();
                break;
            case 2:
                consultarProdutoPorCodigo();
                break;
            case 3:
                consultarTodosProdutos();
                break;
            case 4:
                alterarProdutos();
                break;
            case 5:
                excluirProduto();
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;

    };

    return SUCESSO;
}