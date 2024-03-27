SRC=src
CC=gcc
CFLAGS=-c -fPIC
LIBFLAGS=-shared -o
LFLAGS=-L. -lmybmp

TEST=test
default: libmybmp

%.o: %.c %.h
	$(CC) $(CFLAGS) $<

libmybmp: checks.o lowlevel.o bmp.o histogram.o
	gcc $(LIBFLAGS) libmybmp.so $^

clean:
	rm *.o libmybmp.so
test:
	@$(CC) -o $(TEST) $(TEST).c $(LFLAGS)

# gcc -o gabi gabi.c -L. -lmylib