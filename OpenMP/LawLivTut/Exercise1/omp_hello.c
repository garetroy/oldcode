#include<stdio.h>
#include<omp.h>

int main()
{
    #pragma omp parallel 
    {
        printf("Hello World from thread = %d\n",omp_get_thread_num());
        #pragma omp master  //implied barrier here
        {printf("Number of threads = %d\n",omp_get_num_threads());}
    }
    return 0;
} 
