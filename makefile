
CC=cc -g

Driver:   Driver.c Process.o ProcessTable.o Clock.o
	$(CC) -o Driver Driver.c Process.o ProcessTable.o Clock.o

Process.o:  Process.c Process.h
	$(CC) -c Process.c

ProcessTable.o:  ProcessTable.c ProcessTable.h
	$(CC) -c ProcessTable.c

Clock.o: Clock.c Clock.h
	$(CC) -c Clock.c

clean:
	rm -f Driver *.o
