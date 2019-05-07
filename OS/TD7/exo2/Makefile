OPTI = -Ofast
WAR = -g3 -Wall
THREAD = -lpthread

all: exo2 clean

exo2: exo2.o
	@gcc -o $@.exe $^ ${THREAD} ${WAR} ${OPTI}
	@echo create: $@.exe

exo2.o: exo2.c
	@gcc -c exo2.c ${THREAD} ${WAR} ${OPTI}
	@echo create: $@

clean:
	@echo suppr : *.o
	@rm *.o
