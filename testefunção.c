#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUTOS 100
#define MAX_VENDEDORES 100
#define MAX_COMPRADORES 100
#define MAX_VENDAS 1000

// Estruturas

typedef struct {
    char nome[50];
    int codigo;
    int quantidadeEstoque;
    float preco;
} Produto;

typedef struct {
    char nome[50];
    int numero;
    float salario;
    float comissao;
} Vendedor;

typedef struct {
    char nome[50];
    char cpf[15];
    char email[50];
    char endereco[200];
} Comprador;

typedef struct {
    int numeroVendedor;
    int codigoProduto;
    int quantidade;
    char cpfComprador[15];
    float valorTotal;
} Venda;

// Funções Auxiliares
bool codigoProdutoExiste(int codigo) {
    FILE *arq = fopen("dados_produtos.txt", "r");
    if (!arq) return false;

    Produto p;
    while (fscanf(arq, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n", p.nome, &p.codigo, &p.quantidadeEstoque, &p.preco) == 4) {
        if (p.codigo == codigo) {
            fclose(arq);
            return true;
        }
    }
    fclose(arq);
    return false;
}

bool numeroVendedorExiste(int numero) {
    FILE *arq = fopen("dados_vendedores.txt", "r");
    if (!arq) return false;

    Vendedor v;
    while (fscanf(arq, "%[^,],%d,%f,%f\n", v.nome, &v.numero, &v.salario, &v.comissao) == 4) {
        if (v.numero == numero) {
            fclose(arq);
            return true;
        }
    }
    fclose(arq);
    return false;
}

bool cpfCompradorExiste(char *cpf) {
    FILE *arq = fopen("dados_compradores.txt", "r");
    if (!arq) return false;

    Comprador c;
    while (fscanf(arq, "Nome: %[^\n]\nCPF: %[^\n]\nEmail: %[^\n]\nEndereco: %[^\n]\n", c.nome, c.cpf, c.email, c.endereco) == 4) {
        if (strcmp(c.cpf, cpf) == 0) {
            fclose(arq);
            return true;
        }
    }
    fclose(arq);
    return false;
}

// Cadastro Produto
void cadastrarProduto() {
    Produto p;
    FILE *arq = fopen("dados_produtos.txt", "a");
    if (!arq) {
        printf("Erro ao abrir arquivo de produtos.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    getchar();
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    do {
        printf("Digite o código do produto (numérico): ");
        scanf("%d", &p.codigo);
        if (codigoProdutoExiste(p.codigo)) {
            printf("Código já existe. Tente outro.\n");
        }
    } while (codigoProdutoExiste(p.codigo));

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &p.quantidadeEstoque);

    printf("Digite o preço unitário: ");
    scanf("%f", &p.preco);

    fprintf(arq, "Nome: %s\nCodigo: %d\nQuantidade: %d\nPreco: %.2f\n", p.nome, p.codigo, p.quantidadeEstoque, p.preco);
    fclose(arq);
    printf("Produto cadastrado com sucesso!\n");
}

// Cadastro Vendedor
void cadastrarVendedor() {
    Vendedor v;
    FILE *arq = fopen("dados_vendedores.txt", "a");
    if (!arq) {
        printf("Erro ao abrir arquivo de vendedores.\n");
        return;
    }

    do {
        printf("Digite o número do vendedor: ");
        scanf("%d", &v.numero);
        if (numeroVendedorExiste(v.numero)) {
            printf("Número já existe. Tente outro.\n");
        }
    } while (numeroVendedorExiste(v.numero));

    getchar();
    printf("Digite o nome do vendedor: ");
    fgets(v.nome, sizeof(v.nome), stdin);
    v.nome[strcspn(v.nome, "\n")] = 0;

    printf("Digite o salário fixo do vendedor: ");
    scanf("%f", &v.salario);

    v.comissao = 0.0;

    fprintf(arq, "%s,%d,%.2f,%.2f\n", v.nome, v.numero, v.salario, v.comissao);
    fclose(arq);
    printf("Vendedor cadastrado com sucesso!\n");
}

// Cadastro Comprador
void cadastrarComprador() {
    Comprador c;
    FILE *arq = fopen("dados_compradores.txt", "a");
    if (!arq) {
        printf("Erro ao abrir arquivo de compradores.\n");
        return;
    }

    getchar();
    printf("Digite o nome do comprador: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    do {
        printf("Digite o CPF do comprador: ");
        fgets(c.cpf, sizeof(c.cpf), stdin);
        c.cpf[strcspn(c.cpf, "\n")] = 0;
        if (cpfCompradorExiste(c.cpf)) {
            printf("CPF já cadastrado. Tente outro.\n");
        }
    } while (cpfCompradorExiste(c.cpf));

    printf("Digite o email do comprador: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    printf("Digite o endereço completo do comprador: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    fprintf(arq, "Nome: %s\nCPF: %s\nEmail: %s\nEndereco: %s\n", c.nome, c.cpf, c.email, c.endereco);
    fclose(arq);
    printf("Comprador cadastrado com sucesso!\n");
}

// Registrar Venda
void cadastrarVenda() {
    Venda v;
    Produto p;
    Vendedor vend;
    Comprador c;
    bool produtoEncontrado = false, vendedorEncontrado = false, compradorEncontrado = false;

    printf("Digite o número do vendedor: ");
    scanf("%d", &v.numeroVendedor);

    FILE *arqVend = fopen("dados_vendedores.txt", "r");
    if (!arqVend) {
        printf("Erro ao abrir arquivo de vendedores.\n");
        return;
    }
    while (fscanf(arqVend, "%[^,],%d,%f,%f\n", vend.nome, &vend.numero, &vend.salario, &vend.comissao) == 4) {
        if (vend.numero == v.numeroVendedor) {
            vendedorEncontrado = true;
            break;
        }
    }
    fclose(arqVend);
    if (!vendedorEncontrado) {
        printf("Vendedor não encontrado.\n");
        return;
    }

    printf("Digite o CPF do comprador: ");
    getchar();
    fgets(v.cpfComprador, sizeof(v.cpfComprador), stdin);
    v.cpfComprador[strcspn(v.cpfComprador, "\n")] = 0;

    FILE *arqCompr = fopen("dados_compradores.txt", "r");
    if (!arqCompr) {
        printf("Erro ao abrir arquivo de compradores.\n");
        return;
    }
    while (fscanf(arqCompr, "Nome: %[^\n]\nCPF: %[^\n]\nEmail: %[^\n]\nEndereco: %[^\n]\n", c.nome, c.cpf, c.email, c.endereco) == 4) {
        if (strcmp(c.cpf, v.cpfComprador) == 0) {
            compradorEncontrado = true;
            break;
        }
    }
    fclose(arqCompr);
    if (!compradorEncontrado) {
        printf("Comprador não encontrado.\n");
        return;
    }

    printf("Digite o código do produto: ");
    scanf("%d", &v.codigoProduto);

    FILE *arqProd = fopen("dados_produtos.txt", "r+");
    if (!arqProd) {
        printf("Erro ao abrir arquivo de produtos.\n");
        return;
    }
    long posProduto = 0;
    produtoEncontrado = false;
    while (fscanf(arqProd, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n", p.nome, &p.codigo, &p.quantidadeEstoque, &p.preco) == 4) {
        if (p.codigo == v.codigoProduto) {
            produtoEncontrado = true;
            break;
        }
        posProduto = ftell(arqProd);
    }
    if (!produtoEncontrado) {
        printf("Produto não encontrado.\n");
        fclose(arqProd);
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &v.quantidade);

    if (v.quantidade > p.quantidadeEstoque) {
        printf("Quantidade insuficiente em estoque.\n");
        fclose(arqProd);
        return;
    }

    // Atualiza estoque
    p.quantidadeEstoque -= v.quantidade;

    // Atualiza arquivo do produto (reescrevendo)
    // Para atualizar o estoque de forma simples, vamos recarregar todos os produtos e regravar
    rewind(arqProd);

    Produto tempProduto;
    FILE *tmp = fopen("tmp_produtos.txt", "w");
    if (!tmp) {
        printf("Erro ao atualizar arquivo de produtos.\n");
        fclose(arqProd);
        return;
    }

    while (fscanf(arqProd, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n", tempProduto.nome, &tempProduto.codigo, &tempProduto.quantidadeEstoque, &tempProduto.preco) == 4) {
        if (tempProduto.codigo == p.codigo) {
            tempProduto.quantidadeEstoque = p.quantidadeEstoque;
        }
        fprintf(tmp, "Nome: %s\nCodigo: %d\nQuantidade: %d\nPreco: %.2f\n", tempProduto.nome, tempProduto.codigo, tempProduto.quantidadeEstoque, tempProduto.preco);
    }
    fclose(arqProd);
    fclose(tmp);

    // Substitui arquivo antigo pelo atualizado
    remove("dados_produtos.txt");
    rename("tmp_produtos.txt", "dados_produtos.txt");

    v.valorTotal = v.quantidade * p.preco;

    // Grava venda
    FILE *arqVenda = fopen("dados_vendas.txt", "a");
    if (!arqVenda) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return;
    }
    fprintf(arqVenda, "%d,%d,%d,%s,%.2f\n", v.numeroVendedor, v.codigoProduto, v.quantidade, v.cpfComprador, v.valorTotal);
    fclose(arqVenda);

    printf("Venda registrada com sucesso! Total: R$ %.2f\n", v.valorTotal);
}

// Emitir Nota Fiscal
void emitirNotaFiscal() {
    char cpf[15];
    printf("Digite o CPF do comprador para emitir nota fiscal: ");
    getchar();
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    Comprador c;
    bool compradorEncontrado = false;

    FILE *arqCompr = fopen("dados_compradores.txt", "r");
    if (!arqCompr) {
        printf("Erro ao abrir arquivo de compradores.\n");
        return;
    }

    while (fscanf(arqCompr, "Nome: %[^\n]\nCPF: %[^\n]\nEmail: %[^\n]\nEndereco: %[^\n]\n", c.nome, c.cpf, c.email, c.endereco) == 4) {
        if (strcmp(c.cpf, cpf) == 0) {
            compradorEncontrado = true;
            break;
        }
    }
    fclose(arqCompr);

    if (!compradorEncontrado) {
        printf("Comprador não encontrado.\n");
        return;
    }

    FILE *arqVenda = fopen("dados_vendas.txt", "r");
    if (!arqVenda) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return;
    }

    FILE *arqNota = fopen("nota_fiscal.txt", "w");
    if (!arqNota) {
        printf("Erro ao criar arquivo nota fiscal.\n");
        fclose(arqVenda);
        return;
    }

    fprintf(arqNota, "=== NOTA FISCAL ===\n\n");
    fprintf(arqNota, "Dados do Comprador:\nNome: %s\nCPF: %s\nEmail: %s\nEndereco: %s\n\n", c.nome, c.cpf, c.email, c.endereco);
    fprintf(arqNota, "Produtos comprados:\n");

    Venda v;
    Produto p;
    float total = 0;
    bool algumaVenda = false;

    while (fscanf(arqVenda, "%d,%d,%d,%14[^,],%f\n", &v.numeroVendedor, &v.codigoProduto, &v.quantidade, v.cpfComprador, &v.valorTotal) != EOF) {
        if (strcmp(v.cpfComprador, cpf) == 0) {
            // buscar dados do produto
            FILE *arqProd = fopen("dados_produtos.txt", "r");
            if (!arqProd) continue;
            bool prodFound = false;
            while (fscanf(arqProd, "Nome: %[^\n]\nCodigo: %d\nQuantidade: %d\nPreco: %f\n", p.nome, &p.codigo, &p.quantidadeEstoque, &p.preco) == 4) {
                if (p.codigo == v.codigoProduto) {
                    prodFound = true;
                    break;
                }
            }
            fclose(arqProd);
            if (!prodFound) continue;

            fprintf(arqNota, "%s - Quantidade: %d - Valor unitário: R$ %.2f - Subtotal: R$ %.2f\n", p.nome, v.quantidade, p.preco, v.valorTotal);
            total += v.valorTotal;
            algumaVenda = true;
        }
    }

    if (!algumaVenda) {
        fprintf(arqNota, "Nenhuma venda encontrada para este comprador.\n");
    } else {
        fprintf(arqNota, "\nTotal da compra: R$ %.2f\n", total);
    }

    fclose(arqVenda);
    fclose(arqNota);

    printf("Nota fiscal gerada em 'nota_fiscal.txt'\n");
}

// Main
int main() {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Vendedor\n");
        printf("3. Cadastrar Comprador\n");
        printf("4. Registrar Venda\n");
        printf("5. Emitir Nota Fiscal\n");
        printf("6. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: cadastrarVendedor(); break;
            case 3: cadastrarComprador(); break;
            case 4: cadastrarVenda(); break;
            case 5: emitirNotaFiscal(); break;
            case 6: printf("Programa encerrado.\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 6);

    return 0;
}
