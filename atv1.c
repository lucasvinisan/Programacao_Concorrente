#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <stdlib.h>
#include <locale.h>

double *generate_vector(int number){
    double *vector; 
    int cont; 
    vector = (double *)malloc(sizeof(double) * number); 
    for(cont = 0 ; cont < number; cont++){
        double num = (rand() / (double)RAND_MAX); 
        vector[cont] = num; 
    }
    return vector; 
}

void show_vector(float *vector, int size){
    int cont; 
    for(cont = 0; cont < size; cont++){
        printf("[%.5f]", vector[cont]); 
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese"); 
    int SIZE = 100000000; 
    time_t t; 
    srand(time(NULL)); 
    double *vet = NULL; 
    vet = gerar_vetor(SIZE); 
    int cont; 
    double SUM = 0.0;
    double start, end; 


    start = omp_get_wtime(); 
    /*Processamento sequencial*/
    for(cont = 0; cont < SIZE; cont++){
        SUM = SUM + vet[cont]; 
    }
    /*Fim do Processamento sequencial*/

    end = omp_get_wtime(); 
    double med = SUM/(double)SIZE;
    printf("Soma: %lf\n",SUM);
    printf("Media: %lf\n",med);
    double temp_s = end-start;
    printf("Tempo sequencial: %lf\n",temp_s);


    SUM = 0;
    start = omp_get_wtime(); 

    /*Processo paralelo*/
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:SUM)
            for(cont = 0; cont < SIZE; cont++){
                SUM = SUM + vet[cont]; 
            }
    }
    /*end do processo sequencial*/
    med = SUM/(double)SIZE; 
    printf("SUM: %lf\n",SUM);
    printf("med: %lf\n",med);
    double temp_p = end-start;
    printf("Tempo paralelo: %.4f\n",temp_p);
    double speedup = temp_s/temp_p;
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Efiencia: %f\n",eficiencia);
    return 0; 
}
