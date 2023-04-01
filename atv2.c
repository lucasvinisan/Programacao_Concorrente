#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <omp.h>


#define number_steps 300000000


int main(){
    setlocale(LC_ALL, "Portuguese"); 
    double step; 
    double value_x, pi, sum = 0.0; 
    int cont;
    int number_threads = omp_get_num_threads(); 
    
    /*Sequential Version*/
    printf("Theads: %d\n", number_threads); 
    double start = omp_get_wtime(); 
    step = 1.0/(double) number_steps; 
    for(cont = 0; cont < number_steps; cont++)
    {
        value_x = (cont + 0.5) * step; // width rectangle 
        sum = sum + 4.0 / (1.0 + value_x * value_x); // sum += rectangle area
    }

    pi = step * sum; 
    double end = omp_get_wtime(); 
    double t_serial = end - start; 

    printf("%.5f\n", pi); 
    printf("Executed sequential(S): %f\n", t_serial); 

    
    /*Paralle Version */

    value_x = 0;
    pi = 0; 
    sum = 0; 
    start = omp_get_wtime(); 
    step = 1.0/(double) number_steps; 

    #pragma omp parallel private(value_x) num_threads(4)
    {
        #pragma omp for reduction (+:sum)
        for(cont  = 0; cont < number_steps; cont++)
        {
            value_x = (cont + 0.5) * step; 
            sum = sum + 4.0/ (1.0 + value_x * value_x); 
        }
    }
    pi = step = sum; 
    end  = omp_get_wtime(); 
    double t_parallel = end - start; 
    double speedup = t_serial/t_parallel; 
    printf("Pi: %f\n", pi); 
    printf("Execution Paralle: %.4f\n", speedup);
    printf("efficiency: %.4f\n", speedup/4.0);


    return 0; 
}

