CC := gcc
CFLAGS := -c

temp: main.o manager.o ui.o
	$(CC) -o $@ $^

main.o: main.c manager.h ui.h macros.h
	$(CC) $(CFLAGS) -o $@ main.c

manager.o: manager.c manager.h  macros.h
	$(CC) $(CFLAGS) -o $@ manager.c

ui.o: ui.c ui.h  macros.h
	$(CC) $(CFLAGS) -o $@ ui.c

clean:
	$(RM) *.o *.~ temp