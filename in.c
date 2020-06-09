#include "stdio.h"

int fib(int n)
{
    if(n < 3)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
int swap(int *a, int *b)
{
    int r = *a;
    *a = *b;
    *b = r;

    return 0;
}
int main()
{
    int max = 0;
    int i;
    int j; 
    int a = 10;
    int b = 20;
   
    printf("hello, world\n");

    //1+2+3+....+100
    for(i = 0; i < 101; i++)
        max = max + i;
    printf("%d\n", max);

    //星星
    for(i = 0; i < 10; i++) {
        for(j = 0; j < i; j++)
            putchar('*');
        putchar('\n');
    }
    putchar('\n');

    //99乘法表
    int r;
    for(i = 1; i < 10; i++) {
        for(j = 1; j < 10; j++) {
            printf("%d*%d=%4d ", j, i, i*j);
        }
        putchar('\n');
    }
    putchar('\n');

    //費氏數列
    printf("fib(%d) = %d\n\n", 23, fib(23));

    printf("swap(%d, %d) = ", a, b);
    swap(&a, &b);
    printf("(%d, %d)\n", a, b); 
}
