#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
    int ID = 0;
    printf("Hello(%d)",ID);
    printf(" world(%d)\n",ID);
    }
    return 0;
}
