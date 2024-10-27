#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40

struct Produto {
    int codigo;
    char descricao[50];
    float valorUnitario;
    int quantidadeEstoque;
};

void cadastrarProduto(struct Produto produtos[], int *numProdutos);
void alterarValorUnitario(struct Produto produtos[], int numProdutos);
float obterValorUnitario(struct Produto produtos[], int numProdutos, int codigo);
int obterQuantidadeEstoque(struct Produto produtos[], int numProdutos, int codigo);
void realizarVenda(struct Produto produtos[], int numProdutos);
void atualizarQuantidadeEstoque(struct Produto produtos[], int numProdutos);
void exibirProdutos(struct Produto produtos[], int numProdutos);
void exibirProdutosEstoqueZero(struct Produto produtos[], int numProdutos);

int main() {
    struct Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Alterar valor unitário de um produto\n");
        printf("3. Obter valor unitário de um produto\n");
        printf("4. Obter quantidade em estoque de um produto\n");
        printf("5. Realizar venda\n");
        printf("6. Atualizar quantidade em estoque de um produto\n");
        printf("7. Exibir todos os produtos\n");
        printf("8. Exibir produtos com estoque zero\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &numProdutos);
                break;
            case 2:
                alterarValorUnitario(produtos, numProdutos);
                break;
            case 3: {
                int codigo;
                printf("Informe o código do produto: ");
                scanf("%d", &codigo);
                float valor = obterValorUnitario(produtos, numProdutos, codigo);
                if (valor >= 0) {
                    printf("Valor unitário: %.2f\n", valor);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 4: {
                int codigo;
                printf("Informe o código do produto: ");
                scanf("%d", &codigo);
                int quantidade = obterQuantidadeEstoque(produtos, numProdutos, codigo);
                if (quantidade >= 0) {
                    printf("Quantidade em estoque: %d\n", quantidade);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 5:
                realizarVenda(produtos, numProdutos);
                break;
            case 6:
                atualizarQuantidadeEstoque(produtos, numProdutos);
                break;
            case 7:
                exibirProdutos(produtos, numProdutos);
                break;
            case 8:
                exibirProdutosEstoqueZero(produtos, numProdutos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarProduto(struct Produto produtos[], int *numProdutos) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    struct Produto novoProduto;
    printf("Informe o código do produto: ");
    scanf("%d", &novoProduto.codigo);
    printf("Informe a descrição do produto: ");
    scanf(" %[^\n]", novoProduto.descricao);
    printf("Informe o valor unitário: ");
    scanf("%f", &novoProduto.valorUnitario);
    printf("Informe a quantidade em estoque: ");
    scanf("%d", &novoProduto.quantidadeEstoque);

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;
    printf("Produto cadastrado com sucesso!\n");
}

void alterarValorUnitario(struct Produto produtos[], int numProdutos) {
    int codigo;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Novo valor unitário: ");
            scanf("%f", &produtos[i].valorUnitario);
            printf("Valor unitário alterado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

float obterValorUnitario(struct Produto produtos[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].valorUnitario;
        }
    }
    return -1; 
}

int obterQuantidadeEstoque(struct Produto produtos[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].quantidadeEstoque;
        }
    }
    return -1; 
}

void realizarVenda(struct Produto produtos[], int numProdutos) {
    int codigo, quantidade;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    printf("Informe a quantidade desejada: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            if (produtos[i].quantidadeEstoque == 0) {
                printf("Estoque zerado! Produto não disponível para venda.\n");
                return;
            }
            if (quantidade > produtos[i].quantidadeEstoque) {
                char resposta;
                printf("Quantidade desejada maior que a disponível (%d). Deseja efetivar a compra? (s/n): ", produtos[i].quantidadeEstoque);
                scanf(" %c", &resposta);
                if (resposta == 's' || resposta == 'S') {
                    printf("Valor a ser pago: %.2f\n", produtos[i].valorUnitario * produtos[i].quantidadeEstoque);
                    produtos[i].quantidadeEstoque = 0; // Zera o estoque
                } else {
                    printf("Compra não efetivada.\n");
                }
            } else {
                produtos[i].quantidadeEstoque -= quantidade; // Subtrai a quantidade vendida
                printf("Valor a ser pago: %.2f\n", produtos[i].valorUnitario * quantidade);
            }
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void atualizarQuantidadeEstoque(struct Produto produtos[], int numProdutos) {
    int codigo, novaQuantidade;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Nova quantidade em estoque: ");
            scanf("%d", &novaQuantidade);
            produtos[i].quantidadeEstoque = novaQuantidade;
            printf("Quantidade atualizada com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void exibirProdutos(struct Produto produtos[], int numProdutos) {
    printf("\nLista de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Código: %d, Descrição: %s, Valor: %.2f, Estoque: %d\n",
               produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
    }
}

void exibirProdutosEstoqueZero(struct Produto produtos[], int numProdutos) {
    printf("\nProdutos com Estoque Zero:\n");
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].quantidadeEstoque == 0) {
            printf("Código: %d, Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto com estoque zero.\n");
    }
}