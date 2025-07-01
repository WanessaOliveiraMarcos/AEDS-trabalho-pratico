/********************************************************
* FILENAME    : main.c
* DESCRIPTION : implementa um sistema e-commerce, com ge-
*               renciamento de produtos, vendas, compra-
*               dores e vendedores.
* PUBLIC FUNCTIONS :
* [tipo_retorno] NomeFuncao1( argumentos )
* [tipo_retorno] NomeFuncao2( argumentos )
* NOTES :
* Este sistema foi desenvolvido para fins acadêmicos das
* disciplinas de Fundamentos da Engenharia de Software e
* Algoritmos e Estruturas de Dados
*
* AUTHORS     : Wanessa de Oliveira Marcos, Julya Ketly Oli
*               veira Gandra,
* START DATE  : 22 de Julho de 2025
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_TAMANHO_PRODUTOS 100
#define MAX_TAMANHO_COMPRADORES 100
#define MAX_TAMANHO_NOME 50
#define MAX_TAMANHO_CPF 15
#define MAX_TAMANHO_EMAIL 50
#define MAX_TAMANHO_RUA 50
#define MAX_TAMANHO_BAIRRO 30
#define MAX_TAMANHO_CIDADE 30
#define MAX_TAMANHO_ESTADO 3
#define MAX_TAMANHO_CEP 10
#define MAX_VENDEDORES 100
#define MAX_VENDAS 1000
#define ARQUIVO_VENDAS "vendas.txt"
#define ARQUIVO_VENDEDORES "vendedores.txt"
#define SUCESSO 0

/* * * * * * * * * * * * * * * * * * *
* Declaração das Estruturas de Dados *
* * * * * * * * * * * * * * * * * * */

typedef struct Produtos{
    char nome[50];
    int codigo;
    int quantidadeEstoque;
    float preco;
}Produtos;

typedef struct {
    char rua[MAX_TAMANHO_RUA], bairro[MAX_TAMANHO_BAIRRO], cidade[MAX_TAMANHO_CIDADE], estado[MAX_TAMANHO_ESTADO], cep[MAX_TAMANHO_CEP];
} Endereco;

typedef struct {
    char nome[MAX_TAMANHO_NOME];
    char cpf[MAX_TAMANHO_CPF];
    char email[MAX_TAMANHO_EMAIL];
    Endereco endereco;
} Comprador;

typedef struct {
    char nome[50];
    int numero;
    float salario;
    float comissao;
} Vendedor;

typedef struct {
    int numeroVendedor;
    float valor;
    char data[11]; // "dd/mm/aaaa"
} Venda;

/* * * * * * * * * * * * * * * * * * * *
*       Declaração das Funções         *
* * * * * * * * * * * * * * * * * * * */

 void freteAteCemReais(float valorCompra){
     int frete=30;
     printf("\n----------------\n");
     printf("Frete = R$%d",frete);
     printf("\n----------------\n");
}
//frete com o valor da compra de 100 ate 300 reais
void freteAteTrezentosReais(float valorCompra){
    int frete=20;
    printf("\n----------------\n");
    printf("Frete = R$%d",frete);
    printf("\n----------------\n");
}
 //frete com o valor da compra acima de 300 reais
void freteAcimaTrezentos(float valorCompra){
    int frete=0;
    printf("\n----------------\n");
    printf("Frete = R$%d",frete);
    printf("\n----------------\n");
}

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

