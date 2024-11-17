#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VIDEOS_FAVORITOS 10
#define MAX_NOME 100

typedef struct {
    int id;  
    char titulo[MAX_NOME];  
    char descricao[MAX_NOME];  
    int ano;  
} Video;

typedef struct {
    int id;  
    char nome[MAX_NOME];  
    int favoritos[MAX_VIDEOS_FAVORITOS];  
    int num_favoritos;  
} Usuario;

void gravar_video(FILE *fp, Video v) {
    fseek(fp, 0, SEEK_END);
    fwrite(&v, sizeof(Video), 1, fp);
}

void gravar_usuario(FILE *fp, Usuario u) {
    fseek(fp, 0, SEEK_END);
    fwrite(&u, sizeof(Usuario), 1, fp);
}

void listar_videos(FILE *fp) {
    Video v;
    fseek(fp, 0, SEEK_SET);
    while (fread(&v, sizeof(Video), 1, fp)) {
        printf("ID: %d\nTítulo: %s\nDescrição: %s\nAno: %d\n\n", v.id, v.titulo, v.descricao, v.ano);
    }
}

void listar_usuarios(FILE *fp_usuarios, FILE *fp_videos) {
    Usuario u;
    Video v;
    fseek(fp_usuarios, 0, SEEK_SET);
    while (fread(&u, sizeof(Usuario), 1, fp_usuarios)) {
        printf("ID Usuário: %d\nNome: %s\nVídeos Favoritos:\n", u.id, u.nome);
        for (int i = 0; i < u.num_favoritos; i++) {
            fseek(fp_videos, (u.favoritos[i] - 1) * sizeof(Video), SEEK_SET);  
            fread(&v, sizeof(Video), 1, fp_videos);
            printf("\tTítulo: %s (ID: %d)\n", v.titulo, v.id);
        }
        printf("\n");
    }
}

void atualizar_video(FILE *fp, Video v) {
    Video temp;
    fseek(fp, 0, SEEK_SET);
    while (fread(&temp, sizeof(Video), 1, fp)) {
        if (temp.id == v.id) {
            fseek(fp, -sizeof(Video), SEEK_CUR);
            fwrite(&v, sizeof(Video), 1, fp);
            fflush(fp);  
            return;
        }
    }
    printf("Vídeo com ID %d não encontrado para atualização.\n", v.id);
}

void atualizar_usuario(FILE *fp, Usuario u) {
    Usuario temp;
    fseek(fp, 0, SEEK_SET);
    while (fread(&temp, sizeof(Usuario), 1, fp)) {
        if (temp.id == u.id) {
            fseek(fp, -sizeof(Usuario), SEEK_CUR);
            fwrite(&u, sizeof(Usuario), 1, fp);
            fflush(fp);  
            return;
        }
    }
    printf("Usuário com ID %d não encontrado para atualização.\n", u.id);
}

