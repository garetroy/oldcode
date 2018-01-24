#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
static long   num_steps = 100000;

int main()
{
    int i;
    double step, x, sum, pi, time = 0.0;

    step      = 1.0/(double) num_steps; //The interval
    time      = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) num_threads(NUM_THREADS) firstprivate(x) 
        for(i = 0; i<num_steps; i++){
            x = (i+0.5)*step;
            sum += 4.0/(1.0 + x * x);
        }    
    
    time = omp_get_wtime() - time;
    
    pi = sum * step;
    
    printf("The sum was: %f\n",pi);
    printf("Omp took: %fseconds\n",time);
}
