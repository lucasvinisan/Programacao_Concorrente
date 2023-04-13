#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <locale.h>

#define MAX  100
#define SIZE 100000000


double *generate_vector(int number); 
int *generate_vector_int(int number); 

void show_vector_int(int *vector, int size); 
void show_vector(double *vector, int size); 

double *generate_vector(int number){
    double *vector; 
    int cont; 
    vector = (double *)malloc(sizeof(double) * number);
    for(cont = 0; cont < number; cont++){
        double num = (rand() / (float)RAND_MAX);
        vector[cont] = num; 
    }
    return vector; 
}

int *generate_vector_int(int number){
    int *vector;
    int cont;
    vector = (int *)malloc(sizeof(int) * number); 

    for(cont = 0 ; cont < number; cont++){
        int num = (rand() % MAX); 
        vector[cont] = num; 
    }
    return vector; 
}

void show_vector(double *vector, int size){
    int cont;
    for(cont = 0; cont < size; cont++){
        printf("[%.5f]", vector[cont]); 
    }
    printf("\n");    
}

void show_vector_int(int *vector, int size){
    int cont;
    for(cont  = 0; cont < size; cont++){
        printf("%d", vector[cont]); 
    }
    printf("\n"); 
}

int main(){
    setlocale(LC_ALL, "Portuguese"); 
    time_t temp; 
    double start, end; 
    srand(time(NULL)); 
    int *vector = NULL; 

    /*Pode ser o número passado pelo usuário*/

    int number = 7; 
    int cont = 0; 

    vector = generate_vector_int(SIZE); 

    start = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
            for(int i = 0; i < SIZE; i++)
            {
                if(vector[i] == number)
                {
                    cont++; 
                }
            }
    }
    end = omp_get_wtime(); 

    double med_parallel = cont/(float)SIZE; 
    double temp_parallel = end - start;

    printf("Número de ocorrências: %d\n", cont); 
    printf("Média: %lf\n", med_parallel); 
    printf("Tempo Parallel: %lf\n", temp_parallel); 

    cont  = 0;

    /*Sequential*/
    start = omp_get_wtime(); 
    for(int i = 0; i < SIZE; cont++){
        if((vector[cont] == number)){
            cont++; 
        }
    }
    end = omp_get_wtime(); 

    double temp_sequential = end - start; 
    double med_sequential = cont/(double)SIZE;
    double speedup = temp_sequential / temp_parallel; 

    printf("Número de ocorrências: %d\n", cont); 
    printf("Média: %lf\n", med_sequential); 
    printf("Tempo Sequencial: %lf\n", temp_sequential); 
    printf("Speedup: %f\n", speedup);
    double efficiency  = speedup / 4.0;
    printf("Eficiência: %f\n", efficiency); 
    return 0; 
}