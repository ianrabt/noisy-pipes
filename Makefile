CC = cc
CFLAGS = -std=gnu17 -g -O0 -pedantic -Wall -Wextra `pkg-config --cflags guile-2.2 gsl`
LIBS = `pkg-config --libs guile-2.2`

all: binary-symmetric visualize codes/repetition

guile-test: guile-test.o
	${CC} guile-test.o ${LIBS} -o guile-test

guile-test.o: guile-test.c
	${CC} -c ${CFLAGS} guile-test.c

binary-symmetric: channel-binary-symmetric.c
	${CC} ${CFLAGS} channel-binary-symmetric.c -o channels/binary-symmetric

codes/repetition: codes/repetition.c
	${CC} ${CFLAGS} codes/repetition.c -o codes/repetition

visualize: visualize.c
	${CC} ${CFLAGS} visualize.c -o visualize

.PHONY: clean
clean:
	rm visualize channels/binary-symmetric
