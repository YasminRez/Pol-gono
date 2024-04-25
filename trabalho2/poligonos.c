#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float AreaTriangulo(Ponto A, Ponto B, Ponto C);

float AreaPoligono(Ponto *vertices, int num_vertices);

int main() {
    FILE *arquivo;
    arquivo = fopen("poligonos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int num_vertices;
    fscanf(arquivo, "%d", &num_vertices);

    if (num_vertices < 3) {
        printf("Um poligono precisa ter pelo menos 3 vertices.\n");
        exit(1);
    }

    // Alocar de forma dinamica o array
    Ponto *vertices = malloc(num_vertices * sizeof(Ponto));

    for (int i = 0; i < num_vertices; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    float area = AreaPoligono(vertices, num_vertices);

    printf("A area do poligono eh: %.2f\n", area);

    free(vertices);
    fclose(arquivo);

    return 0;
}

float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    float matriz[3][3] = {
        {A.X, A.Y, 1},
        {B.X, B.Y, 1},
        {C.X, C.Y, 1}
    };

    float area = 0.5 * (
        (matriz[0][0] * matriz[1][1] + matriz[1][0] * matriz[2][1] + matriz[2][0] * matriz[0][1]) -
        (matriz[1][0] * matriz[0][1] + matriz[2][0] * matriz[1][1] + matriz[0][0] * matriz[2][1])
    );
    
    return area < 0 ? -area : area;
}


float AreaPoligono(Ponto *vertices, int num_vertices) {
    float area_total = 0;
    
    // Calcular a area de cada triangulo por meio dos vertices consecutivos
    for (int i = 1; i < num_vertices - 1; i++) {
        area_total += AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }
    
    return area_total;
}
