main:	main.o	tadArvore.o	desenvolvimento.o
		gcc main.o tadArvore.o desenvolvimento.o -o exe
		rm *.o
main.o:	main.o
		gcc -c main.c
tadArvore.o:	tadArvore.c	tadArvore.h
		gcc -c tadArvore.c
desenvolvimento.o:	desenvolvimento.c	desenvolvimento.h
		gcc -c desenvolvimento.c