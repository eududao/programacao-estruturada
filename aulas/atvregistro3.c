#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

struct Conta {
    int numeroConta;
    char nome[50];
    char cpf[15];
    char telefone[15];
    float saldo;
};

int buscarConta(struct Conta contas[], int numContas, int numeroConta);
void cadastrarConta(struct Conta contas[], int *numContas, int numeroConta);
void consultarSaldo(struct Conta contas[], int numContas, int numeroConta);
void depositar(struct Conta contas[], int numContas, int numeroConta);
void sacar(struct Conta contas[], int numContas, int numeroConta);
void exibirContas(struct Conta contas[], int numContas);

int main() {
    struct Conta contasCorrentes[MAX_CONTAS];
    struct Conta contasPoupancas[MAX_CONTAS];
    int numContasCorrentes = 0, numContasPoupancas = 0;
    int opcao, tipoConta, numeroConta;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar conta corrente\n");
        printf("2. Cadastrar conta poupança\n");
        printf("3. Consultar saldo de uma conta\n");
        printf("4. Depositar em uma conta\n");
        printf("5. Sacar de uma conta\n");
        printf("6. Exibir contas cadastradas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o número da conta corrente: ");
                scanf("%d", &numeroConta);
                cadastrarConta(contasCorrentes, &numContasCorrentes, numeroConta);
                break;
            case 2:
                printf("Informe o número da conta poupança: ");
                scanf("%d", &numeroConta);
                cadastrarConta(contasPoupancas, &numContasPoupancas, numeroConta);
                break;
            case 3:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                printf("Qual tipo de conta? (1 - Corrente, 2 - Poupança): ");
                scanf("%d", &tipoConta);
                if (tipoConta == 1) {
                    consultarSaldo(contasCorrentes, numContasCorrentes, numeroConta);
                } else {
                    consultarSaldo(contasPoupancas, numContasPoupancas, numeroConta);
                }
                break;
            case 4:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                printf("Qual tipo de conta? (1 - Corrente, 2 - Poupança): ");
                scanf("%d", &tipoConta);
                if (tipoConta == 1) {
                    depositar(contasCorrentes, numContasCorrentes, numeroConta);
                } else {
                    depositar(contasPoupancas, numContasPoupancas, numeroConta);
                }
                break;
            case 5:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                printf("Qual tipo de conta? (1 - Corrente, 2 - Poupança): ");
                scanf("%d", &tipoConta);
                if (tipoConta == 1) {
                    sacar(contasCorrentes, numContasCorrentes, numeroConta);
                } else {
                    sacar(contasPoupancas, numContasPoupancas, numeroConta);
                }
                break;
            case 6:
                printf("Qual tipo de conta deseja exibir? (1 - Corrente, 2 - Poupança): ");
                scanf("%d", &tipoConta);
                if (tipoConta == 1) {
                    exibirContas(contasCorrentes, numContasCorrentes);
                } else {
                    exibirContas(contasPoupancas, numContasPoupancas);
                }
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

int buscarConta(struct Conta contas[], int numContas, int numeroConta) {
    if (numContas == 0) {
        return -1; 
    }
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            return i; 
        }
    }
    return -2; 
}

void cadastrarConta(struct Conta contas[], int *numContas, int numeroConta) {
    if (*numContas >= MAX_CONTAS) {
        printf("Limite de contas atingido!\n");
        return;
    }
    
    int pos = buscarConta(contas, *numContas, numeroConta);
    if (pos != -2) {
        printf("Número da conta já cadastrado!\n");
        return;
    }

    struct Conta novaConta;
    novaConta.numeroConta = numeroConta;

    printf("Informe o nome do titular: ");
    scanf(" %[^\n]", novaConta.nome);
    printf("Informe o CPF do titular: ");
    scanf(" %[^\n]", novaConta.cpf);
    printf("Informe o telefone de contato: ");
    scanf(" %[^\n]", novaConta.telefone);
    novaConta.saldo = 0; // Saldo inicial

    contas[*numContas] = novaConta;
    (*numContas)++;
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(struct Conta contas[], int numContas, int numeroConta) {
    int pos = buscarConta(contas, numContas, numeroConta);
    if (pos >= 0) {
        printf("Saldo da conta %d: %.2f\n", numeroConta, contas[pos].saldo);
    } else {
        printf("Conta não está cadastrada.\n");
    }
}

void depositar(struct Conta contas[], int numContas, int numeroConta) {
    int pos = buscarConta(contas, numContas, numeroConta);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor a ser depositado: ");
        scanf("%f", &valor);
        if (valor > 0) {
            contas[pos].saldo += valor;
            printf("Depósito realizado com sucesso! Novo saldo: %.2f\n", contas[pos].saldo);
        } else {
            printf("Valor inválido para depósito.\n");
        }
    } else {
        printf("Conta não está cadastrada.\n");
    }
}

void sacar(struct Conta contas[], int numContas, int numeroConta) {
    int pos = buscarConta(contas, numContas, numeroConta);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor a ser sacado: ");
        scanf("%f", &valor);
        if (valor > 0 && valor <= contas[pos].saldo) {
            contas[pos].saldo -= valor;
            printf("Saque realizado com sucesso! Novo saldo: %.2f\n", contas[pos].saldo);
        } else {
            printf("Saldo insuficiente ou valor inválido para saque.\n");
        }
    } else {
        printf("Conta não está cadastrada.\n");
    }
}

void exibirContas(struct Conta contas[], int numContas) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < numContas; i++) {
        printf("Número da conta: %d, Nome: %s, Telefone: %s\n",
               contas[i].numeroConta, contas[i].nome, contas[i].telefone);
    }
}