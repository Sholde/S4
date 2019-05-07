OPTI = -Ofast
WAR = -g3 -Wall
THREAD = -lpthread

all: exo1 clean

exo1: exo1.o
	@gcc -o $@.exe $^ ${THREAD} ${WAR} ${OPTI}
	@echo create: $@.exe

exo1.o:
	@gcc -c exo1.c ${THREAD} ${WAR} ${OPTI}
	@echo create: $@

clean:
	@echo suppr : *.o
	@rm *.o
