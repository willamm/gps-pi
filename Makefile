#Makefile

CC=gcc
CFLAGS=-Wall -Werror -pedantic
DEPS=gpsdclient.h
CLIB=-lgps
OBJECTS=dcgps.o gps-utils.o gpsprint.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dcgps: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIB)

clean:
	rm -f *.o core.* dcgps

debug: $(OBJECTS) 
	$(CC) -o dcgpsDEBUG -g $(OBJECTS) $(CLIB)

