#include <stdio.h>

#define TAM 20

int main(){
    int num;
    int numVetor1[TAM];
    print("Digite um valor inteiro.");
    scanf("%d", &num);
    preencherVetorNumero(numVetor1, num);
    imprimirVetor(numVetor1, TAM);
    return 0;
}

void preencherVetorNumero(int v[], int num){
    for (int i = TAM; i >= 0; --i){
        v[i] = num % 10;
        num/ = 10;
    }
    if (num != 0) {
        printf("Erro: Não foi possível inserir esses dígitos: %d\n", num);
    }
}

void imprimirVetor(int v[], int TAM) {
    printf("Vetor: ");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}