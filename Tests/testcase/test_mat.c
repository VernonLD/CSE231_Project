#include <stdio.h>
#include <stdlib.h>

int main()
{
	// matrix axb and matrix bxc
	// ptr1 mat1, ptr2 mat2, ptr3 res mat
    int a, b, c, *ptr1, *ptr2, *ptr3 = 0;

    scanf("%d", &a);
    scanf("%d", &b);    
    scanf("%d", &c);

    *ptr1 = (int *) malloc(a * b * sizeof(int));
    *ptr2 = (int *) malloc(b * c * sizeof(int));

    *ptr3 = (int *) malloc(a * c * sizeof(int));

    // init two matrix casually
    int i, j, count = 0;
    for(i = 0; i < a; ++i) {
    	for(j = 0; j < b; ++j) {
    		*(ptr1 + i*a + j) = count;
    	}
    }
    count = 0;
    for(i = 0; i < b; ++i) {
    	for(j = 0; j < c; ++j) {
    		*(ptr1 + i*c + j) = count;
    	}
    }

    // multiply
    int k, res = 0;
    for(i = 0; i < a; ++i) {
    	for(j = 0; j < c; ++j) {
    		for(k = 0; k < b; ++k) 
    			res += *(ptr1 + i*a + k) * *(ptr2 + i*b +k);
    		*(ptr3 + i * a + c) = res;
    		res = 0;
    	}
    }

    return 0;
}

