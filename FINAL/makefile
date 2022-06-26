pokeristars: Poker.o dx.o di.o c.o global.o
	gcc -Wall -std=c99 -g -o pokeristars Poker.o dx.o di.o c.o global.o
Poker.o: Poker.c dx.h di.h c.h
	gcc -Wall -std=c99 -g -c Poker.c c.c di.c dx.c global.c
dx.o: dx.c dx.h global.h
	gcc -Wall -std=c99 -g -c dx.c
di.o: di.c di.h global.h
	gcc -Wall -std=c99 -g -c di.c
c.o: c.c c.h global.h
	gcc -Wall -std=c99 -g -c c.c
s.o: s.c s.h
	gcc -Wall -std=c99 -g -c s.c
global.o: global.c global.h
	gcc -Wall -std=c99 -g -c -global.c


