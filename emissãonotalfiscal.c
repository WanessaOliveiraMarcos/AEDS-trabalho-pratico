#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[50];
    char cpf[15];
    char email[50];
    char endereco[200]; // Endereço completo numa string só
} Comprador;

typedef struct {
    char nome[50];
    int codigo;
    int quantidadeEstoque;
    float preco;
} Produto;

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
    //Abre o arquivo dados_compradores.txt para leitura



    // leitura simplificada com verificação direta de fscanf
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

//Se o comprador não foi encontrado no arquivo, imprime mensagem e encerra a função.



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
//Abre o arquivo dados_produtos.txt para leitura
        Produto produto;
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

    fprintf(arquivoNota, "\nTotal da venda: R$ %.2f\n", total);
    fclose(arquivoNota);

    printf("Nota fiscal gerada com sucesso no arquivo nota_fiscal.txt\n");
}

int main() {
    emitirNotaFiscal();
    return 0;
}