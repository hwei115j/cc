/*
int out(int a)
{
    putchar(a);
}
*/
int div(int a, int b)
{
    int sum = 0;

    while(a > b) {
        sum++;
        a = a - b;
    }
    if(a == b)
        sum++;
    return sum;
}

int out_num(int n)
{

    int max;
    int r;
    int f = 0;

    for(max = 10000; max; max = div(max, 10)) {
        r = div(n, max);
        n = n - (r * max);
        if(r > 0)
            f = 1;
        if(f)
            out(r + 48);
    }
    return 0;
}
int out_str(char *str)
{
    for(int i = 0; str[i]; i++)
        out(str[i]);
    return 0;
}
int spa(int n)
{
    out_num(n);
    out(' ');
    out(' ');
    if(div(n, 10) == 0)
        out(' ');
    return 0;
}
int fib(int n)
{
    if(n == 0)
        return 0;
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
    
    out_str("hello, world\n\n");

    //1+2+3+....+100
    for(i = 0; i < 101; i++)
        max = max + i;
    out_num(max);
    out('\n');

    //星星
    for(i = 0; i < 10; i++) {
        for(j = 0; j < i; j++)
            out('*');
        out('\n');
    }
    out('\n');

    //99乘法表
    int r;
    for(i = 1; i < 10; i++) {
        for(j = 1; j < 10; j++) {
            out_num(j);
            out('*');
            out_num(i);
            out('=');
            spa(i*j);
        }
        out('\n');
    }
    out('\n');

    //費氏數列
    out_str("fib(");
    out_num(23);
    out_str(") = ");
    out_num(fib(23));
    out('\n');
    out('\n');

    out_str("    (a, b) = (");
    out_num(a);
    out_str(", ");
    out_num(b);
    out_str(")\n");

    swap(&a, &b);

    out_str("swap(a, b) = (");
    out_num(a);
    out_str(", ");
    out_num(b);
    out_str(")\n");
}
