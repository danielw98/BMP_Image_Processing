SRC=src
CC=gcc
CFLAGS=-c -fPIC
LIBFLAGS=-shared -o
LFLAGS=-L. -lmylib

TEST=test
default: libmylib

%.o: %.c %.h
	$(CC) $(CFLAGS) $<

libmylib: checks.o lowlevel.o bmp.o
	gcc $(LIBFLAGS) libmylib.so $^

clean:
	rm *.o libmylib.so
test:
	@$(CC) -o $(TEST) $(TEST).c $(LFLAGS)

