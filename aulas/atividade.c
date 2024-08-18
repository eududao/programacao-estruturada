#include <stdio.h>

void imprimirnumeros() {
    for (int i = 1; i <= 100; i++) {
        if (i == 100) {
            printf("%d\n", i);
        } else {
            printf("%d, ", i);
        }
    }
}

void somatorioimpares() {
    int soma = 0; 
    for (int i = 11; i < 1000; i += 2) {
        soma += i;    
    }
    printf("%d\n", soma);
}

void imprimirmultiplosde3() {
    for (int i = 3; i <= 200; i += 3) {
        if (i % 10 != 3) {
            if (i == 198) {
                printf("%d\n", i);
            } else {
                printf("%d, ", i);
            }
        }
    }
}

int main() {
    printf("Números de 1 a 100: ");
    imprimirnumeros();

    printf("Somatório dos ímpares entre 10 e 1000: ");
    somatorioimpares();

    printf("Múltiplos de 3 que não terminam em 3 entre 1 e 200: ");
    imprimirmultiplosde3();
    
    return 0;
}