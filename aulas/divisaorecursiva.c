#include <stdio.h>

int divisao(int dividendo, int divisor) {
    if (dividendo < divisor) {
        return 0;
    }
    return 1 + divisao(dividendo - divisor, divisor);
}

int main() {
    int dividendo, divisor;
    printf("Digite o dividendo: ");
    scanf("%d", &dividendo);
    printf("Digite o divisor: ");
    scanf("%d", &divisor);

    int resultado = divisao(dividendo, divisor);
    printf("Resultado da divisão: %d\n", resultado);

    return 0;
}