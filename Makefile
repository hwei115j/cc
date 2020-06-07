all: cc.c
	gcc cc.c -o cc
	make -C ./source/asm/
	make -C ./source/vm/
	make -C ./source/sexp/
	make -C ./source/c0/ asm
	make -C ./source/c0/ sexp
clean:
	rm -f *.o *.exe *.stackdump *.s
	make -C ./source/asm clean
	make -C ./source/vm clean
	make -C ./source/sexp clean
	make -C ./source/c0 clean

