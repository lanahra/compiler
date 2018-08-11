all:
	flex scanner.l
	gcc -c lex.yy.c
	gcc -Wall main.c lex.yy.o -lfl -o main

clean:
	rm main lex.yy.*