int carregarNumeroDeCompradores(Comprador compradores[]) {
    FILE *arquivo = fopen("dados_compradores.txt", "r");
    int i = 0;

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    while (
        fscanf(arquivo, "Nome: %[^\n]\n", compradores[i].nome) == 1 &&
        fscanf(arquivo, "CPF: %[^\n]\n", compradores[i].cpf) == 1 &&
        fscanf(arquivo, "Email: %[^\n]\n", compradores[i].email) == 1 &&
        fscanf(arquivo, "Rua: %[^\n]\n", compradores[i].endereco.rua) == 1 &&
        fscanf(arquivo, "Bairro: %[^\n]\n", compradores[i].endereco.bairro) == 1 &&
        fscanf(arquivo, "Cidade: %[^\n]\n", compradores[i].endereco.cidade) == 1 &&
        fscanf(arquivo, "Estado: %[^\n]\n", compradores[i].endereco.estado) == 1 &&
        fscanf(arquivo, "CEP: %[^\n]\n", compradores[i].endereco.cep) == 1
    ) {
        i++;
    }

    fclose(arquivo);
    return i;
}

/* * * * * * * * * * * * * * * * * * *
*  Funções do CRUD dos Compradores   *
* * * * * * * * * * * * * * * * * * */

int cadastrarCompradores(){
    int resposta, codigo;
    bool verificaCodigo = false;
    FILE *arquivo;
    Comprador compradores[MAX_TAMANHO_COMPRADORES];
    arquivo = fopen("dados_compradores.txt", "a");
    int i = carregarNumeroDeCompradores(compradores);
    printf("Numero de compradores total: %d", i);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    //inserindo dados
    do {
        printf("\n=== CADASTRO DE COMPRADOR %d ===\n", i+1);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Digite o nome do comprador: ");
        fgets(compradores[i].nome, sizeof(compradores[i].nome), stdin);

        // remove o '\n' se estiver presente
        compradores[i].nome[strcspn(compradores[i].nome, "\n")] = 0;

        printf("Digite o CPF do comprador (sem pontos): ");
        fgets(compradores[i].cpf, sizeof(compradores[i].cpf), stdin);

        // remove o '\n' se estiver presente
        compradores[i].cpf[strcspn(compradores[i].cpf, "\n")] = 0;

        printf("Digite o email: ");
        fgets(compradores[i].email, sizeof(compradores[i].email), stdin);

        // remove o '\n' se estiver presente
        compradores[i].email[strcspn(compradores[i].email, "\n")] = 0;

        printf("Digite a Rua: ");
        fgets(compradores[i].endereco.rua, sizeof(compradores[i].endereco.rua), stdin);
        // remove o '\n' se estiver presente
        compradores[i].endereco.rua[strcspn(compradores[i].endereco.rua, "\n")] = 0;

        printf("Digite a Bairro: ");
        fgets(compradores[i].endereco.bairro, sizeof(compradores[i].endereco.bairro), stdin);
        // remove o '\n' se estiver presente
        compradores[i].endereco.bairro[strcspn(compradores[i].endereco.bairro, "\n")] = 0;

        printf("Digite a Cidade: ");
        fgets(compradores[i].endereco.cidade, sizeof(compradores[i].endereco.cidade), stdin);
        // remove o '\n' se estiver presente
        compradores[i].endereco.cidade[strcspn(compradores[i].endereco.cidade, "\n")] = 0;

        printf("Digite a CEP: ");
        fgets(compradores[i].endereco.cep, sizeof(compradores[i].endereco.cep), stdin);
        // remove o '\n' se estiver presente
        compradores[i].endereco.cep[strcspn(compradores[i].endereco.cep, "\n")] = 0;

        printf("Digite a Estado:");
        fgets(compradores[i].endereco.estado, sizeof(compradores[i].endereco.estado), stdin);
        // remove o '\n' se estiver presente
        compradores[i].endereco.estado[strcspn(compradores[i].endereco.estado, "\n")] = 0;

         // Escreve os dados no arquivo
        fprintf(arquivo, "Nome: %s\n", compradores[i].nome);
        fprintf(arquivo, "CPF: %s\n", compradores[i].cpf);
        fprintf(arquivo, "Email: %s\n", compradores[i].email);
        fprintf(arquivo, "Rua: %s\n", compradores[i].endereco.rua);
        fprintf(arquivo, "Bairro: %s\n", compradores[i].endereco.bairro);
        fprintf(arquivo, "Cidade: %s\n", compradores[i].endereco.cidade);
        fprintf(arquivo, "Estado: %s\n", compradores[i].endereco.estado);
        fprintf(arquivo, "CEP: %s\n", compradores[i].endereco.cep);

        i++;
        printf("\nQuer cadastrar mais compradores? SIM=1 NAO=2: ");
        scanf("%d", &resposta);

    }while(resposta == 1);

    // fecha o arquivo
    fclose(arquivo);
}

