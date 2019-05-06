OPTI = -Ofast
WAR = -g3 -Wall
THREAD = -lpthread

all: exo1.exe clean

exo1.exe: exo1.o
	@gcc -o $@ $^ ${THREAD} ${WAR} ${OPTI}
	@echo compilation: $@

exo1.o:
	@gcc -c exo1.c ${THREAD} ${WAR} ${OPTI}
	@echo compilation: $@

clean:
	@echo supression  : *.o
	@rm *.o
