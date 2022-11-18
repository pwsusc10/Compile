parser_201820805.out : lex.yy.c 
	gcc -ll  main.c -o parser_201820805.out

lex.yy.c : lex.l
	flex lex.l



.PHONY : clean
clean :
	rm -rf *.yy.c *.out *.o


