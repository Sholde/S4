OPTI = -Ofast
WAR = -g3 -Wall
THREAD = -lpthread

all: exo2.exe clean

exo2.exe: exo2.o
	@gcc -o $@ $^ ${THREAD} ${WAR} ${OPTI}
	@echo compilation: $@

exo2.o: exo2.c
	@gcc -c exo2.c ${THREAD} ${WAR} ${OPTI}
	@echo compilation: $@

clean:
	@echo supression  : *.o
	@rm *.o
