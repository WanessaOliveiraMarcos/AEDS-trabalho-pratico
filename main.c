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
*               veira Gandra, Marco Túlio Sales de Deus e
                Mirna dos Reis Arcanjo
* START DATE  : 22 de Julho de 2025
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_TAMANHO_PRODUTOS 100
#define MAX_TAMANHO_COMPRADORES 100
#define MAX_TAMANHO_RUA      100
#define MAX_TAMANHO_BAIRRO   50
#define MAX_TAMANHO_CIDADE   50
#define MAX_TAMANHO_ESTADO   3
#define MAX_TAMANHO_CEP      9
#define MAX_TAMANHO_NOME     100
#define MAX_TAMANHO_CPF      50
#define MAX_TAMANHO_EMAIL    100
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
    int codigo;
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
    int codigoProduto;
    int quantidadeVendida;
    float precoUnitario;
    float subtotal;
} ProdutoVenda;

typedef struct {
    int numeroVenda;
    int numeroVendedor;
    int codigoComprador;
    char data[11]; // "dd/mm/aaaa"
    ProdutoVenda *produtos;
    int quantidadeTotalProdutos;
    int capacidadeItens;
    float valorTotal;
} Venda;


/* * * * * * * * * * * * * * * * * * * *
*       Declaração das Funções         *
* * * * * * * * * * * * * * * * * * * */

 int freteAteCemReais(float valorCompra){
     int frete=30;
     printf("\n----------------\n");
     printf("Frete = R$%d",frete);
     printf("\n----------------\n");
     return 0;
}
int freteAteTrezentosReais(float valorCompra){
    int frete=20;
    printf("\n----------------\n");
    printf("Frete = R$%d",frete);
    printf("\n----------------\n");
    return 0;
}
 int freteAcimaTrezentos(float valorCompra){
    int frete=0;
    printf("\n----------------\n");
    printf("Frete = R$%d",frete);
    printf("\n----------------\n");
    return 0;
}
bool verificarCodigoProduto(int codigo, Produtos *produtos) {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    char nome[MAX_TAMANHO_NOME];
    int codigoArquivo, quantidade;
    float preco;
    int i = 0;

    while (fscanf(arquivo, " Nome: %49[^\n]\n", nome) == 1 &&
           fscanf(arquivo, " Codigo: %d\n", &codigoArquivo) == 1 &&
           fscanf(arquivo, " Quantidade: %d\n", &quantidade) == 1 &&
           fscanf(arquivo, " Preco: %f\n", &preco) == 1) {

        if (codigoArquivo == codigo) {
            strcpy(produtos->nome, nome);
            produtos->codigo = codigoArquivo;
            produtos->quantidadeEstoque = quantidade;
            produtos->preco = preco;

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
bool verificarCodigoComprador(int codigo, Comprador *compradores) {
    FILE *arquivo = fopen("dados_compradores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    char nome[MAX_TAMANHO_NOME];
    int codigoArquivo, quantidade;
    float preco;
    int i = 0;

    while (fscanf(arquivo, "Nome: %s\n", compradores[i].nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &compradores[i].codigo) == 1 &&
           fscanf(arquivo, "CPF: %s\n", compradores[i].cpf) == 1 &&
           fscanf(arquivo, "Email: %s\n", compradores[i].email) == 1 &&
           fscanf(arquivo, "Rua: %s\n", compradores[i].endereco.rua) == 1 &&
           fscanf(arquivo, "Bairro: %s\n", compradores[i].endereco.bairro) == 1 &&
           fscanf(arquivo, "Cidade: %s\n", compradores[i].endereco.cidade) == 1 &&
           fscanf(arquivo, "Estado: %s\n", compradores[i].endereco.estado) == 1 &&
           fscanf(arquivo, "CEP: %s\n", compradores[i].endereco.cep) == 1) {

        if (codigoArquivo == codigo) {
            printf("\nComprador encontrado!");
            fclose(arquivo);
            return true;
        }
        i++;
    }

    fclose(arquivo);
    return false;
}

float obterPrecoProduto(int codigo) {
    Produtos produtos[MAX_TAMANHO_PRODUTOS];
    int numProdutos = carregarProdutos(produtos);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].preco;
        }
    }

    return -1.0f;
}
bool verificarEstoque(int codigo, int quantidadeDesejada) {
    Produtos produtos[MAX_TAMANHO_PRODUTOS];
    int numProdutos = carregarProdutos(produtos);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            if (produtos[i].quantidadeEstoque >= quantidadeDesejada) {
                return true;
            } else {
                printf("Estoque insuficiente! Disponível: %d\n", produtos[i].quantidadeEstoque);
                return false;
            }
        }
    }

    printf("Produto com código %d não encontrado!\n", codigo);
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
    return i;
}

int verificaNumeroVendedor(int numeroVendedor){
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    Vendedor temp;
    bool vendedorExiste = false;
    if (arquivo == NULL) return 0;
    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", temp.nome, &temp.numero, &temp.salario, &temp.comissao) != EOF) {
        if (temp.numero == numeroVendedor) {
            vendedorExiste = true;
            break;
        }
    }
    fclose(arquivo);
    if(vendedorExiste == true){
        return 1;
    } else {
        return 0;
    }
}

int verificaNumeroComprador(int numeroComprador){
    FILE *arquivo = fopen("dados_compradores.txt", "r");
    Comprador temp;
    bool compradorExiste = false;
    if (arquivo == NULL) return 0;
    while (fscanf(arquivo, "Nome: %[^\n]\nCodigo: %d\nCPF: %[^\n]\nEmail: %[^\n]\nRua: %[^\n]\nBairro: %[^\n]\nCidade: %[^\n]\nEstado: %[^\n]\nCEP: %[^\n]\n",
              temp.nome, &temp.codigo, temp.cpf, temp.email,
              temp.endereco.rua, temp.endereco.bairro,
              temp.endereco.cidade, temp.endereco.estado,
              temp.endereco.cep) !=EOF) {
        if (temp.codigo == numeroComprador) {
            compradorExiste = true;
            break;
        }
    }
    fclose(arquivo);
    if(compradorExiste == true){
        return 1;
    } else {
        return 0;
    }
}

