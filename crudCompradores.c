#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_TAMANHO_COMPRADORES
#define MAX_TAMANHO_NOME 50
#define MAX_TAMANHO_CPF 15
#define MAX_TAMANHO_EMAIL 50
#define MAX_TAMANHO_RUA 50
#define MAX_TAMANHO_BAIRRO 30
#define MAX_TAMANHO_CIDADE 30
#define MAX_TAMANHO_ESTADO 3
#define MAX_TAMANHO_CEP 10
#define SUCESSO 0
// Declaração de estruturas de dados
typedef struct {
    char rua[MAX_TAMANHO_RUA], bairro[MAX_TAMANHO_BAIRRO], cidade[MAX_TAMANHO_CIDADE], estado[MAX_TAMANHO_ESTADO], cep[MAX_TAMANHO_CEP];
} Endereco;

typedef struct {
    char nome[MAX_TAMANHO_NOME];
    char cpf[MAX_TAMANHO_CPF];
    char email[MAX_TAMANHO_EMAIL];
    Endereco endereco;
} Comprador;

// Declaração de Funções
int carregarNumeroDeCompradores(Comprador compradores[]) {
    FILE *arquivo = fopen("dados_comprador.txt", "r");
    int i = 0;

    if (arquivo == NULL) return 0;

    while (
        fscanf(arquivo, "Nome: %[^\n]\n", compradores[i].nome) == 1 &&
        fscanf(arquivo, "CPF: %[^\n]\n", compradores[i].cpf) == 1 &&
        fscanf(arquivo, "Email: %[^\n]\n", compradores[i].email) == 1 &&
        fscanf(arquivo, "Rua: %[^\n]\n", compradores[i].endereco.rua) == 1 &&
        fscanf(arquivo, "Bairro: %[^\n]\n", compradores[i].endereco.bairro) == 1 &&
        fscanf(arquivo, "Cidade: %[^\n]\n", compradores[i].endereco.cidade) == 1 &&
        fscanf(arquivo, "Estado: %[^\n]\n", compradores[i].endereco.estado) == 1 &&
        fscanf(arquivo, "CEP: %[^\n]\n", compradores[i].endereco.cep) == 1) {
        i++;
        if (i >= MAX_TAMANHO_COMPRADORES) {
            break;
        }
    }


    fclose(arquivo);
    return i; // número de compradores carregados
}
int desejaContinuar(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    int resposta;
    printf("\nQuer cadastrar mais compradores? SIM=1 NAO=2: ");
    scanf("%d", &resposta);
    return resposta;
}
int cadastrarCompradores(){
    int resposta, codigo;
    bool verificaCodigo = false;
    FILE *arquivo;
    Comprador compradores[MAX_TAMANHO_COMPRADORES];
    arquivo = fopen("dados_compradores.txt", "a");
    int i = carregarNumeroDeCompradores(compradores);
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
        resposta = desejaContinuar();

    }while(resposta == 1 && i < MAX_TAMANHO_COMPRADORES);
    if(i >= MAX_TAMANHO_COMPRADORES){
        printf("O numero de produtos cadastrados excedeu o limite de %d", MAX_TAMANHO_COMPRADORES);
        return 1;
    }

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

int main(int argc, char ** argv)
{
    int opcao = 0;
    printf("-------------------------------------\n");
    printf("|            MENU                    |\n");
    printf("| 1- Cadastrar Compradores           |\n");
    printf("| 2- Consultar Compradores           |\n");
    printf("| 3- Alterar Compradores             |\n");
    printf("| 4- Excluir Compradores             |\n");
    printf("| 5- SAIR                            |\n");
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
                //consultarTodosCompradores();
                break;
            case 4:
                //alterarComprador();
                break;
            case 5:
                //excluirComprador();
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
