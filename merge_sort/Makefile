# Warning, this makefile assert that you have correctly set SS_CC
SS_CC=/usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc

CC=${SS_CC}

all:
	$(CC) -o merge_sort.ss merge_sort_c89.c
	gcc -o merge_sort merge_sort.c

clean:
	rm merge_sort.ss


