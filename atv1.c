#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <stdlib.h>
#include <locale.h>

double *gerar_vetor(int numero){
    double *vetor_gerado; 
    int cont; 
    vetor_gerado = (double *)malloc(sizeof(double) * numero); 
    for(cont = 0 ; cont < numero; cont++){
        double numero = (rand() / (double)RAND_MAX); 
        vetor_gerado[cont] = numero; 
    }
    return vetor_gerado; 
}

void mostrar_vetor(float *vetor_criado, int tamanho){
    int cont; 
    for(cont = 0; cont < tamanho; cont++){
        printf("[%.5f]", vetor_criado[cont]); 
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese"); 
    int tamaho_maximo = 100000000; 
    time_t t; 
    srand(time(NULL)); 
    double *vet = NULL; 
    vet = gerar_vetor(tamaho_maximo); 
    int cont; 
    double soma = 0.0;
    double inicio, fim; 


    inicio = omp_get_wtime(); 
    /*Processamento sequencial*/
    for(cont = 0; cont < tamaho_maximo; cont++){
        soma = soma + vet[cont]; 
    }
    /*Fim do Processamento sequencial*/

    fim = omp_get_wtime(); 
    double media = soma/(double)tamaho_maximo;
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double tempo_s = fim-inicio;
    printf("Tempo sequencial: %lf\n",tempo_s);


    soma = 0;
    inicio = omp_get_wtime(); 

    /*Processo paralelo*/
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
            for(cont = 0; cont < tamaho_maximo; cont++){
                soma = soma + vet[cont]; 
            }
    }
    /*fim do processo sequencial*/
    media = soma/(double)tamaho_maximo; 
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double tempo_p = fim-inicio;
    printf("Tempo paralelo: %.4f\n",tempo_p);
    double speedup = tempo_s/tempo_p;
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Efiencia: %f\n",eficiencia);
    return 0; 
}
