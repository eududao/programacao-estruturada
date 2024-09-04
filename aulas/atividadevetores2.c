#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 50

void imprimirVetor(int vetor[], int tam) {
    printf("Vetor: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int buscaBinaria(int vetor[], int tam, int chave) {
    int esq = 0;
    int dir = tam - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (vetor[meio] == chave) {
            return meio;
        }
        if (vetor[meio] < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1;  
}

void inserirEmOrdem(int vetor[], int *tam, int valor) {
    if (*tam >= TAMANHO_MAX) {
        printf("Vetor já está cheio. Não é possível inserir mais elementos.\n");
        return;
    }
    int i = *tam - 1;
    while (i >= 0 && vetor[i] > valor) {
        vetor[i + 1] = vetor[i];
        i--;
    }
    vetor[i + 1] = valor;
    (*tam)++;
}

void removerElemento(int vetor[], int *tam, int valor) {
    int indice = buscaBinaria(vetor, *tam, valor);
    if (indice == -1) {
        printf("Elemento não encontrado.\n");
        return;
    }
    for (int i = indice; i < *tam - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    (*tam)--;
}

int main() {
    int tam;
    int vetor[TAMANHO_MAX];
    
    printf("Digite o tamanho do vetor (entre 3 e 50): ");
    scanf("%d", &tam);
    
    if (tam < 3 || tam > 50) {
        printf("Tamanho inválido. O tamanho deve estar entre 3 e 50.\n");
        return 1;
    }

    int tamanhoAtual = 0;
    printf("Digite %d valores inteiros para preencher o vetor:\n", tam);
    for (int i = 0; i < tam; i++) {
        int valor;
        printf("Valor %d: ", i + 1);
        scanf("%d", &valor);
        inserirEmOrdem(vetor, &tamanhoAtual, valor);
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Imprimir todo o vetor\n");
        printf("2. Consultar (buscar binária)\n");
        printf("3. Remover um elemento\n");
        printf("4. Inserir um elemento\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        
        int opcao;
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            imprimirVetor(vetor, tamanhoAtual);
        } else if (opcao == 2) {
            int valor;
            printf("Digite o valor para consultar: ");
            scanf("%d", &valor);
            int indice = buscaBinaria(vetor, tamanhoAtual, valor);
            if (indice == -1) {
                printf("Elemento não encontrado.\n");
            } else {
                printf("Elemento encontrado na posição: %d\n", indice);
            }
        } else if (opcao == 3) {
            int valor;
            printf("Digite o valor para remover: ");
            scanf("%d", &valor);
            removerElemento(vetor, &tamanhoAtual, valor);
        } else if (opcao == 4) {
            int valor;
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            inserirEmOrdem(vetor, &tamanhoAtual, valor);
        } else if (opcao == 5) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}