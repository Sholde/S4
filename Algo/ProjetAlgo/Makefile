run: main_compil lib_compil
	./main
	
main_compil: lib_compil
	gcc -o main main.c -g3 -Wall
	
lib_compil:
	gcc -o lib lib.h -g3 -Wall
