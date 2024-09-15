#include <stdio.h>

#define QTD_LINHAS 10
#define QTD_COLUNAS 10

void multiplicarMatrizes(int matrizA[QTD_LINHAS][QTD_COLUNAS], int linA, int colA,
                        int matrizB[QTD_LINHAS][QTD_COLUNAS], int linB, int colB,
                        int matrizMult[QTD_LINHAS][QTD_COLUNAS]) {

    if (colA != linB) {
        printf("A multiplicação não pode ser realizada. Número de colunas de matrizA deve ser igual ao número de linhas de matrizB.\n");
        return;
    }
    
    for (int i = 0; i < linA; i++) {
        for (int j = 0; j < colB; j++) {
            matrizMult[i][j] = 0;
        }
    }
    

    for (int i = 0; i < linA; i++) {
        for (int j = 0; j < colB; j++) {
            for (int k = 0; k < colA; k++) {
                matrizMult[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

int main() {
    int matrizA[QTD_LINHAS][QTD_COLUNAS] = {{1, 2}, {3, 4}};
    int matrizB[QTD_LINHAS][QTD_COLUNAS] = {{5, 6}, {7, 8}};
    int matrizMult[QTD_LINHAS][QTD_COLUNAS];
    
    int linA = 2, colA = 2;
    int linB = 2, colB = 2;

    multiplicarMatrizes(matrizA, linA, colA, matrizB, linB, colB, matrizMult);

    for (int i = 0; i < linA; i++) {
        for (int j = 0; j < colB; j++) {
            printf("%d ", matrizMult[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}