void consultarTodosCompradores(){
    char nome[MAX_TAMANHO_NOME], cpf[MAX_TAMANHO_CPF], email[MAX_TAMANHO_EMAIL];
    char rua[MAX_TAMANHO_RUA], bairro[MAX_TAMANHO_BAIRRO], cidade[MAX_TAMANHO_CIDADE], estado[MAX_TAMANHO_ESTADO], cep[MAX_TAMANHO_CEP];
    Endereco endereco[1];
    int codigoArquivo, quantidade;
    float preco;

    FILE *arquivo = fopen("dados_compradores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ;
    };

    // %[^\n] tudo menos o \n
     while (fscanf(arquivo, "Nome: %[^\n]\n", nome) == 1 &&
        fscanf(arquivo, "CPF: %[^\n]\n", cpf) == 1 &&
        fscanf(arquivo, "Email: %[^\n]\n", email) == 1 &&
        fscanf(arquivo, "Rua: %[^\n]\n", rua) == 1 &&
        fscanf(arquivo, "Bairro: %[^\n]\n", bairro) == 1 &&
        fscanf(arquivo, "Cidade: %[^\n]\n", cidade) == 1 &&
        fscanf(arquivo, "Estado: %[^\n]\n", estado) == 1 &&
        fscanf(arquivo, "CEP: %[^\n]\n", cep) == 1) {
        printf("Nome: %s\n", nome);
        printf("CPF: %s\n", cpf);
        printf("Email: %s\n", email);
        printf("Rua: R$ %s\n", rua);
        printf("Bairro: %s\n", bairro);
        printf("Cidade: %s\n", cidade);
        printf("Estado: %s\n", estado);
        printf("CEP: %s\n", cep);
        printf("---------------------------\n");
    }
    fclose(arquivo);
}

