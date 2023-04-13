#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <omp.h>

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
    srand(time(NULL)); 
    int *vector = NULL; 

    vector = generate_vector_int(SIZE); 
    double sum = 0.0; /*Soma*/
    double start, end; 


    start = omp_get_wtime(); 
    /*Sequential peocess*/
    for(int i  = 0 ; i < SIZE; i++){
        sum = sum + vector[i]; 
    }
    end = omp_get_wtime(); 

    double time_sequential = end - start; 
    double med = sum / (double)SIZE;


    printf("Média: %lf\n", med);
    printf("soma: %lf\n", sum); 
    printf("Tempo sequencial: %lf\n", time_sequential); 

    double sum_parallel; 

    start = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omr for reduction(+:soma)
            for(int j = 0; j < SIZE; j++){
                sum_parallel += vector[j];
            }
    }
    end = omp_get_wtime(); 
    double time_parallel = end - start; 
    double med_parallel = sum_parallel / (double)MAX; 
    double Speedup = time_sequential / time_parallel; 
    double efficiency = Speedup / 3.0; 

    printf("Média: %lf\n", med_parallel);
    printf("soma: %lf\n", sum_parallel); 
    printf("Tempo sequencial: %lf\n", time_sequential);
    printf("Eficiência: %lf\n", efficiency); 
    printf("Speedup: %lf\n", Speedup); 

    return 0; 
}