exo1: exo1.o bmp.o 
	gcc exo1.o bmp.o -ansi -Wall -o exo1
exo1.o: exo1.c bmp.h 
	gcc -c exo1.c
bmp.o: bmp.c bmp.h
	gcc -c bmp.c
exo2: exo2.o bmp.o 
	gcc exo2.o bmp.o -ansi -Wall -o exo2
exo2.o: exo2.c bmp.h 
	gcc -c exo2.c
exo3: exo3.o bmp.o 
	gcc exo3.o bmp.o -ansi -Wall -o exo3
exo3.o: exo3.c bmp.h 
	gcc -c exo3.c

exo3Bonus: exo3Bonus.o bmp.o 
	gcc exo3Bonus.o bmp.o -ansi -Wall -lm -o exo3Bonus
exo3Bonus.o: exo3Bonus.c bmp.h 
	gcc -c exo3Bonus.c
