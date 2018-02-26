#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, i, j, *ptr, sum, swap = 0;
 	scanf("%d", &num);

    ptr = (int*) malloc(num * sizeof(int));  //memory allocated using malloc

    for(i = 0; i < num; ++i)
    {
        for(j = 0; j < num - i - 1; ++j) {
        	if (*(ptr + i) > *(ptr + j)) {
        		swap = *(ptr + j);
        		*(ptr + j) = *(ptr + i);
        		*(ptr + i) = swap;
        	}
        }
    }

    free(ptr);
    return 0;
}