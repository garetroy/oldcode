#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define PAD         8

static long   num_steps = 100000;
       double step;

void
thunk(double (*sum)[PAD])
{
    int    i; 
    int    portion    = omp_get_thread_num() + 1;
    int    numthreads = omp_get_num_threads();
    double x          = 0;
    
    for(i = portion; i<num_steps; i=i+numthreads){
        x = (i+0.5)*step;
        sum[portion-1][0] += 4.0/(1.0 + x * x);
    }    
}

int main()
{
    int i;
    double x, pi, time = 0.0;
    double sum[NUM_THREADS][PAD];

    step      = 1.0/(double) num_steps; //The interval
    time      = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS); 
    #pragma omp parallel
    {
        thunk(sum);
    } 
    
    time = omp_get_wtime() - time;
    
    for(i = 0; i < NUM_THREADS; i++){
        pi += sum[i][0] * step;
    }
    
    printf("The sum was: %f\n",pi);
    printf("Omp took: %fseconds\n",time);
}