int verificarCamposCompradores(Comprador *comprador){
    if (strlen(comprador->nome) == 0) {
        printf("Campo 'nome' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->cpf) == 0) {
        printf("Campo 'cpf' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->email) == 0) {
        printf("Campo 'email' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->endereco.rua) == 0) {
        printf("Campo 'rua' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->endereco.bairro) == 0) {
        printf("\nCampo 'bairro' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->endereco.cidade) == 0) {
        printf("\nCampo 'cidade' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->endereco.estado) == 0) {
        printf("\nCampo 'estado' nao esta preenchido\n");
        return 0;
    }

    if (strlen(comprador->endereco.cep) == 0) {
        printf("\nCampo 'cep' nao esta preenchido\n");
        return 0;
    }
    return 1;
}
int verificarCamposProdutos(Produtos *produto){
    if (strlen(produto->nome) == 0) {
        printf("Campo 'nome' nao esta preenchido\n");
        return 0;
    }

    if (produto->quantidadeEstoque < 0) {
        printf("Campo 'quantidade estoque' nao pode ser negativo\n");
        return 0;
    }

    if (produto->preco < 0) {
        printf("Campo 'preco' nao pode ser negativo\n");
        return 0;
    }

    return 1;
}

int verificarCamposVendedores(Vendedor *vendedor){
    if (strlen(vendedor->nome) == 0) {
        printf("Campo 'nome' nao esta preenchido\n");
        return 0;
    }

    if (vendedor->numero < 0) {
        printf("Campo 'numero' nao pode ser negativo\n");
        return 0;
    }

    if (vendedor->salario < 0) {
        printf("Campo 'salario' nao pode ser negativo\n");
        return 0;
    }

    if (vendedor->comissao < 0) {
        printf("Campo 'comissao' nao pode ser negativo\n");
        return 0;
    }
    return 1;
}

int verificarCamposVendas(Venda *venda) {
    if (strlen(venda->data) != 10 || venda->data[2] != '/' || venda->data[5] != '/') {
        printf("Formato de data inválido. Use dd/mm/aaaa\n");
        return 0;
    }

    if (venda->numeroVendedor <= 0) {
        printf("Número do vendedor deve ser positivo\n");
        return 0;
    }

    if (venda->numeroVenda <= 0) {
        printf("Número da venda deve ser positivo\n");
        return 0;
    }

    if (venda->codigoComprador <= 0) {
        printf("Código do comprador deve ser positivo\n");
        return 0;
    }

    if (venda->valorTotal <= 0) {
        printf("Valor total da venda deve ser positivo\n");
        return 0;
    }

    if (venda->quantidadeTotalProdutos <= 0) {
        printf("A venda deve conter pelo menos um produto\n");
        return 0;
    }

    for (int i = 0; i < venda->quantidadeTotalProdutos; i++) {
        if (venda->produtos[i].quantidadeVendida <= 0) {
            printf("Quantidade do produto %d deve ser positiva\n", venda->produtos[i].codigoProduto);
            return 0;
        }

        if (venda->produtos[i].precoUnitario <= 0) {
            printf("Preço unitário do produto %d deve ser positivo\n", venda->produtos[i].codigoProduto);
            return 0;
        }

        float subtotal_calculado = venda->produtos[i].precoUnitario * venda->produtos[i].quantidadeVendida;
        if (fabs(venda->produtos[i].subtotal - subtotal_calculado) > 0.01) {
            printf("Subtotal inconsistente para o produto %d\n", venda->produtos[i].codigoProduto);
            return 0;
        }
    }

    return 1;
}

/* * * * * * * * * * * * * * * * * * *
*  Funções do CRUD dos Compradores   *
* * * * * * * * * * * * * * * * * * */
int obterDadosCompradores() {
    int resposta, codigo;
    FILE *arquivo;
    Comprador compradores[MAX_TAMANHO_COMPRADORES];
    bool verificaCodigo = false;
    arquivo = fopen("dados_compradores.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int i = carregarNumeroDeCompradores(compradores);
    if (i == -1) {
        fclose(arquivo);
        return 1;
    }

   //inserindo dados
    do {
        printf("\n=== CADASTRO DE COMPRADOR %d ===\n", i+1);
        // gera o código do comprador e verifica se o código gerado já está cadastrado
        do {
            codigo = CodigoAleatorio();
            verificaCodigo = verificarCodigoComprador(codigo, compradores);
        }while(verificaCodigo == true);
        compradores[i].codigo = codigo;
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


        if (verificarCamposCompradores(&compradores[i])) {
            if (cadastrarCompradores(&compradores[i]) == 0) {
                printf("\nComprador cadastrado com sucesso!\n");
            } else {
                printf("\nErro ao salvar o comprador.\n");
            }
        } else {
            printf("\nComprador não cadastrado. Dados inválidos.\n");
        }
        printf("\nQuer cadastrar mais compradores? SIM=1 NAO=2: ");
        scanf("%d", &resposta);

    }while(resposta == 1);

    fclose(arquivo);
    return 0;
}
int cadastrarCompradores(Comprador *comprador){
    int resposta, codigo;
    bool verificaCodigo = false;
    Comprador compradores[MAX_TAMANHO_COMPRADORES];
    FILE *arquivo;
    arquivo = fopen("dados_compradores.txt", "a");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(arquivo, "Nome: %s\n", comprador->nome);
    fprintf(arquivo, "Codigo: %d\n", comprador->codigo);
    fprintf(arquivo, "CPF: %s\n", comprador->cpf);
    fprintf(arquivo, "Email: %s\n", comprador->email);
    fprintf(arquivo, "Rua: %s\n", comprador->endereco.rua);
    fprintf(arquivo, "Bairro: %s\n", comprador->endereco.bairro);
    fprintf(arquivo, "Cidade: %s\n", comprador->endereco.cidade);
    fprintf(arquivo, "Estado: %s\n", comprador->endereco.estado);
    fprintf(arquivo, "CEP: %s\n", comprador->endereco.cep);

    fclose(arquivo);
    return 0;
}
int consultarCompradorPorCodigo(int codigo){
    bool compradorEncontrado = false;
    Comprador comprador;

    FILE *arquivo = fopen("dados_compradores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    };
    while (fscanf(arquivo, "Nome: %s\n", comprador.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &comprador.codigo) == 1 &&
           fscanf(arquivo, "CPF: %s\n", comprador.cpf) == 1 &&
           fscanf(arquivo, "Email: %s\n", comprador.email) == 1 &&
           fscanf(arquivo, "Rua: %s\n", comprador.endereco.rua) == 1 &&
           fscanf(arquivo, "Bairro: %s\n", comprador.endereco.bairro) == 1 &&
           fscanf(arquivo, "Cidade: %s\n", comprador.endereco.cidade) == 1 &&
           fscanf(arquivo, "Estado: %s\n", comprador.endereco.estado) == 1 &&
           fscanf(arquivo, "CEP: %s\n", comprador.endereco.cep) == 1 ){

        if (comprador.codigo == codigo) {
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", comprador.nome);
            printf("Código: %d\n", comprador.codigo);
            printf("CPF: %s\n", comprador.cpf);
            printf("Email: %s\n", comprador.email);
            printf("Rua: %s\n", comprador.endereco.rua);
            printf("Bairro: %s\n", comprador.endereco.bairro);
            printf("Cidade: %s\n", comprador.endereco.cidade);
            printf("Estado: %s\n", comprador.endereco.estado);
            printf("CEP: %s\n", comprador.endereco.cep);

            compradorEncontrado = true;
            break;
        }
    }
    fclose(arquivo);
    if(!compradorEncontrado){
      printf("Código %d não encontrado!\n", codigo);
    }
    return 0;
}

int consultarTodosCompradores(){
    char nome[MAX_TAMANHO_NOME], cpf[MAX_TAMANHO_CPF], email[MAX_TAMANHO_EMAIL];
    char rua[MAX_TAMANHO_RUA], bairro[MAX_TAMANHO_BAIRRO], cidade[MAX_TAMANHO_CIDADE], estado[MAX_TAMANHO_ESTADO], cep[MAX_TAMANHO_CEP];
    Endereco endereco[1];
    int codigoArquivo, quantidade, codigo;
    float preco;

    FILE *arquivo = fopen("dados_compradores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    };

     while (fscanf(arquivo, "Nome: %[^\n]\n", nome) == 1 &&
        fscanf(arquivo, "Codigo: %[^\n]\n", &codigo) == 1 &&
        fscanf(arquivo, "CPF: %[^\n]\n", cpf) == 1 &&
        fscanf(arquivo, "Email: %[^\n]\n", email) == 1 &&
        fscanf(arquivo, "Rua: %[^\n]\n", rua) == 1 &&
        fscanf(arquivo, "Bairro: %[^\n]\n", bairro) == 1 &&
        fscanf(arquivo, "Cidade: %[^\n]\n", cidade) == 1 &&
        fscanf(arquivo, "Estado: %[^\n]\n", estado) == 1 &&
        fscanf(arquivo, "CEP: %[^\n]\n", cep) == 1) {
        printf("Nome: %s\n", nome);
        printf("Codigo: %d\n", codigo);
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
    return 0;
}

int alterarCompradores(int codigoPesquisado) {
    bool compradorEncontrado = false;
    int total = 0, i=0;
    Comprador tempComprador;
    Comprador comprador;
    FILE *arquivo, *temp_compradores;
    arquivo = fopen("dados_compradores.txt", "r");
    temp_compradores = fopen("temp_compradores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fscanf(arquivo, "Nome: %[^\n]\n", tempComprador.nome) == 1 &&
            fscanf(arquivo, "Codigo: %[^\n]\n", &tempComprador.codigo) == 1 &&
            fscanf(arquivo, "CPF: %[^\n]\n", tempComprador.cpf) == 1 &&
            fscanf(arquivo, "Email: %[^\n]\n", tempComprador.email) == 1 &&
            fscanf(arquivo, "Rua: %[^\n]\n", tempComprador.endereco.rua) == 1 &&
            fscanf(arquivo, "Bairro: %[^\n]\n", tempComprador.endereco.bairro) == 1 &&
            fscanf(arquivo, "Cidade: %[^\n]\n", tempComprador.endereco.cidade) == 1 &&
            fscanf(arquivo, "Estado: %[^\n]\n", tempComprador.endereco.estado) == 1 &&
            fscanf(arquivo, "CEP: %[^\n]\n", tempComprador.endereco.cep) == 1 ) {
        if (codigoPesquisado == tempComprador.codigo) {
            compradorEncontrado = true;
            printf("Comprador Encontrado!\n");
            printf("Nome: %s\n", tempComprador.nome);
            printf("Codigo: %s\n", tempComprador.codigo);
            printf("CPF: %s\n", tempComprador.cpf);
            printf("Email: %s\n", tempComprador.email);
            printf("Rua: %s\n", tempComprador.endereco.rua);
            printf("Bairro: %s\n", tempComprador.endereco.bairro);
            printf("Cidade: %s\n", tempComprador.endereco.cidade);
            printf("CEP: %s\n", tempComprador.endereco.cep);
            printf("Estado: %s\n", tempComprador.endereco.estado);

            printf("Digite o nome: ");
            fgets(comprador.nome, sizeof(comprador.nome), stdin);
            comprador.nome[strcspn(comprador.nome, "\n")] = 0;
            printf("Digite o CPF do comprador (sem pontos): ");
            fgets(comprador.cpf, sizeof(comprador.cpf), stdin);
            comprador.cpf[strcspn(comprador.cpf, "\n")] = 0;

            printf("Digite o email: ");
            fgets(comprador.email, sizeof(comprador.email), stdin);
            comprador.email[strcspn(comprador.email, "\n")] = 0;

            printf("Digite a Rua: ");
            fgets(comprador.endereco.rua, sizeof(comprador.endereco.rua), stdin);
            comprador.endereco.rua[strcspn(comprador.endereco.rua, "\n")] = 0;

            printf("Digite a Bairro: ");
            fgets(comprador.endereco.bairro, sizeof(comprador.endereco.bairro), stdin);
            comprador.endereco.bairro[strcspn(comprador.endereco.bairro, "\n")] = 0;

            printf("Digite a Cidade: ");
            fgets(comprador.endereco.cidade, sizeof(comprador.endereco.cidade), stdin);
            comprador.endereco.cidade[strcspn(comprador.endereco.cidade, "\n")] = 0;

            printf("Digite a CEP: ");
            fgets(comprador.endereco.cep, sizeof(comprador.endereco.cep), stdin);
            comprador.endereco.cep[strcspn(comprador.endereco.cep, "\n")] = 0;

            printf("Digite a Estado:");
            fgets(comprador.endereco.estado, sizeof(comprador.endereco.estado), stdin);
            comprador.endereco.estado[strcspn(comprador.endereco.estado, "\n")] = 0;
            fprintf(temp_compradores, "Nome: %s\n", comprador.nome);
            fprintf(temp_compradores, "Codigo: %d\n", tempComprador.codigo);
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
            fprintf(temp_compradores, "Codigo: %d\n", tempComprador.codigo);
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
        remove("dados_compradores.txt");
        rename("temp_compradores.txt", "dados_compradores.txt");
        printf("\nComprador alterado com sucesso!\n");
    } else {
        remove("temp_compradores.txt");
        printf("\nComprador nao encontrado!.\n");
    }
    printf("Comprador alterado.\n");
    return 0;
}

int excluirComprador(int codigoPesquisado) {
    bool compradorEncontrado = false;
    int total = 0, i=0;
    Comprador tempComprador;
    Comprador comprador;
    FILE *arquivo, *temp_compradores;
    arquivo = fopen("dados_compradores.txt", "r");
    temp_compradores = fopen("temp_compradores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Informe o codigo do comprador que deseja excluir: ");
    scanf("%d", &codigoPesquisado);

    while (fscanf(arquivo, "Nome: %[^\n]\n", tempComprador.nome) == 1 &&
            fscanf(arquivo, "Codigo: %[^\n]\n", &tempComprador.codigo) == 1 &&
            fscanf(arquivo, "CPF: %[^\n]\n", tempComprador.cpf) == 1 &&
            fscanf(arquivo, "Email: %[^\n]\n", tempComprador.email) == 1 &&
            fscanf(arquivo, "Rua: %[^\n]\n", tempComprador.endereco.rua) == 1 &&
            fscanf(arquivo, "Bairro: %[^\n]\n", tempComprador.endereco.bairro) == 1 &&
            fscanf(arquivo, "Cidade: %[^\n]\n", tempComprador.endereco.cidade) == 1 &&
            fscanf(arquivo, "Estado: %[^\n]\n", tempComprador.endereco.estado) == 1 &&
            fscanf(arquivo, "CEP: %[^\n]\n", tempComprador.endereco.cep) == 1 ) {
        if (codigoPesquisado != tempComprador.codigo) {
            fprintf(temp_compradores, "Nome: %s\n", tempComprador.nome);
            fprintf(temp_compradores, "Codigo: %d\n", tempComprador.codigo);
            fprintf(temp_compradores, "CPF: %s\n", tempComprador.cpf);
            fprintf(temp_compradores, "Email: %s\n", tempComprador.email);
            fprintf(temp_compradores, "Rua: %s\n", tempComprador.endereco.rua);
            fprintf(temp_compradores, "Bairro: %s\n", tempComprador.endereco.bairro);
            fprintf(temp_compradores, "Cidade: %s\n", tempComprador.endereco.cidade);
            fprintf(temp_compradores, "Estado: %s\n", tempComprador.endereco.estado);
            fprintf(temp_compradores, "CEP: %s\n", tempComprador.endereco.cep);
            break;
        } else {
            printf("Comprador Encontrado!\n");
            printf("Nome: %s\n", tempComprador.nome);
            printf("Codigo: %d\n", tempComprador.codigo);
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
        remove("dados_compradores.txt");
        rename("temp_compradores.txt", "dados_compradores.txt");
        printf("\nComprador excluido com sucesso!\n");
    } else {
        remove("temp_compradores.txt");
        printf("\nComprador nao encontrado!.\n");
    }
    return 0;
}

/* * * * * * * * * * * * * * * * * * *
*    Funções do CRUD dos Produtos  *
* * * * * * * * * * * * * * * * * * */

int excluirProduto(int codigo){
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int resposta = 0;
    bool produtoEncontrado = false;
    Produtos produto;
    Produtos tempProduto;
    do {

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fscanf(arquivo, "Nome: %s\n", tempProduto.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &tempProduto.codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &tempProduto.quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &tempProduto.preco) == 1) {

        if (tempProduto.codigo != codigo) {
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
        remove("dados_produtos.txt");
        rename("temp.txt", "dados_produtos.txt");
        printf("\nProduto excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
    printf("\nQuer excluir mais produtos? SIM=1 NAO=2: ");
    scanf("%d", &resposta);
    }while(resposta == 1);
    return 0;
}
int alterarProdutos(int codigo) {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    bool produtoEncontrado = false;
    Produtos produto;
    Produtos tempProduto;

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fscanf(arquivo, "Nome: %s\n", tempProduto.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &tempProduto.codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &tempProduto.quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &tempProduto.preco) == 1) {

        if (tempProduto.codigo == codigo) {
            produtoEncontrado = true;

            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", tempProduto.nome);
            printf("Código: %d\n", tempProduto.codigo);
            printf("Quantidade: %d\n", tempProduto.quantidadeEstoque);
            printf("Preço: R$ %.2f\n", tempProduto.preco);

            printf("\nDigite o novo nome do produto: ");
            scanf("%s", produto.nome);

            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &produto.quantidadeEstoque);

            printf("Digite o novo preço: R$ ");
            scanf("%f", &produto.preco);

            produto.codigo = codigo;

            fprintf(temp, "Nome: %s\n", produto.nome);
            fprintf(temp, "Codigo: %d\n", produto.codigo);
            fprintf(temp, "Quantidade: %d\n", produto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", produto.preco);

        } else {
            fprintf(temp, "Nome: %s\n", tempProduto.nome);
            fprintf(temp, "Codigo: %d\n", tempProduto.codigo);
            fprintf(temp, "Quantidade: %d\n", tempProduto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", tempProduto.preco);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (produtoEncontrado) {
        remove("dados_produtos.txt");
        rename("temp.txt", "dados_produtos.txt");
        printf("\nProduto alterado com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
    return 0;
}
int consultarTodosProdutos(){
    char nome[50];
    int codigoArquivo, quantidade;
    float preco;

    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    };
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
    return 0;
}
int consultarProdutoPorCodigo(int codigo){
    bool produtoEncontrado = false;
    char nome[50];
    int codigoArquivo, quantidade;
    float preco;
    int encontrado = 0;

    FILE *arquivo = fopen("dados_produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
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
            produtoEncontrado = true;
            break;
        }
    }
    fclose(arquivo);
    if(produtoEncontrado == false){
      printf("Código %d não encontrado!\n", codigo);
    }
    return 0;
}
int obterDadosProdutos() {
    Produtos produto;
    int resposta, codigo;
    bool verificaCodigo;

    do {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\n=== CADASTRO DE PRODUTO ===\n");

        printf("Digite o nome do produto: ");
        fgets(produto.nome, sizeof(produto.nome), stdin);
        produto.nome[strcspn(produto.nome, "\n")] = 0;

        printf("Digite a quantidade do produto no estoque: ");
        scanf("%d", &produto.quantidadeEstoque);

        printf("Digite o valor do produto: R$ ");
        scanf("%f", &produto.preco);

        do {
            codigo = CodigoAleatorio();
            verificaCodigo = verificarCodigoProduto(codigo, &produto);
        } while (verificaCodigo == true);

        produto.codigo = codigo;

        if (verificarCamposProdutos(&produto)) {
            if (cadastrarProdutos(&produto) == 0) {
                printf("\nProduto cadastrado com sucesso!\n");
            } else {
                printf("\nErro ao salvar o produto.\n");
            }
        } else {
            printf("\nProduto não cadastrado. Dados inválidos.\n");
        }

        printf("Quer cadastrar mais produtos? SIM=1 NAO=2: ");
        scanf("%d", &resposta);

    } while (resposta == 1);

    return 0;
}


int cadastrarProdutos(Produtos *produto) {
    FILE *arquivo = fopen("dados_produtos.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(arquivo, "Nome: %s\n", produto->nome);
    fprintf(arquivo, "Codigo: %d\n", produto->codigo);
    fprintf(arquivo, "Quantidade: %d\n", produto->quantidadeEstoque);
    fprintf(arquivo, "Preco: %.2f\n", produto->preco);

    fclose(arquivo);
    return 0;
}


/* * * * * * * * * * * * * * * * * * *
*   Funções do CRUD dos Vendedores   *
* * * * * * * * * * * * * * * * * * */

int obterDadosVendedores(){
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "a+");
    if (arquivo == NULL) return 1;

    Vendedor v;

    printf("Número do vendedor: ");
    scanf("%d", &v.numero);
    getchar();

    // Verificar se número já existe
    Vendedor temp;
    while (fscanf(arquivo, "%49[^,],%d,%f,%f\n", temp.nome, &temp.numero, &temp.salario, &temp.comissao) != EOF) {
        if (temp.numero == v.numero) {
            printf("Número já existente.\n");
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);  // Fechar após leitura

    printf("Nome do vendedor: ");
    fgets(v.nome, sizeof(v.nome), stdin);
    v.nome[strcspn(v.nome, "\n")] = 0;  // Remover \n do final

    printf("Salário fixo: ");
    scanf("%f", &v.salario);
    getchar();

    v.comissao = 0;  // Inicializa com 0

    int verificaCampos = verificarCamposVendedores(&v);
    if (verificaCampos == 1) {
        if (cadastrarVendedor(&v) == 0) {
            printf("\nVendedor cadastrado com sucesso!\n");
            return 0;
        } else {
            printf("Erro ao cadastrar o Vendedor!\n");
            return 1;
        }
    } else {
        printf("Não foi possível cadastrar o Vendedor! Campos inválidos.\n");
        return 1;
    }
}

int cadastrarVendedor(Vendedor *vendedor) {
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "a");
    if (arquivo == NULL) return 1;

    fprintf(arquivo, "%s,%d,%.2f,%.2f\n", vendedor->nome, vendedor->numero, vendedor->salario, vendedor->comissao);

    fclose(arquivo);
    return 0;
}

int listarVendedores() {
    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return 1;

    Vendedor v;
    printf("\nLista de Vendedores:\n");
    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", v.nome, &v.numero, &v.salario, &v.comissao) != EOF) {
        printf("Nome: %s | Numero: %d | Salario: %.2f | Comissao: %.2f\n", v.nome, v.numero, v.salario, v.comissao);
    }
    fclose(arquivo);
    return 0;
}

int alterarVendedor(int numero) {
    Vendedor lista[MAX_VENDEDORES];
    int total = 0, encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return 1;

    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", lista[total].nome, &lista[total].numero, &lista[total].salario, &lista[total].comissao) != EOF) {
        total++;
    }
    fclose(arquivo);

    for (int i = 0; i < total; i++) {
        if (lista[i].numero == numero) {
            printf("Novo nome: ");
            fgets(lista[i].nome, 50, stdin);
            lista[i].nome[strcspn(lista[i].nome, "\n")] = 0;
            printf("Novo salario: ");
            scanf("%f", &lista[i].salario);
            getchar();
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Vendedor nao encontrado.\n");
        return 1;
    }

    arquivo = fopen(ARQUIVO_VENDEDORES, "w");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s,%d,%.2f,%.2f\n", lista[i].nome, lista[i].numero, lista[i].salario, lista[i].comissao);
    }
    fclose(arquivo);
    printf("Vendedor alterado.\n");
    return 0;
}

int excluirVendedor(int numero) {
    Vendedor lista[MAX_VENDEDORES];
    int total = 0, encontrado = 0;

    FILE *arquivo = fopen(ARQUIVO_VENDEDORES, "r");
    if (arquivo == NULL) return 1;

    while (fscanf(arquivo, "%[^,],%d,%f,%f\n", lista[total].nome, &lista[total].numero, &lista[total].salario, &lista[total].comissao) != EOF) {
        total++;
    }
    fclose(arquivo);

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
        printf("Vendedor excluido.\n");
    else
        printf("Vendedor nao encontrado.\n");
    return 0;
}

/* * * * * * * * * * * * * * * * * * *
*     Funções do CRUD das Vendas     *
* * * * * * * * * * * * * * * * * * */

int atualizarEstoque(int codigo, int quantidadeVendida) {
    FILE *arquivo = fopen("dados_produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int quantidadeNovaEstoque;
    bool produtoEncontrado = false;
    Produtos produto;
    Produtos tempProduto;

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fscanf(arquivo, "Nome: %s\n", tempProduto.nome) == 1 &&
           fscanf(arquivo, "Codigo: %d\n", &tempProduto.codigo) == 1 &&
           fscanf(arquivo, "Quantidade: %d\n", &tempProduto.quantidadeEstoque) == 1 &&
           fscanf(arquivo, "Preco: %f\n", &tempProduto.preco) == 1) {

        if (tempProduto.codigo == codigo) {
            produtoEncontrado = true;

            quantidadeNovaEstoque = tempProduto.quantidadeEstoque - quantidadeVendida;

            fprintf(temp, "Nome: %s\n", tempProduto.nome);
            fprintf(temp, "Codigo: %d\n", tempProduto.codigo);
            fprintf(temp, "Quantidade: %d\n", quantidadeNovaEstoque);
            fprintf(temp, "Preco: %.2f\n", tempProduto.preco);
        } else {
            fprintf(temp, "Nome: %s\n", tempProduto.nome);
            fprintf(temp, "Codigo: %d\n", tempProduto.codigo);
            fprintf(temp, "Quantidade: %d\n", tempProduto.quantidadeEstoque);
            fprintf(temp, "Preco: %.2f\n", tempProduto.preco);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (produtoEncontrado) {
        remove("dados_produtos.txt");
        rename("temp.txt", "dados_produtos.txt");
    } else {
        remove("temp.txt");
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
    return 0;
}
int obterDadosVenda() {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "a+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Venda v;
    v.produtos = NULL;
    v.quantidadeTotalProdutos = 0;
    v.capacidadeItens = 5;
    v.produtos = malloc(v.capacidadeItens * sizeof(ProdutoVenda));

    if (v.produtos == NULL) {
        printf("Erro ao alocar memória para produtos.\n");
        fclose(arquivo);
        return 1;
    }

    printf("Número da venda: ");
    scanf("%d", &v.numeroVenda);

    printf("Número do vendedor: ");
    scanf("%d", &v.numeroVendedor);
    getchar();

    int verificaVendedor = verificaNumeroVendedor(v.numeroVendedor);
    if (verificaVendedor != 1) {
        printf("\nO número do vendedor digitado não foi encontrado!");
        printf("\nCadastre o vendedor antes de cadastrar a venda.\n");
        free(v.produtos);
        fclose(arquivo);
        return 1;
    }

    printf("Código do comprador: ");
    scanf("%d", &v.codigoComprador);
    getchar();

    int verificaComprador = verificaNumeroComprador(v.codigoComprador);
    if (verificaComprador != 1) {
        printf("\nO número do comprador digitado não foi encontrado!");
        printf("\nCadastre o comprador antes de cadastrar a venda.\n");
        free(v.produtos);
        fclose(arquivo);
        return 1;
    }

    printf("Data da venda (dd/mm/aaaa): ");
    fgets(v.data, sizeof(v.data), stdin);
    v.data[strcspn(v.data, "\n")] = 0;

    char continuar = 'S';
    v.valorTotal = 0;

    while (continuar == 'S' || continuar == 's') {
        if (v.quantidadeTotalProdutos >= v.capacidadeItens) {
            v.capacidadeItens *= 2;
            ProdutoVenda *temp = realloc(v.produtos, v.capacidadeItens * sizeof(ProdutoVenda));
            if (temp == NULL) {
                printf("Erro ao realocar memória.\n");
                free(v.produtos);
                fclose(arquivo);
                return 1;
            }
            v.produtos = temp;
        }

        ProdutoVenda pv;
        printf("\nCódigo do produto: ");
        scanf("%d", &pv.codigoProduto);

        float preco = obterPrecoProduto(pv.codigoProduto);
        if (preco == -1) {
            printf("Produto não encontrado!\n");
            continue;
        }
        pv.precoUnitario = preco;

        printf("Quantidade vendida: ");
        scanf("%d", &pv.quantidadeVendida);

        if (!verificarEstoque(pv.codigoProduto, pv.quantidadeVendida)) {
            printf("Quantidade em estoque insuficiente!\n");
            continue;
        }

        pv.subtotal = pv.precoUnitario * pv.quantidadeVendida;
        v.valorTotal += pv.subtotal;

        v.produtos[v.quantidadeTotalProdutos++] = pv;

        printf("Adicionar outro produto? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
    }

    if (v.quantidadeTotalProdutos == 0) {
        printf("Nenhum produto válido foi adicionado à venda. Operação cancelada.\n");
        free(v.produtos);
        fclose(arquivo);
        return 1;
    }

    // Chama cadastrarVenda para salvar a venda
    if (cadastrarVenda(&v) == 0) {
        fclose(arquivo);
        return 0;
    } else {
        printf("Erro ao cadastrar a venda.\n");
        free(v.produtos);
        fclose(arquivo);
        return 1;
    }
}

int cadastrarVenda(Venda *v) {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(arquivo, "Venda: %d\n", v->numeroVenda);
    fprintf(arquivo, "Vendedor: %d\n", v->numeroVendedor);
    fprintf(arquivo, "Comprador: %d\n", v->codigoComprador);
    fprintf(arquivo, "Data: %s\n", v->data);
    fprintf(arquivo, "Total: %.2f\n", v->valorTotal);
    fprintf(arquivo, "Itens:\n");

    for (int i = 0; i < v->quantidadeTotalProdutos; i++) {
        fprintf(arquivo, "%d,%d,%.2f,%.2f\n",
                v->produtos[i].codigoProduto,
                v->produtos[i].quantidadeVendida,
                v->produtos[i].precoUnitario,
                v->produtos[i].subtotal);

        atualizarEstoque(v->produtos[i].codigoProduto, v->produtos[i].quantidadeVendida);
    }
    fprintf(arquivo, "---\n");

    printf("\nVenda cadastrada com sucesso! Total: R$ %.2f\n", v->valorTotal);

    free(v->produtos);
    fclose(arquivo);
    return 0;
}
int listarVendas() {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    printf("\nLista de Vendas:\n");
    printf("------------------------------------------------------------\n");

    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(strncmp(linha, "Venda:", 6) == 0) {
            int numeroVenda;
            sscanf(linha, "Venda: %d", &numeroVenda);

            fgets(linha, sizeof(linha), arquivo);
            int vendedor;
            sscanf(linha, "Vendedor: %d", &vendedor);

            fgets(linha, sizeof(linha), arquivo);
            int comprador;
            sscanf(linha, "Comprador: %d", &comprador);

            fgets(linha, sizeof(linha), arquivo);
            char data[11];
            sscanf(linha, "Data: %10s", data);

            fgets(linha, sizeof(linha), arquivo);
            float total;
            sscanf(linha, "Total: %f", &total);

            printf("Venda Nº %d | Vendedor: %d | Comprador: %d\n", numeroVenda, vendedor, comprador);
            printf("Data: %s | Total: R$ %.2f\n", data, total);
            printf("Itens:\n");

            fgets(linha, sizeof(linha), arquivo);

            while(fgets(linha, sizeof(linha), arquivo) && strcmp(linha, "---\n") != 0) {
                int codigo, quantidade;
                float precoUnitario, subtotal;
                sscanf(linha, "%d,%d,%f,%f", &codigo, &quantidade, &precoUnitario, &subtotal);

                printf("- Código: %d | Qtd: %d | Preço: R$ %.2f | Subtotal: R$ %.2f\n",
                       codigo, quantidade, precoUnitario, subtotal);
            }
            printf("------------------------------------------------------------\n");
        }
    }

    fclose(arquivo);
    return 0;
}

int alterarVenda(int numeroVenda) {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    FILE *temp = fopen("temp_vendas.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        return 1;
    }

    char linha[100];
    int encontrado = 0;
    int dentroDaVenda = 0;

    while(fgets(linha, sizeof(linha), arquivo)) {
        if(strncmp(linha, "Venda:", 6) == 0) {
            int num;
            sscanf(linha, "Venda: %d", &num);

            if(num == numeroVenda) {
                encontrado = 1;
                dentroDaVenda = 1;

                printf("\nVenda encontrada:\n");
                printf("%s", linha);

                char dadosVenda[5][100];
                for(int i = 0; i < 5; i++) {
                    fgets(dadosVenda[i], sizeof(dadosVenda[i]), arquivo);
                    printf("%s", dadosVenda[i]);
                }

                printf("\nO que deseja alterar?\n");
                printf("1 - Vendedor\n");
                printf("2 - Comprador\n");
                printf("3 - Data\n");
                printf("4 - Itens da venda\n");
                printf("0 - Cancelar\n");
                printf("Opção: ");

                int opcao;
                scanf("%d", &opcao);
                getchar();

                if(opcao == 0) {
                    fprintf(temp, "Venda: %d\n", num);
                    for(int i = 0; i < 5; i++) {
                        fprintf(temp, "%s", dadosVenda[i]);
                    }

                    while(fgets(linha, sizeof(linha), arquivo) && strcmp(linha, "---\n") != 0) {
                        fprintf(temp, "%s", linha);
                    }
                    fprintf(temp, "---\n");

                    dentroDaVenda = 0;
                    continue;
                }

                if(opcao == 1) {
                    printf("Novo número do vendedor: ");
                    int novoVendedor;
                    scanf("%d", &novoVendedor);
                    getchar();

                    if(verificaNumeroVendedor(novoVendedor)) {
                        sprintf(dadosVenda[1], "Vendedor: %d\n", novoVendedor);
                    } else {
                        printf("Vendedor não encontrado!\n");
                    }
                }
                else if(opcao == 2) {
                    printf("Novo código do comprador: ");
                    int novoComprador;
                    scanf("%d", &novoComprador);
                    getchar();
                    sprintf(dadosVenda[2], "Comprador: %d\n", novoComprador);
                }
                else if(opcao == 3) {
                    printf("Nova data (dd/mm/aaaa): ");
                    char novaData[11];
                    fgets(novaData, 11, stdin);
                    getchar();
                    novaData[strcspn(novaData, "\n")] = 0;
                    sprintf(dadosVenda[3], "Data: %s\n", novaData);
                }
                else if(opcao == 4) {
                    printf("Alteração de itens ainda não implementada.\n");
                }

                fprintf(temp, "Venda: %d\n", num);
                for(int i = 0; i < 5; i++) {
                    fprintf(temp, "%s", dadosVenda[i]);
                }

                while(fgets(linha, sizeof(linha), arquivo) && strcmp(linha, "---\n") != 0) {
                    fprintf(temp, "%s", linha);
                }
                fprintf(temp, "---\n");

                dentroDaVenda = 0;
            } else {
                fprintf(temp, "%s", linha);
            }
        } else if(!dentroDaVenda) {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado) {
        remove(ARQUIVO_VENDAS);
        rename("temp_vendas.txt", ARQUIVO_VENDAS);
        printf("Venda alterada com sucesso.\n");
    } else {
        remove("temp_vendas.txt");
        printf("Venda não encontrada.\n");
    }
    return 0;
}

int excluirVenda(int numeroVenda) {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    FILE *temp = fopen("temp_vendas.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        return 1;
    }

    char linha[100];
    int encontrado = 0;
    int dentroDaVenda = 0;

    while(fgets(linha, sizeof(linha), arquivo)) {
        if(strncmp(linha, "Venda:", 6) == 0) {
            int num;
            sscanf(linha, "Venda: %d", &num);

            if(num == numeroVenda) {
                encontrado = 1;
                dentroDaVenda = 1;
                printf("Venda Nº %d será excluída.\n", num);

                while(fgets(linha, sizeof(linha), arquivo) && strcmp(linha, "---\n") != 0) {
                    continue;
                }

                dentroDaVenda = 0;
                continue;
            } else {
                fprintf(temp, "%s", linha);
            }
        } else if(!dentroDaVenda) {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado) {
        remove(ARQUIVO_VENDAS);
        rename("temp_vendas.txt", ARQUIVO_VENDAS);
        printf("Venda excluída com sucesso.\n");
    } else {
        remove("temp_vendas.txt");
        printf("Venda não encontrada.\n");
    }
    return 0;
}

/* * * * * * * * * * * * * * * * * *  * * * * * *
*    Funções de Emitir e Buscar Notas Fiscais   *
* * * * * * * * * * * * * * * * * * * * * * * * */

int emitirNotaFiscal(int numeroVenda) {
    FILE *arquivoVendas = fopen(ARQUIVO_VENDAS, "r");
    if (!arquivoVendas) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return 1;
    }

    Venda venda;
    venda.produtos = NULL;
    bool vendaEncontrada = false;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivoVendas)) {
        if (strstr(linha, "Venda:")) {
            if (sscanf(linha, "Venda: %d", &venda.numeroVenda) == 1 && venda.numeroVenda == numeroVenda) {
                vendaEncontrada = true;

                while (fgets(linha, sizeof(linha), arquivoVendas)) {
                    if (strstr(linha, "Vendedor:")) {
                        sscanf(linha, "Vendedor: %d", &venda.numeroVendedor);
                    }
                    else if (strstr(linha, "Comprador:")) {
                        sscanf(linha, "Comprador: %d", &venda.codigoComprador);
                    }
                    else if (strstr(linha, "Data:")) {
                        sscanf(linha, "Data: %10s", venda.data);
                    }
                    else if (strstr(linha, "Total:")) {
                        sscanf(linha, "Total: %f", &venda.valorTotal);
                    }
                    else if (strstr(linha, "Itens:")) {
                        venda.capacidadeItens = 2;
                        venda.produtos = malloc(venda.capacidadeItens * sizeof(ProdutoVenda));
                        venda.quantidadeTotalProdutos = 0;

                        while (fgets(linha, sizeof(linha), arquivoVendas) && !strstr(linha, "---")) {
                            if (venda.quantidadeTotalProdutos >= venda.capacidadeItens) {
                                venda.capacidadeItens *= 2;
                                ProdutoVenda *temp = realloc(venda.produtos, venda.capacidadeItens * sizeof(ProdutoVenda));
                                if (!temp) {
                                    printf("Erro ao alocar memória.\n");
                                    free(venda.produtos);
                                    fclose(arquivoVendas);
                                    return 1;
                                }
                                venda.produtos = temp;
                            }

                            if (sscanf(linha, "%d,%d,%f,%f",
                                   &venda.produtos[venda.quantidadeTotalProdutos].codigoProduto,
                                   &venda.produtos[venda.quantidadeTotalProdutos].quantidadeVendida,
                                   &venda.produtos[venda.quantidadeTotalProdutos].precoUnitario,
                                   &venda.produtos[venda.quantidadeTotalProdutos].subtotal) == 4) {
                                venda.quantidadeTotalProdutos++;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    fclose(arquivoVendas);

    if (!vendaEncontrada) {
        printf("Venda não encontrada.\n");
        return 1;
    }

    Comprador comprador;
    bool compradorEncontrado = false;
    FILE *arquivoCompradores = fopen("dados_compradores.txt", "r");
    if (arquivoCompradores) {
        while (fgets(linha, sizeof(linha), arquivoCompradores)) {
            if (strstr(linha, "Codigo:")) {
                int codigo;
                if (sscanf(linha, "Codigo: %d", &codigo) == 1 && codigo == venda.codigoComprador) {
                    compradorEncontrado = true;
                    comprador.codigo = codigo;

                    while (fgets(linha, sizeof(linha), arquivoCompradores) && !strstr(linha, "Codigo:")) {
                        if (strstr(linha, "Nome:")) {
                            sscanf(linha, "Nome: %[^\n]", comprador.nome);
                        }
                        else if (strstr(linha, "CPF:")) {
                            sscanf(linha, "CPF: %[^\n]", comprador.cpf);
                        }
                        else if (strstr(linha, "Email:")) {
                            sscanf(linha, "Email: %[^\n]", comprador.email);
                        }
                        else if (strstr(linha, "Rua:")) {
                            sscanf(linha, "Rua: %[^\n]", comprador.endereco.rua);
                        }
                        else if (strstr(linha, "Bairro:")) {
                            sscanf(linha, "Bairro: %[^\n]", comprador.endereco.bairro);
                        }
                        else if (strstr(linha, "Cidade:")) {
                            sscanf(linha, "Cidade: %[^\n]", comprador.endereco.cidade);
                        }
                        else if (strstr(linha, "Estado:")) {
                            sscanf(linha, "Estado: %[^\n]", comprador.endereco.estado);
                        }
                        else if (strstr(linha, "CEP:")) {
                            sscanf(linha, "CEP: %[^\n]", comprador.endereco.cep);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        fclose(arquivoCompradores);
    }

    if (!compradorEncontrado) {
        printf("Comprador da venda não encontrado.\n");
        free(venda.produtos);
        return 1;
    }

    Vendedor vendedor;
    bool vendedorEncontrado = false;
    FILE *arquivoVendedores = fopen("vendedores.txt", "r");
    if (arquivoVendedores) {
        while (fgets(linha, sizeof(linha), arquivoVendedores)) {
            if (sscanf(linha, "%[^,],%d,%f,%f",
                      vendedor.nome, &vendedor.numero, &vendedor.salario, &vendedor.comissao) == 4) {
                if (vendedor.numero == venda.numeroVendedor) {
                    vendedorEncontrado = true;
                    break;
                }
            }
        }
        fclose(arquivoVendedores);
    }

    if (!vendedorEncontrado) {
        printf("Vendedor da venda não encontrado.\n");
        free(venda.produtos);
        return 1;
    }

    char **nomesProdutos = malloc(venda.quantidadeTotalProdutos * sizeof(char*));
    for (int i = 0; i < venda.quantidadeTotalProdutos; i++) {
        nomesProdutos[i] = malloc(50 * sizeof(char));
        strcpy(nomesProdutos[i], "Produto não encontrado");
    }

    int *estoqueProdutos = malloc(venda.quantidadeTotalProdutos * sizeof(int));
    for (int i = 0; i < venda.quantidadeTotalProdutos; i++) {
        FILE *arquivoProdutos = fopen("dados_produtos.txt", "r");
        if (arquivoProdutos) {
            Produtos produto;
            while (fgets(linha, sizeof(linha), arquivoProdutos)) {
                if (strstr(linha, "Codigo:")) {
                    if (sscanf(linha, "Codigo: %d", &produto.codigo) == 1 &&
                        produto.codigo == venda.produtos[i].codigoProduto) {
                        fseek(arquivoProdutos, -strlen(linha), SEEK_CUR);
                        fscanf(arquivoProdutos, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n",
                               produto.nome, &produto.codigo, &produto.quantidadeEstoque, &produto.preco);
                        strcpy(nomesProdutos[i], produto.nome);
                        estoqueProdutos[i] = produto.quantidadeEstoque;
                        break;
                    }
                }
            }
            fclose(arquivoProdutos);
        }
    }

    FILE *arquivoNota = fopen("nota_fiscal.txt", "w");
    if (!arquivoNota) {
        printf("Erro ao criar arquivo da nota fiscal.\n");
        for (int i = 0; i < venda.quantidadeTotalProdutos; i++) {
            free(nomesProdutos[i]);
        }
        free(nomesProdutos);
        free(estoqueProdutos);
        free(venda.produtos);
        return 1;
    }

    fprintf(arquivoNota, "=== NOTA FISCAL ===\n\n");
    fprintf(arquivoNota, "Número da Venda: %d\n", venda.numeroVenda);
    fprintf(arquivoNota, "Data: %s\n", venda.data);
    fprintf(arquivoNota, "Vendedor: %s (Nº %d)\n\n", vendedor.nome, venda.numeroVendedor);

    fprintf(arquivoNota, "Dados do Comprador:\n");
    fprintf(arquivoNota, "Nome: %s\n", comprador.nome);
    fprintf(arquivoNota, "CPF: %s\n", comprador.cpf);
    fprintf(arquivoNota, "Email: %s\n", comprador.email);
    fprintf(arquivoNota, "Endereço: %s, %s - %s/%s - CEP: %s\n\n",
            comprador.endereco.rua, comprador.endereco.bairro,
            comprador.endereco.cidade, comprador.endereco.estado,
            comprador.endereco.cep);

    fprintf(arquivoNota, "Produtos comprados:\n");
    fprintf(arquivoNota, "%-30s %5s %10s %10s\n", "Descrição", "Qtd", "Unitário", "Subtotal");
    fprintf(arquivoNota, "------------------------------------------------------------\n");

    for (int i = 0; i < venda.quantidadeTotalProdutos; i++) {
        fprintf(arquivoNota, "%-30s %5d %10.2f %10.2f\n",
                nomesProdutos[i],
                venda.produtos[i].quantidadeVendida,
                venda.produtos[i].precoUnitario,
                venda.produtos[i].subtotal);
                fprintf(arquivoNota, "  Codigo: %d\n\n",
                venda.produtos[i].codigoProduto,
                estoqueProdutos[i]);
    }

    float frete = (venda.valorTotal > 300) ? 0 : (venda.valorTotal > 100) ? 20 : 30;
    fprintf(arquivoNota, "------------------------------------------------------------\n");
    fprintf(arquivoNota, "%-30s %15s\n", "Subtotal:", "R$");
    fprintf(arquivoNota, "%-30s %15.2f\n", "Frete:", frete);
    fprintf(arquivoNota, "%-30s %15.2f\n", "Total:", venda.valorTotal + frete);

    fclose(arquivoNota);

    for (int i = 0; i < venda.quantidadeTotalProdutos; i++) {
        free(nomesProdutos[i]);
    }
    free(nomesProdutos);
    free(estoqueProdutos);
    free(venda.produtos);

    printf("\n=== NOTA FISCAL GERADA ===\n");
    arquivoNota = fopen("nota_fiscal.txt", "r");
    if (arquivoNota) {
        while (fgets(linha, sizeof(linha), arquivoNota)) {
            printf("%s", linha);
        }
        fclose(arquivoNota);
    }
    printf("\nNota fiscal salva em 'nota_fiscal.txt'\n");
    return 0;
}

int buscarNotaPorNumeroVenda(int numeroVenda) {
    FILE *arquivoNota = fopen("nota_fiscal.txt", "r");
    if (!arquivoNota) {
        printf("Erro ao abrir arquivo de notas fiscais.\n");
        return 1;
    }

    char linha[256];
    bool encontrouNota = false;
    bool exibir = false;

    printf("\n=== NOTA FISCAL ===\n");

    while (fgets(linha, sizeof(linha), arquivoNota)) {
        if (strstr(linha, "Número da Venda:")) {
            int num;
            if (sscanf(linha, "Número da Venda: %d", &num) == 1 && num == numeroVenda) {
                encontrouNota = true;
                exibir = true;
            } else {
                exibir = false;
            }
        }

        if (exibir) {
            linha[strcspn(linha, "\n")] = '\0';
            printf("%s\n", linha);

            if (strstr(linha, "Total:")) {
                break;
            }
        }
    }

    if (!encontrouNota) {
        printf("\nNota fiscal com número %d não encontrada.\n", numeroVenda);
    }

    fclose(arquivoNota);
    return 0;
}
/* * * * * * * * * * * * * * * * * * *
*         Declarando Menus           *
* * * * * * * * * * * * * * * * * * */
int menuVendedores(){
    int opcao;
    int numero;
    do {
        printf("\n=== CRUD VENDEDORES ===\n");
        printf("1. Cadastrar\n2. Listar\n3. Alterar\n4. Excluir\n5. Voltando para o Menu Principal...\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: obterDadosCompradores(); break;
            case 2: listarVendedores(); break;
            case 3:
                printf("Digite o numero do vendedor: ");
                scanf("%d", &numero);
                alterarVendedor(numero);
                break;
            case 4:
             printf("Digite o numero do vendedor: ");
             scanf("%d", &numero);
             excluirVendedor(numero);
             break;
        }
    } while (opcao != 5);
    return 0;
}
int menuCompradores(){
    int opcao = 0;
    int numero;
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
                    obterDadosCompradores();
                    break;
                case 2:
                    consultarTodosCompradores();
                    break;
                case 3:
                    printf("Digite o numero do comprador: ");
                    scanf("%d", &numero);
                    alterarProdutos(numero);
                    break;
                case 4:
                    printf("Digite o numero do comprador: ");
                    scanf("%d", &numero);
                    excluirComprador(numero);
                    break;
                case 5:
                    printf("Voltar ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                    break;

        };
    }while (opcao != 5);
    return 0;
}
int menuProdutos(){
    int opcao = 0;
    int codigo;
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
                obterDadosProdutos();
                break;
            case 2:
                printf("Digite o codigo produto: ");
                scanf("%d", &codigo);
                consultarProdutoPorCodigo(codigo);
                break;
            case 3:
                consultarTodosProdutos();
                break;
            case 4:
                printf("Digite o codigo produto: ");
                scanf("%d", &codigo);
                alterarProdutos(codigo);
                break;
            case 5:
                printf("Digite o codigo produto: ");
                scanf("%d", &codigo);
                excluirProduto(codigo);
                break;
            case 6:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
    return 0;
}

int menuVendas(){
    int opcao, numero;
    do {
        printf("\n=== CRUD VENDAS ===\n");
        printf("1. Cadastrar Venda\n2. Listar Vendas\n3. Alterar Venda\n4. Excluir Venda\n5. Voltando para o Menu Principal\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: obterDadosVenda(); break;
            case 2: listarVendas(); break;
            case 3:
                printf("Digite o numero da venda: ");
                scanf("%d", &numero);
                alterarVenda(numero);
                break;
            case 4:
                printf("Digite o numero da venda: ");
                scanf("%d", &numero);
                excluirVenda(numero);
                break;
        }
    } while (opcao != 5);
    return 0;
}

/* * * * * * * * * * * * * * * * * * *
*       Programa Principal           *
* * * * * * * * * * * * * * * * * * */

int main(int argc, char **argv) {
    int opcao = 0;
    int numero;
    do {
        printf("----------------------------------\n");
        printf("|         MENU PRINCIPAL         |\n");
        printf("| 1- Produtos                    |\n");
        printf("| 2- Compradores                 |\n");
        printf("| 3- Vendedores                  |\n");
        printf("| 4- Vendas                      |\n");
        printf("| 5- Emitir Nota Fiscal          |\n");
        printf("| 6- Buscar Nota Fiscal          |\n");
        printf("| 7- SAIR                        |\n");
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
                printf("Digite o numero da venda: ");
                scanf("%d", &numero);
                emitirNotaFiscal(numero);
                break;
            case 6:
                printf("Digite o numero da venda: ");
                scanf("%d", &numero);
                buscarNotaPorNumeroVenda(numero);
                break;
            case 7:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return SUCESSO;
}
