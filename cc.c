#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define error(...) pferror(__FILE__, __LINE__, __VA_ARGS__)
#define SYS(...) my_system(__VA_ARGS__)

#define swap(a, b)         \
    {                      \
        typeof(a) tmp = b; \
        b = a;             \
        a = tmp;           \
    }

static inline void my_system(char *fmt, ...)
{
    va_list args;
    char str[512];

    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);
    fprintf(stderr, "%s\n", str);
    system(str);
}
static inline void pferror(char *file, int line, char *fmt, ...)
{
    fprintf(stderr, "%s:%d: ", file, line);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
static void help()
{
    fprintf(stderr, "cc [-s][-a][-S][-m][--dump-stack][--dump-memory] input.c\n");
    fprintf(stderr, "[-s]\n    輸出組合語言檔案o.s\n\n");
    fprintf(stderr, "[-a]\n    由stdout輸出格式化的S-expression\n\n");
    fprintf(stderr, "[-S][--dump-stack] %%1\n    輸出虛擬機的堆疊狀況"\
            "。%%1為一個小於4095的正整數，會列出4095~%%1之間的記憶體位置\n\n");
    fprintf(stderr, "[-m][--dump-memory] %%1 %%2\n    輸出虛擬機的記憶體位置。會列出%%1 %%2之間的記憶體範圍"\
            "，在只有%%1的情況下，會列出%%1的記憶體位置\n\n");
    exit(1);
}
int main(int argc, char *argv[])
{
    int flag[256] = {0};
    int min = 4080, max = 4095;
    int i;
    char *file = NULL;
    char *c0 = "./source/c0/build/c.exe";
    char *sc = "./source/c0/build/sc.exe";
    char *as = "./source/asm/as.exe";
    char *vm = "./source/vm/vm.exe";
    char *sexp = "./source/sexp/style.exe";
    char *o_s = "./o.s";

    for(i = 0; i < argc && !strstr(argv[i], "cc") ; i++);
    for(i++; i < argc; i++) {
        if(argv[i][0] == '-') {
            if(!strcmp(argv[i], "-a")) {
                flag['a'] = 1;
            } 
            else if(!strcmp(argv[i], "-s")) {
                flag['s'] = 1;
            }
            else if(!strcmp(argv[i], "--dump-stack") || !strcmp(argv[i], "-S")) {
                if(i+1 >= argc || !isdigit(argv[i+1][0])) 
                    min = 4080;
                else { 
                    sscanf(argv[i+1], "%d", &min);
                    i++;
                }
                flag['S'] = 1;
            }
            else if(!strcmp(argv[i], "--dump-memory") || !strcmp(argv[i], "-m")) {
                if(i+1 >= argc || !isdigit(argv[i+1][0])) {
                    max = 4000;
                    min = 4080;
                }
                else if(i+2 >= argc || !isdigit(argv[i+2][0])) {
                    sscanf(argv[i+1], "%d", &min);
                    max = min;
                    i++;
                }
                else if(isdigit(argv[i+1][0]) && isdigit(argv[i+2][0])) {
                    sscanf(argv[i+1], "%d", &min);
                    sscanf(argv[i+2], "%d", &max);
                    i+=2;
                }
                flag['m'] = 1;
            }
            else {
                help();
            }
        }
        else
            file = argv[i];
    }


    if(!file) {
        help();
    } 
    else if(flag['s']) {
        SYS("cpp %s | %s > %s", file, c0, o_s);
    }
    else if(flag['a']) {
        SYS("cpp %s | %s | %s", file, sc, sexp);
    }
    else if(flag['S']) {
        SYS("cpp %s | %s > %s && %s %s ./out && %s --dump-stack %d ./out", file, c0, o_s, as, o_s, vm, min);
        SYS("rm -f %s out", o_s);
    }
    else if(flag['m']) {
        SYS("cpp %s | %s > %s && %s %s ./out && %s --dump-memory %d %d ./out", file, c0, o_s, as, o_s, vm, min, max);
        SYS("rm -f %s out", o_s);
    }
    else {
        SYS("cpp %s | %s > %s && %s %s ./out && %s ./out", file, c0, o_s, as, o_s, vm);
        SYS("rm -f %s out", o_s);
    }
}