void alterarCompradores() {
    char nomePesquisado[MAX_TAMANHO_NOME];
    bool compradorEncontrado = false;
    int total = 0, i=0;
    Comprador tempComprador;
    Comprador comprador;
    FILE *arquivo, *temp_compradores;
    arquivo = fopen("dados_compradores.txt", "r");
    temp_compradores = fopen("temp_compradores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("Informe o nome do comprador que deseja editar: ");

    // limpa o buffer antes de fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    fgets(nomePesquisado, sizeof(nomePesquisado), stdin);
    // remove o '\n' se estiver presente
    nomePesquisado[strcspn(nomePesquisado, "\n")] = 0;

    while (fscanf(arquivo, "Nome: %[^\n]\n", tempComprador.nome) == 1 &&
            fscanf(arquivo, "CPF: %[^\n]\n", tempComprador.cpf) == 1 &&
            fscanf(arquivo, "Email: %[^\n]\n", tempComprador.email) == 1 &&
            fscanf(arquivo, "Rua: %[^\n]\n", tempComprador.endereco.rua) == 1 &&
            fscanf(arquivo, "Bairro: %[^\n]\n", tempComprador.endereco.bairro) == 1 &&
            fscanf(arquivo, "Cidade: %[^\n]\n", tempComprador.endereco.cidade) == 1 &&
            fscanf(arquivo, "Estado: %[^\n]\n", tempComprador.endereco.estado) == 1 &&
            fscanf(arquivo, "CEP: %[^\n]\n", tempComprador.endereco.cep) == 1 ) {
        if (strcmp(nomePesquisado, tempComprador.nome) == 0) {
            compradorEncontrado = true;
            // mostrar dados atuais
            printf("Comprador Encontrado!\n");
            printf("Nome: %s\n", tempComprador.nome);
            printf("CPF: %s\n", tempComprador.cpf);
            printf("Email: %s\n", tempComprador.email);
            printf("Rua: %s\n", tempComprador.endereco.rua);
            printf("Bairro: %s\n", tempComprador.endereco.bairro);
            printf("Cidade: %s\n", tempComprador.endereco.cidade);
            printf("CEP: %s\n", tempComprador.endereco.cep);
            printf("Estado: %s\n", tempComprador.endereco.estado);

            // pega os novos dados do comprador encontrado
            printf("Digite o nome: ");
            fgets(comprador.nome, sizeof(comprador.nome), stdin);
            // remove o '\n' se estiver presente
            comprador.nome[strcspn(comprador.nome, "\n")] = 0;
            printf("Digite o CPF do comprador (sem pontos): ");
            fgets(comprador.cpf, sizeof(comprador.cpf), stdin);
            // remove o '\n' se estiver presente
            comprador.cpf[strcspn(comprador.cpf, "\n")] = 0;


            printf("Digite o email: ");
            fgets(comprador.email, sizeof(comprador.email), stdin);
            // remove o '\n' se estiver presente
            comprador.email[strcspn(comprador.email, "\n")] = 0;

            printf("Digite a Rua: ");
            fgets(comprador.endereco.rua, sizeof(comprador.endereco.rua), stdin);
            // remove o '\n' se estiver presente
            comprador.endereco.rua[strcspn(comprador.endereco.rua, "\n")] = 0;

            printf("Digite a Bairro: ");
            fgets(comprador.endereco.bairro, sizeof(comprador.endereco.bairro), stdin);
            // remove o '\n' se estiver presente
            comprador.endereco.bairro[strcspn(comprador.endereco.bairro, "\n")] = 0;

            printf("Digite a Cidade: ");
            fgets(comprador.endereco.cidade, sizeof(comprador.endereco.cidade), stdin);
            // remove o '\n' se estiver presente
            comprador.endereco.cidade[strcspn(comprador.endereco.cidade, "\n")] = 0;

            printf("Digite a CEP: ");
            fgets(comprador.endereco.cep, sizeof(comprador.endereco.cep), stdin);
            // remove o '\n' se estiver presente
            comprador.endereco.cep[strcspn(comprador.endereco.cep, "\n")] = 0;

            printf("Digite a Estado:");
            fgets(comprador.endereco.estado, sizeof(comprador.endereco.estado), stdin);
            // remove o '\n' se estiver presente
            comprador.endereco.estado[strcspn(comprador.endereco.estado, "\n")] = 0;
            fprintf(temp_compradores, "Nome: %s\n", comprador.nome);
            fprintf(temp_compradores, "CPF: %s\n", comprador.cpf);
            fprintf(temp_compradores, "Email: %s\n", comprador.email);
            fprintf(temp_compradores, "Rua: %s\n", comprador.endereco.rua);
            fprintf(temp_compradores, "Bairro: %s\n", comprador.endereco.bairro);
            fprintf(temp_compradores, "Cidade: %s\n", comprador.endereco.cidade);
            fprintf(temp_compradores, "Estado: %s\n", comprador.endereco.estado);
            fprintf(temp_compradores, "CEP: %s\n", comprador.endereco.cep);
            break;
        } else {
            fprintf(temp_compradores, "Nome: %s\n", tempComprador.nome);
            fprintf(temp_compradores, "CPF: %s\n", tempComprador.cpf);
            fprintf(temp_compradores, "Email: %s\n", tempComprador.email);
            fprintf(temp_compradores, "Rua: %s\n", tempComprador.endereco.rua);
            fprintf(temp_compradores, "Bairro: %s\n", tempComprador.endereco.bairro);
            fprintf(temp_compradores, "Cidade: %s\n", tempComprador.endereco.cidade);
            fprintf(temp_compradores, "Estado: %s\n", tempComprador.endereco.estado);
            fprintf(temp_compradores, "CEP: %s\n", tempComprador.endereco.cep);
        }
    }

    fclose(arquivo);
    fclose(temp_compradores);
    if (compradorEncontrado) {
        // substitui o arquivo original pelo arquivo temporário
        remove("dados_compradores.txt");
        rename("temp_compradores.txt", "dados_compradores.txt");
        printf("\nComprador alterado com sucesso!\n");
    } else {
        remove("temp_compradores.txt");
        printf("\nComprador nao encontrado!.\n");
    }
    printf("Comprador alterado.\n");
}

void excluirComprador(){
    char nomePesquisado[MAX_TAMANHO_NOME];
    bool compradorEncontrado = false;
    int total = 0, i=0;
    Comprador tempComprador;
    Comprador comprador;
    FILE *arquivo, *temp_compradores;
    arquivo = fopen("dados_compradores.txt", "r");
    temp_compradores = fopen("temp_compradores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("Informe o nome do comprador que deseja excluir: ");

    // limpa o buffer antes de fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    fgets(nomePesquisado, sizeof(nomePesquisado), stdin);
    // remove o '\n' se estiver presente
    nomePesquisado[strcspn(nomePesquisado, "\n")] = 0;

    while (fscanf(arquivo, "Nome: %[^\n]\n", tempComprador.nome) == 1 &&
            fscanf(arquivo, "CPF: %[^\n]\n", tempComprador.cpf) == 1 &&
            fscanf(arquivo, "Email: %[^\n]\n", tempComprador.email) == 1 &&
            fscanf(arquivo, "Rua: %[^\n]\n", tempComprador.endereco.rua) == 1 &&
            fscanf(arquivo, "Bairro: %[^\n]\n", tempComprador.endereco.bairro) == 1 &&
            fscanf(arquivo, "Cidade: %[^\n]\n", tempComprador.endereco.cidade) == 1 &&
            fscanf(arquivo, "Estado: %[^\n]\n", tempComprador.endereco.estado) == 1 &&
            fscanf(arquivo, "CEP: %[^\n]\n", tempComprador.endereco.cep) == 1 ) {
        if (!(strcmp(nomePesquisado, tempComprador.nome) == 0)) {
            fprintf(temp_compradores, "Nome: %s\n", tempComprador.nome);
            fprintf(temp_compradores, "CPF: %s\n", tempComprador.cpf);
            fprintf(temp_compradores, "Email: %s\n", tempComprador.email);
            fprintf(temp_compradores, "Rua: %s\n", tempComprador.endereco.rua);
            fprintf(temp_compradores, "Bairro: %s\n", tempComprador.endereco.bairro);
            fprintf(temp_compradores, "Cidade: %s\n", tempComprador.endereco.cidade);
            fprintf(temp_compradores, "Estado: %s\n", tempComprador.endereco.estado);
            fprintf(temp_compradores, "CEP: %s\n", tempComprador.endereco.cep);
            break;
        } else {
            // mostrar dados atuais
            printf("Comprador Encontrado!\n");
            printf("Nome: %s\n", tempComprador.nome);
            printf("CPF: %s\n", tempComprador.cpf);
            printf("Email: %s\n", tempComprador.email);
            printf("Rua: %s\n", tempComprador.endereco.rua);
            printf("Bairro: %s\n", tempComprador.endereco.bairro);
            printf("Cidade: %s\n", tempComprador.endereco.cidade);
            printf("CEP: %s\n", tempComprador.endereco.cep);
            printf("Estado: %s\n", tempComprador.endereco.estado);
            compradorEncontrado = true;
        }
    }

    fclose(arquivo);
    fclose(temp_compradores);
    if (compradorEncontrado) {
        // substitui o arquivo original pelo arquivo temporário
        remove("dados_compradores.txt");
        rename("temp_compradores.txt", "dados_compradores.txt");
        printf("\nComprador excluido com sucesso!\n");
    } else {
        remove("temp_compradores.txt");
        printf("\nComprador nao encontrado!.\n");
    }
}

/* * * * * * * * * * * * * * * * * * *
*    Funções do CRUD dos Produtos  *
* * * * * * * * * * * * * * * * * * */

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
        return;
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
        return;
    }

    // fecha o arquivo
    fclose(arquivo);
}

