#include <stdio.h>

void inserir_ordenado(int vetor[], int *n, int valor) {
    int i = 0;
    
    while (i < *n && vetor[i] < valor) {
        i++;
    }
    
    for (int j = *n; j > i; j--) {
        vetor[j] = vetor[j - 1];
    }
    
    vetor[i] = valor;
    (*n)++;
}

int main() {
    int qtd;
    
    printf("Digite a quantidade de valores: ");
    scanf("%d", &qtd);
    
    if (qtd <= 0) {
        printf("A quantidade de valores deve ser maior que zero.\n");
        return 1;
    }
    
    int vetor[qtd];
    int n = 0; 
    
    for (int i = 0; i < qtd; i++) {
        int valor;
        
        printf("Digite um valor: ");
        scanf("%d", &valor);
        
        inserir_ordenado(vetor, &n, valor);
    }
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    
    return 0;
}