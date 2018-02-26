#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, i, *ptr, sum = 0;
 	num = 5;


    ptr = (int*) malloc(num * sizeof(int));  //memory allocated using malloc


    for(i = 0; i < num; ++i)
    {
        sum += *(ptr + i);
    }

    free(ptr);
    return 0;
}