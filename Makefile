hw1_201820805.exe: main.o 
	gcc -o hw1_201820805.exe main.o 

main.o: main.c
	gcc -c -o main.o main.c

.PHONEY:  clean
clean:
	rm -r *.exe *.o