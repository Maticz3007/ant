main: mrowka
	cc main.c mrowka.c -o ant.out -Wall
main_dbg: mrowka
	cc main.c mrowka.o -o ant.out -ggdb
mrowka:
	cc -c mrowka.c