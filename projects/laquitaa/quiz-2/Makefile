CFLAGS = -Wall -fpic -coverage -lm

prog:
	gcc -o testme -g  testme.c $(CFLAGS)
	
force:
	touch testme.c
	make
	
all:run

run: prog
	./testme
	
.PHONY: all run
		
clean:
	rm prog *.gcov *.gcda *.gcno *.so *.out testme.o

cleanall: 
	rm prog 