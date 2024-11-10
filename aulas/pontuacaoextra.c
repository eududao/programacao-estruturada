#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void geraVetor(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 1000000;  
    }
}

void vetorCrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
    }
}

void vetorDecrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;
    }
}

void imprimeVetor(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubbleSort(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int* vetor, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

void selectionSort(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        int temp = vetor[min_idx];
        vetor[min_idx] = vetor[i];
        vetor[i] = temp;
    }
}

double medirTempo(void (*ordenacao)(int*, int), int* vetor, int tamanho) {
    clock_t inicio = clock();
    ordenacao(vetor, tamanho);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000; // Retorna o tempo em milissegundos
}

int main() {

    int tamanhos[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    
    for (int i = 0; i < numTamanhos; i++) {
        int tamanho = tamanhos[i];
        
        int* vetor = (int*)malloc(tamanho * sizeof(int));
        
        geraVetor(vetor, tamanho);
        double tempoBubbleDesordenado = medirTempo(bubbleSort, vetor, tamanho);
        
        vetorCrescente(vetor, tamanho);
        double tempoBubbleCrescente = medirTempo(bubbleSort, vetor, tamanho);
        
        vetorDecrescente(vetor, tamanho);
        double tempoBubbleDecrescente = medirTempo(bubbleSort, vetor, tamanho);
        
        printf("Bubble Sort - Tamanho: %d, Desordenado: %.3fms, Crescente: %.3fms, Decrescente: %.3fms\n",
               tamanho, tempoBubbleDesordenado, tempoBubbleCrescente, tempoBubbleDecrescente);
        
        geraVetor(vetor, tamanho);
        double tempoInsertionDesordenado = medirTempo(insertionSort, vetor, tamanho);
        
        vetorCrescente(vetor, tamanho);
        double tempoInsertionCrescente = medirTempo(insertionSort, vetor, tamanho);
        
        vetorDecrescente(vetor, tamanho);
        double tempoInsertionDecrescente = medirTempo(insertionSort, vetor, tamanho);
        
        printf("Insertion Sort - Tamanho: %d, Desordenado: %.3fms, Crescente: %.3fms, Decrescente: %.3fms\n",
               tamanho, tempoInsertionDesordenado, tempoInsertionCrescente, tempoInsertionDecrescente);
        
        geraVetor(vetor, tamanho);
        double tempoSelectionDesordenado = medirTempo(selectionSort, vetor, tamanho);
        
        vetorCrescente(vetor, tamanho);
        double tempoSelectionCrescente = medirTempo(selectionSort, vetor, tamanho);
        
        vetorDecrescente(vetor, tamanho);
        double tempoSelectionDecrescente = medirTempo(selectionSort, vetor, tamanho);
        
        printf("Selection Sort - Tamanho: %d, Desordenado: %.3fms, Crescente: %.3fms, Decrescente: %.3fms\n",
               tamanho, tempoSelectionDesordenado, tempoSelectionCrescente, tempoSelectionDecrescente);
        
        free(vetor);
    }
    
    return 0;
}