/* * * * * * * * * * * * * * * * * * *
*   Funções do CRUD dos Vendedores   *
* * * * * * * * * * * * * * * * * * */

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

/* * * * * * * * * * * * * * * * * * *
*     Funções do CRUD das Vendas     *
* * * * * * * * * * * * * * * * * * */

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

void emitirNotaFiscal() {
    char cpfComprador[15];

    printf("Digite o CPF do comprador: ");
    scanf("%s", cpfComprador);

    Comprador comprador;
    bool compradorEncontrado = false;

    FILE *arquivoComprador = fopen("dados_compradores.txt", "r");
    if (!arquivoComprador) {
        printf("Erro ao abrir arquivo de compradores.\n");
        return;
    }

    while (fscanf(arquivoComprador, "Nome: %[^\n]\nCPF: %[^\n]\nEmail: %[^\n]\nEndereco: %[^\n]\n",
                  comprador.nome, comprador.cpf, comprador.email, comprador.endereco) == 4) {
        if (strcmp(comprador.cpf, cpfComprador) == 0) {
            compradorEncontrado = true;
            break;
        }
    }
    fclose(arquivoComprador);

    if (!compradorEncontrado) {
        printf("Comprador nao encontrado.\n");
        return;
    }

    FILE *arquivoNota = fopen("nota_fiscal.txt", "w");
    if (!arquivoNota) {
        printf("Erro ao criar arquivo da nota fiscal.\n");
        return;
    }

    fprintf(arquivoNota, "=== NOTA FISCAL ===\n\n");
    fprintf(arquivoNota, "Dados do Comprador:\n");
    fprintf(arquivoNota, "Nome: %s\nCPF: %s\nEmail: %s\nEndereco: %s\n\n",
            comprador.nome, comprador.cpf, comprador.email, comprador.endereco);

    int qtdProdutos;
    printf("Informe quantos produtos deseja adicionar na nota: ");
    scanf("%d", &qtdProdutos);

    float total = 0;
    fprintf(arquivoNota, "Produtos comprados:\nDescricao - Qtd - Preco Unitario - Subtotal\n");

    for (int i = 0; i < qtdProdutos; i++) {
        int codigo, quantidade;
        printf("Produto %d:\n", i + 1);
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);
        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);

        FILE *arquivoProdutos = fopen("dados_produtos.txt", "r");
        if (!arquivoProdutos) {
            printf("Erro ao abrir arquivo de produtos.\n");
            fclose(arquivoNota);
            return;
        }

        Produtos produto;
        bool produtoEncontrado = false;
        while (fscanf(arquivoProdutos, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n",
                      produto.nome, &produto.codigo, &produto.quantidadeEstoque, &produto.preco) == 4) {
            if (produto.codigo == codigo) {
                produtoEncontrado = true;
                break;
            }
        }
        fclose(arquivoProdutos);

        if (!produtoEncontrado) {
            printf("Produto com codigo %d nao encontrado. Ignorando.\n", codigo);
            continue;
        }

        float subtotal = quantidade * produto.preco;
        total += subtotal;
        fprintf(arquivoNota, "%s - %d - R$ %.2f - R$ %.2f\n", produto.nome, quantidade, produto.preco, subtotal);
    }

    // Calcula o frete com base no total da compra
    int frete = 0;
    if (total > 300) {
        freteAcimaTrezentos(total);
        frete = 0;
    } else if (total > 100) {
        freteAteTrezentosReais(total);
        frete = 20;
    } else {
        freteAteCemReais(total);
        frete = 30;
    }

    // Exibe e grava o frete na nota
    fprintf(arquivoNota, "\nFrete: R$ %d\n", frete);
    fprintf(arquivoNota, "Total com frete: R$ %.2f\n", total + frete);
    fclose(arquivoNota);

    printf("Nota fiscal gerada com sucesso no arquivo nota_fiscal.txt\n");
}
// Declarando Menu
void menuVendedores(){
    int opcao;
    do {
        printf("\n=== CRUD VENDEDORES ===\n");
        printf("1. Cadastrar\n2. Listar\n3. Alterar\n4. Excluir\n5. Voltando para o Menu Principal...\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarVendedor(); break;
            case 2: listarVendedores(); break;
            case 3: alterarVendedor(); break;
            case 4: excluirVendedor(); break;
        }
    } while (opcao != 5);
}
void menuCompradores(){
    int opcao = 0;
    do {
        printf("-------------------------------------\n");
        printf("|          MENU COMPRADORES          |\n");
        printf("| 1- Cadastrar Compradores           |\n");
        printf("| 2- Consultar Compradores           |\n");
        printf("| 3- Alterar Compradores             |\n");
        printf("| 4- Excluir Compradores             |\n");
        printf("| 5- Voltar para o menu principal    |\n");
        printf("-------------------------------------\n");
        printf("Digite o numero da operacao que deseja realizar:\n");
        scanf("%d",&opcao);
        switch (opcao) {
                case 1:
                    cadastrarCompradores();
                    break;
                case 2:
                    consultarTodosCompradores();
                    break;
                case 3:
                    alterarProdutos();
                    break;
                case 4:
                    excluirComprador();
                    break;
                case 5:
                    printf("Voltar ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                    break;

        };
    }while (opcao != 5);
}
void menuProdutos(){
    int opcao = 0;
    do {
        printf("----------------------------------\n");
        printf("|         MENU PRODUTOS           |\n");
        printf("| 1- Cadastrar Produtos           |\n");
        printf("| 2- Consultar Produtos Por Codigo|\n");
        printf("| 3- Consultar Todos Produtos     |\n");
        printf("| 4- Alterar Produtos             |\n");
        printf("| 5- Excluir Produtos             |\n");
        printf("| 6- Voltar ao menu principal     |\n");
        printf("----------------------------------\n");
        printf("Digite o numero da operacao que deseja realizar:\n");
        scanf("%d", &opcao);

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
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
}

void menuVendas(){
    int opcao;
    do {
        printf("\n=== CRUD VENDAS ===\n");
        printf("1. Cadastrar Venda\n2. Listar Vendas\n3. Alterar Venda\n4. Excluir Venda\n5. Voltando para o Menu Principal\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarVenda(); break;
            case 2: listarVendas(); break;
            case 3: alterarVenda(); break;
            case 4: excluirVenda(); break;
        }
    } while (opcao != 5);
}

/* * * * * * * * * * * * * * * * * * *
*       Programa Principal           *
* * * * * * * * * * * * * * * * * * */

int main(int argc, char **argv) {
    int opcao = 0;
    do {
        printf("----------------------------------\n");
        printf("|         MENU PRINCIPAL         |\n");
        printf("| 1- Produtos                    |\n");
        printf("| 2- Compradores                 |\n");
        printf("| 3- Vendedores                  |\n");
        printf("| 4- Vendas                      |\n");
        printf("| 5- Nota Fiscal                 |\n");
        printf("| 6- SAIR                        |\n");
        printf("----------------------------------\n");
        printf("Digite o numero da operacao que deseja realizar:\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuProdutos();
                break;
            case 2:
                menuCompradores();
                break;
            case 3:
                menuVendedores();
                break;
            case 4:
                menuVendas();
                break;
            case 5:
                emitirNotaFiscal();
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    return SUCESSO;
}
