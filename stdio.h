

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

#define getchar() in()
#define putchar(ch) out(ch)
/*
int getchar()
{
    return in();
}

int putchar(int ch)
{
    out(ch);
    return ch;
}
*/
int out_num(int n)
{

    int max;
    int r;
    int f = 0;
    int count = 0;
    
    if(n == 0) {
        count++;
        putchar(48);
    }
    for(max = 10000; max; max = div(max, 10)) {
        r = div(n, max);
        n = n - (r * max);
        if(r > 0)
            f = 1;
        if(f) {
            putchar(r + 48);
            count++;
        }
    }
    return count;
}

int puts(char *str)
{
    int count = 0;
    for(int i = 0; str[i]; i++) {
        putchar(str[i]);
        count++;
    }

    return count;
}


int printf(char *fmt, ...)
{
    char *va_list = va_start(&fmt);
    int p = 0;
    int count;
    int n;
    int reg = 0;

    while(*fmt) {
        if(*fmt != '%') {
            putchar(*fmt);
            count++;
        } else if(*fmt == '\\') {
            fmt++;
            if(*fmt == '\\')
                putchar('\\');
            else if(*fmt == 'n')
                putchar('\n');
            else if(*fmt == 't')
                putchar('\t');
            count++;
        } else {
            fmt++;
            if(*fmt == '%')
                putchar('%');
            else if(*fmt == 'd')
                count = count + out_num(va_list[p++]);
            else if(*fmt == 's')
                count = count + puts(va_list[p++]);
            else if(*fmt == 'c') {
                count++;
                putchar(va_list[p++]);
            }
            else if(*fmt > '0' && *fmt < '9' || *fmt == '0' || *fmt == '9') {
                n = *fmt - '0';
                fmt++;
                if(*fmt == 'd')
                    reg = out_num(va_list[p++]);
                count = count + reg;

                for(; reg < n; reg++)
                    putchar(' ');
            }
        } 
        fmt++;
    }

    return count;
}

