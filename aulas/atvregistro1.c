#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 26

struct EstadoInfo {
    char nome[50];
    int numeroVeiculos;
    int numeroAcidentes;
};

void coletarDados(struct EstadoInfo estados[]);
void encontrarMaiorMenor(struct EstadoInfo estados[], int *indiceMaior, int *indiceMenor);
float calcularPercentual(struct EstadoInfo estados[], int estado);
float calcularMedia(struct EstadoInfo estados[]);
void estadosAcimaMedia(struct EstadoInfo estados[], float media);

int main() {
    struct EstadoInfo estados[NUM_ESTADOS];
    int indiceMaior, indiceMenor;
    float media;

    coletarDados(estados);
    encontrarMaiorMenor(estados, &indiceMaior, &indiceMenor);

    printf("Maior número de acidentes: %d em %s\n", estados[indiceMaior].numeroAcidentes, estados[indiceMaior].nome);
    printf("Menor número de acidentes: %d em %s\n", estados[indiceMenor].numeroAcidentes, estados[indiceMenor].nome);

    media = calcularMedia(estados);
    printf("Média de acidentes no país: %.2f\n", media);

    printf("Percentuais de veículos envolvidos em acidentes:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        float percentual = calcularPercentual(estados, i);
        printf("%s: %.2f%%\n", estados[i].nome, percentual);
    }

    printf("Estados com acidentes acima da média:\n");
    estadosAcimaMedia(estados, media);

    return 0;
}

void coletarDados(struct EstadoInfo estados[]) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("Informe o nome do estado %d: ", i + 1);
        scanf(" %[^\n]", estados[i].nome);
        printf("Informe o número de veículos: ");
        scanf("%d", &estados[i].numeroVeiculos);
        printf("Informe o número de acidentes: ");
        scanf("%d", &estados[i].numeroAcidentes);
    }
}

void encontrarMaiorMenor(struct EstadoInfo estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].numeroAcidentes > estados[*indiceMaior].numeroAcidentes) {
            *indiceMaior = i;
        }
        if (estados[i].numeroAcidentes < estados[*indiceMenor].numeroAcidentes) {
            *indiceMenor = i;
        }
    }
}

float calcularPercentual(struct EstadoInfo estados[], int estado) {
    if (estados[estado].numeroVeiculos == 0) return 0.0;
    return (float)estados[estado].numeroAcidentes / estados[estado].numeroVeiculos * 100;
}

float calcularMedia(struct EstadoInfo estados[]) {
    int totalAcidentes = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        totalAcidentes += estados[i].numeroAcidentes;
    }
    return (float)totalAcidentes / NUM_ESTADOS;
}

void estadosAcimaMedia(struct EstadoInfo estados[], float media) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].numeroAcidentes > media) {
            printf("%s\n", estados[i].nome);
        }
    }
}