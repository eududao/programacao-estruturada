#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QTD_LINHAS 100
#define QTD_COLUNAS 100

void lerMatriz(int mat[][QTD_COLUNAS], int lin, int col);
void preencherMatrizAleatoria(int mat[][QTD_COLUNAS], int lin, int col);
void imprimirMatriz(int mat[][QTD_COLUNAS], int lin, int col);

int lerDentroIntervalo(int min, int max);
int contarImpares(int mat[][QTD_COLUNAS], int lin, int col);
void procurarElemento(int mat[][QTD_COLUNAS], int lin, int col, int elem);
int somarElementos(int mat[][QTD_COLUNAS], int lin, int col);
float calcularMedia(int mat[][QTD_COLUNAS], int lin, int col);
void imprimirMediaPorLinha(int mat[][QTD_COLUNAS], int lin, int col);

int main() {
    int qtdLinhas, qtdColunas;
    int matriz[QTD_LINHAS][QTD_COLUNAS];

    srand(time(0));

    printf("Digite a quantidade de linhas (1-%d): ", QTD_LINHAS);
    qtdLinhas = lerDentroIntervalo(1, QTD_LINHAS);
    printf("Digite a quantidade de colunas (1-%d): ", QTD_COLUNAS);
    qtdColunas = lerDentroIntervalo(1, QTD_COLUNAS);

    preencherMatrizAleatoria(matriz, qtdLinhas, qtdColunas);
    printf("\n--------------------\n");
    imprimirMatriz(matriz, qtdLinhas, qtdColunas);

    int quantidadeImpares = contarImpares(matriz, qtdLinhas, qtdColunas);
    printf("Quantidade de números ímpares: %d\n", quantidadeImpares);

    int elemento;
    printf("Digite um elemento para procurar: ");
    scanf("%d", &elemento);
    procurarElemento(matriz, qtdLinhas, qtdColunas, elemento);

    int somatorio = somarElementos(matriz, qtdLinhas, qtdColunas);
    printf("Somatório de todos os elementos: %d\n", somatorio);

    float media = calcularMedia(matriz, qtdLinhas, qtdColunas);
    printf("Média de todos os elementos: %.2f\n", media);

    printf("Média de elementos por linha:\n");
    imprimirMediaPorLinha(matriz, qtdLinhas, qtdColunas);

    return 0;
}

void lerMatriz(int mat[][QTD_COLUNAS], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("Digite mat[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

void preencherMatrizAleatoria(int mat[][QTD_COLUNAS], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            mat[i][j] = rand() % 100 + 1;
        }
    }
}

void imprimirMatriz(int mat[][QTD_COLUNAS], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int lerDentroIntervalo(int min, int max) {
    int valor;
    scanf("%d", &valor);
    while (valor < min || valor > max) {
        printf("Valor invalido! Digite valor entre %d e %d: ", min, max);
        scanf("%d", &valor);
    }
    return valor;
}

int contarImpares(int mat[][QTD_COLUNAS], int lin, int col) {
    int cont = 0;
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            if (mat[i][j] % 2 != 0) {
                ++cont;
            }
        }
    }
    return cont;
}

void procurarElemento(int mat[][QTD_COLUNAS], int lin, int col, int elem) {
    int encontrado = 0;
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            if (mat[i][j] == elem) {
                printf("Elemento %d encontrado na linha %d e coluna %d.\n", elem, i, j);
                encontrado = 1;
                break;
            }
        }
        if (encontrado) break;
    }
    if (!encontrado) {
        printf("Elemento %d não encontrado na matriz.\n", elem);
    }
}

int somarElementos(int mat[][QTD_COLUNAS], int lin, int col) {
    int soma = 0;
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            soma += mat[i][j];
        }
    }
    return soma;
}

float calcularMedia(int mat[][QTD_COLUNAS], int lin, int col) {
    int soma = somarElementos(mat, lin, col);
    int totalElementos = lin * col;
    return (float)soma / totalElementos;
}

void imprimirMediaPorLinha(int mat[][QTD_COLUNAS], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        int somaLinha = 0;
        for (int j = 0; j < col; ++j) {
            somaLinha += mat[i][j];
        }
        float mediaLinha = (float)somaLinha / col;
        printf("Média da linha %d: %.2f\n", i, mediaLinha);
    }
}
