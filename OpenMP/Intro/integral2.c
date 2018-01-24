#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

static long   num_steps = 100000;
       double step;

double
thunk()
{
    int    i; 
    int    portion    = omp_get_thread_num();
    int    numthreads = omp_get_num_threads();
    double sum        = 0;
    double x          = 0;
    
    for(i = portion; i<num_steps; i=i+numthreads){
        x = (i+0.5)*step;
        sum += 4.0/(1.0 + x * x);
    }    
    
    return sum;
}

int main()
{
    int i;
    double sum, x, pi, time = 0.0;

    step      = 1.0/(double) num_steps; //The interval
    time      = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS); 
    #pragma omp parallel
    {
        double tempsum = thunk();

        #pragma omp atomic
            sum += tempsum;
    } 
    
    time = omp_get_wtime() - time;
    pi   = sum * step;
    
    printf("The sum was: %f\n",pi);
    printf("Omp took: %fseconds\n",time);
}
