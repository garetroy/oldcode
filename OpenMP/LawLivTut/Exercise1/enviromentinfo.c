#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    #pragma omp master
    {
        printf("The amount of processors available %f\n",omp_get_num_procs());
        printf("The current amount of threads being used are %f threads\n",omp_get_num_threads());
        printf("The maximum amount of threads are %f\n",omp_get_max_threads());
        printf("I should be in a parallel region %d\n",omp_in_parallel());
        printf("Dynamic threads are enabled: %d\n",omp_get_dynamic());
        printf("Nested parallelism is enabled: %d\n",omp_get_nested());

    }
}

