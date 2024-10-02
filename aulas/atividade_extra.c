#include <stdio.h>
#include <stdlib.h>

#define M 5 // Número de linhas da matriz
#define N 4 // Número de colunas da matriz

// Declaração das funções
void preencherMatriz(int m[][N], int lin, int col);
void imprimirMatriz(int m[][N], int lin, int col);
void maiorCadaColuna(int m[][N], int lin, int col, int v[]);
void imprimirVetor(int v[], int tam);
void linhaOuColunaMaisRepetidos(int m[][N], int lin, int col);

int main() {
    int matriz[M][N]; // Matriz de MxN
    int vetor[N];     // Vetor para armazenar os maiores valores de cada coluna
    int opcao;       // Variável para armazenar a opção do usuário

    do {
        // Exibe o menu
        printf("\nMENU\n\n");
        printf("1 - preencher matriz com aleatorios\n");
        printf("2 - Maior cada coluna\n");
        printf("3 - Linha ou Coluna com mais repetidos\n");
        printf("0 - Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao); // Lê a opção do usuário

        switch (opcao) {
            case 1:
                // Preenche a matriz com números aleatórios e imprime
                preencherMatriz(matriz, M, N);
                imprimirMatriz(matriz, M, N);
                break;
            case 2:
                // Calcula e imprime o maior elemento de cada coluna
                maiorCadaColuna(matriz, M, N, vetor);
                imprimirVetor(vetor, N);
                break;
            case 3:
                // Encontra e imprime a linha ou coluna com mais números repetidos
                linhaOuColunaMaisRepetidos(matriz, M, N);
                break;
            default:
                break; // Caso a opção não seja válida
        }
    } while (opcao != 0); // Continua até o usuário escolher sair

    return 0; // Finaliza o programa
}

// Preenche a matriz com números aleatórios de 1 a 100
void preencherMatriz(int m[][N], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            m[i][j] = rand() % 100 + 1; // Gera número aleatório
        }
    }
}

// Imprime a matriz formatada
void imprimirMatriz(int m[][N], int lin, int col) {
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%3d ", m[i][j]); // Imprime cada elemento
        }
        printf("\n"); 
    }
}

// Encontra o maior elemento de cada coluna da matriz
void maiorCadaColuna(int m[][N], int lin, int col, int v[]) {
    for (int j = 0; j < col; ++j) {
        int maior = m[0][j]; // Inicializa o maior como o primeiro elemento da coluna
        for (int i = 1; i < lin; ++i) {
            if (m[i][j] > maior) {
                maior = m[i][j]; // Atualiza o maior se encontrar um número maior
            }
        }
        v[j] = maior; // Armazena o maior número no vetor
    }
}

// Imprime os elementos do vetor
void imprimirVetor(int v[], int tam) {
    for (int i = 0; i < tam; ++i) {
        printf("%d ", v[i]); // Imprime cada elemento do vetor
    }
    printf("\n"); // Nova linha ao final
}

// Encontra a linha ou coluna com mais números repetidos
void linhaOuColunaMaisRepetidos(int m[][N], int lin, int col) {
    int maxRepetidos = 0; // Para armazenar o máximo de repetições
    int indiceMaisRepetido = -1;   // Para armazenar o índice da linha ou coluna com mais repetições
    int tipo = -1;        // 0 para linha, 1 para coluna

    // Verifica as linhas
    for (int i = 0; i < lin; ++i) {
        int contagem[101] = {0}; // Array para contar as ocorrências de números (1 a 100)
        int repetidos = 0;        // Contador de repetições

        for (int j = 0; j < col; ++j) {
            contagem[m[i][j]]++; // Incrementa a contagem para o número atual
        }

        // Conta o total de números repetidos
        for (int k = 1; k <= 100; ++k) {
            if (contagem[k] > 1) {
                repetidos += contagem[k]; // Soma as repetições
            }
        }

        // Atualiza se a linha atual tem mais repetições
        if (repetidos > maxRepetidos) {
            maxRepetidos = repetidos; // Atualiza o máximo
            indiceMaisRepetido = i;            // Atualiza o índice da linha
            tipo = 0;                 // Marca como linha
        }
    }

    // Verifica as colunas
    for (int j = 0; j < col; ++j) {
        int contagem[101] = {0}; // Array para contar as ocorrências de números
        int repetidos = 0;        // Contador de repetições

        for (int i = 0; i < lin; ++i) {
            contagem[m[i][j]]++; // Incrementa a contagem para o número atual
        }

        // Conta o total de números repetidos
        for (int k = 1; k <= 100; ++k) {
            if (contagem[k] > 1) {
                repetidos += contagem[k]; // Soma as repetições
            }
        }

        // Atualiza se a coluna atual tem mais repetições
        if (repetidos > maxRepetidos) {
            maxRepetidos = repetidos; // Atualiza o máximo
            indiceMaisRepetido = j;            // Atualiza o índice da coluna
            tipo = 1;                 // Marca como coluna
        }
    }

    // Exibe o resultado
    if (tipo == 0) {
        printf("A linha com mais numeros repetidos e a linha %d com %d repeticoes.\n", indiceMaisRepetido, maxRepetidos);
    } else if (tipo == 1) {
        printf("A coluna com mais numeros repetidos e a coluna %d com %d repeticoes.\n", indiceMaisRepetido, maxRepetidos);
    } else {
        printf("Nao foram encontrados numeros repetidos.\n");
    }
}
