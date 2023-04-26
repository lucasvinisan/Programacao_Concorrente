#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <locale.h>
#define MAX 1000000

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
    /*Não concluida */

    int number[MAX]; 
    #pragma omp parallel for
    for(int i = 0; i < MAX; i++){

    }
    return 0; 
}