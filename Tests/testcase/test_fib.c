#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
    if(n == 0 || n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

int main()
{
    int num, res = 0;
 	scanf("%d", &num);

    res = fib(10);
    printf("%d\n", res);
    return 0;
}