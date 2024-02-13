//Delikatnyi Artem 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

void get_neigh(int *cur_ver, int **matrix, int **visited, int **neighb, int number_of_vertex){
    for (int i = 0; i < number_of_vertex; i++){
        if (((matrix[*cur_ver][i]) != 0) && ((*visited)[i] != 1)){
            (*neighb)[i] = 1;
        }
    }
}


int get_min(int *visited, int *values, int number_of_vertex){
    int min_val = INT_MAX, index = -1;
    for (int i = 0; i < number_of_vertex; i++){
        if (((visited)[i] != 1) && ((values)[i] < min_val)){
            min_val = (values)[i];
            index = i;
        }
    }
    return index;
}


void dijkstra(int *cur_vertex, int **visited, int **values, int **matrix, int number_of_vertex){
    while (true){
        int *neighb = (int*)calloc(number_of_vertex, sizeof(int));
        get_neigh(cur_vertex, matrix, visited, &neighb, number_of_vertex);
        for (int i = 0; i < number_of_vertex; i++){
            if (neighb[i] == 1){
                int cur_value;
                cur_value = (*values)[*cur_vertex] + matrix[*cur_vertex][i];
                if (cur_value < (*values)[i]){
                    (*values)[i] = cur_value;
                }
            }
        }
        (*visited)[*cur_vertex] = 1;
        *cur_vertex = get_min(*visited, *values, number_of_vertex);
        if (*cur_vertex == -1){
            break;
        }
    }

    printf("\nTable of distances beetween verticles:\n");
    printf("(0 on the main diagonal represent the distance from a vertex to itself)\n");
    printf("(0 on another place - represent that it is not possible to reach to this vertex)\n\n");
    for (int i = 0; i < number_of_vertex; i++){
        for (int j = 0; j < number_of_vertex; j++){
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------------------\n");

    printf("The closest distance to each vertex:\n");
    for (int i = 0; i < number_of_vertex; i++){
        printf("%4d ", i+1);
    }
    printf("\n");
    for (int i = 0; i < number_of_vertex; i++){
        printf("%4d ", (*values)[i]);
    }
    printf("\n\n");


}


int main(){
    int mode = 7;

    while (1){

        printf("Decide the mode:\n");
        printf("1 - Static mode (all data has already been entered).\n");
        printf("2 - Dynamic mode (you need to eneter data by yourself).\n");
        printf("0 - Close program.\n");

        scanf("%d", &mode);
        if (mode == 0){
            printf("Thanks for using! Have a good day!\n");
            break;
        }

        if (mode == 2){
            int cur_vertex = 0;
            int number_of_vertex;
            printf("Write the number of vertex: ");
            scanf("%d", &number_of_vertex);

            int *visited = (int *)malloc(sizeof(int)*number_of_vertex);
            int *values = (int *)malloc(sizeof(int)*number_of_vertex);
            for (int i = 0; i < number_of_vertex; i++){
                if (i == 0){
                    values[i] = 0;
                }
                else{
                    values[i] = INT_MAX;
                }
            }


            int **matrix;
            matrix = (int**)malloc(sizeof(int*)*number_of_vertex);
            for (int i = 0; i < number_of_vertex; i++){
                matrix[i] = (int*)malloc(sizeof(int)*number_of_vertex);
            }


            printf("-> if the vertex goed into itself or there is no access to the vertex - insert 0\n");
            for (int i = 0; i < number_of_vertex; i++){
                printf("-> write the data for the %d row seperated by the space:\n", i+1);
                for (int j = 0; j < number_of_vertex; j++){
                    scanf("%d", &(matrix[i][j]));
                }
            }
            dijkstra(&cur_vertex, &visited, &values, matrix, number_of_vertex);
        }
        else if (mode == 1){
            int number_of_vertex = 7;
            int cur_vertex = 0;

            int *visited = (int *)malloc(sizeof(int)*number_of_vertex);
            int *values = (int *)malloc(sizeof(int)*number_of_vertex);
            for (int i = 0; i < number_of_vertex; i++){
                if (i == 0){
                    values[i] = 0;
                }
                else{
                    values[i] = INT_MAX;
                }
            }

            int **matrix;
            matrix = (int**)malloc(sizeof(int*)*number_of_vertex);
            for (int i = 0; i < number_of_vertex; i++){
                matrix[i] = (int*)malloc(sizeof(int)*number_of_vertex);
            }

            int matrix_stat[7][7] = {
                {0, 2448, 712, 1419, 81, 2142, 1583},
                {2448, 0, 1744, 1372, 2391, 357, 1203},
                {712, 1744, 0, 943, 664, 1453, 1054},
                {1419, 1372, 943, 0, 1341, 1015, 189},
                {81, 2391, 664, 1341, 0, 2080, 1507},
                {2142, 357, 1453, 1015, 2080, 0, 848},
                {1583, 1203, 1054, 189, 1507, 848, 0}
            };

            for (int i = 0; i < number_of_vertex; i++){
                for (int j = 0; j < number_of_vertex; j++){
                    matrix[i][j] = matrix_stat[i][j];
                }
            }

            dijkstra(&cur_vertex, &visited, &values, matrix, number_of_vertex);
        }

    }



    return 0;
}