void remover_video(FILE *fp, int id_video) {
    FILE *temp_fp = fopen("videos_temp.bin", "wb");
    Video v;
    fseek(fp, 0, SEEK_SET);
    while (fread(&v, sizeof(Video), 1, fp)) {
        if (v.id != id_video) {
            fwrite(&v, sizeof(Video), 1, temp_fp);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("videos.bin");
    rename("videos_temp.bin", "videos.bin");
}

void remover_usuario(FILE *fp, int id_usuario) {
    FILE *temp_fp = fopen("usuarios_temp.bin", "wb");
    Usuario u;
    fseek(fp, 0, SEEK_SET);
    while (fread(&u, sizeof(Usuario), 1, fp)) {
        if (u.id != id_usuario) {
            fwrite(&u, sizeof(Usuario), 1, temp_fp);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("usuarios.bin");
    rename("usuarios_temp.bin", "usuarios.bin");
}

int main() {
    FILE *videos_fp = fopen("videos.bin", "rb+");
    if (videos_fp == NULL) videos_fp = fopen("videos.bin", "wb");

    FILE *usuarios_fp = fopen("usuarios.bin", "rb+");
    if (usuarios_fp == NULL) usuarios_fp = fopen("usuarios.bin", "wb");

    int opcao;
    do {
        printf("1. Cadastrar Vídeo\n");
        printf("2. Cadastrar Usuário\n");
        printf("3. Atualizar Vídeo\n");
        printf("4. Atualizar Usuário\n");
        printf("5. Listar Vídeos\n");
        printf("6. Listar Usuários e seus Favoritos\n");
        printf("7. Remover Vídeo\n");
        printf("8. Remover Usuário\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  

        if (opcao == 1) {
            Video v;
            printf("Informe o ID do vídeo: ");
            scanf("%d", &v.id);
            getchar();  
            printf("Informe o título do vídeo: ");
            fgets(v.titulo, MAX_NOME, stdin);
            v.titulo[strcspn(v.titulo, "\n")] = '\0';  
            printf("Informe a descrição do vídeo: ");
            fgets(v.descricao, MAX_NOME, stdin);
            v.descricao[strcspn(v.descricao, "\n")] = '\0';  
            printf("Informe o ano de lançamento: ");
            scanf("%d", &v.ano);

            gravar_video(videos_fp, v);
        } else if (opcao == 2) {
            Usuario u;
            printf("Informe o ID do usuário: ");
            scanf("%d", &u.id);
            getchar();  
            printf("Informe o nome do usuário: ");
            fgets(u.nome, MAX_NOME, stdin);
            u.nome[strcspn(u.nome, "\n")] = '\0';  

            printf("Quantos vídeos você quer favoritar? ");
            scanf("%d", &u.num_favoritos);
            for (int i = 0; i < u.num_favoritos; i++) {
                printf("Informe o ID do vídeo %d: ", i + 1);
                scanf("%d", &u.favoritos[i]);
            }

            gravar_usuario(usuarios_fp, u);
        } else if (opcao == 3) {
            Video v;
            printf("Informe o ID do vídeo a ser atualizado: ");
            scanf("%d", &v.id);
            getchar();  
            printf("Informe o título do vídeo: ");
            fgets(v.titulo, MAX_NOME, stdin);
            v.titulo[strcspn(v.titulo, "\n")] = '\0';  
            printf("Informe a descrição do vídeo: ");
            fgets(v.descricao, MAX_NOME, stdin);
            v.descricao[strcspn(v.descricao, "\n")] = '\0';  
            printf("Informe o ano de lançamento: ");
            scanf("%d", &v.ano);

            atualizar_video(videos_fp, v);
        } else if (opcao == 4) {
            Usuario u;
            printf("Informe o ID do usuário a ser atualizado: ");
            scanf("%d", &u.id);
            getchar();  // Limpa o buffer
            printf("Informe o nome do usuário: ");
            fgets(u.nome, MAX_NOME, stdin);
            u.nome[strcspn(u.nome, "\n")] = '\0';  

            printf("Quantos vídeos você quer favoritar? ");
            scanf("%d", &u.num_favoritos);
            for (int i = 0; i < u.num_favoritos; i++) {
                printf("Informe o ID do vídeo %d: ", i + 1);
                scanf("%d", &u.favoritos[i]);
            }

            atualizar_usuario(usuarios_fp, u);
        } else if (opcao == 5) {
            listar_videos(videos_fp);
        } else if (opcao == 6) {
            listar_usuarios(usuarios_fp, videos_fp);
        } else if (opcao == 7) {
            int id_video;
            printf("Informe o ID do vídeo a ser removido: ");
            scanf("%d", &id_video);
            remover_video(videos_fp, id_video);
        } else if (opcao == 8) {
            int id_usuario;
            printf("Informe o ID do usuário a ser removido: ");
            scanf("%d", &id_usuario);
            remover_usuario(usuarios_fp, id_usuario);
        }

    } while (opcao != 0);

    fclose(videos_fp);
    fclose(usuarios_fp);

    return 0;
}