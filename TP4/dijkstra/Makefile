all:  dijkstra_large dijkstra_small

dijkstra_large: dijkstra_large.c Makefile
	/usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc -static dijkstra_large.c -O3 -o dijkstra_large.ss
	gcc -o dijkstra_large dijkstra_large.c

dijkstra_small: dijkstra_small.c Makefile
	/usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc -static dijkstra_small.c -O3 -o dijkstra_small.ss
	gcc -o dijkstra_small dijkstra_small.c

clean:
	rm -rf dijkstra_large dijkstra_small output*
