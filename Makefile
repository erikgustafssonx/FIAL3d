OBJS= main.o console_io.o gamelogics.o
CFLAGS= -ansi -Wall -O2 

fial3d: ${OBJS}
	${CC} -o fial3d ${OBJS} ${CFLAGS} ${LIBS}

main.o: fial3d.h 

gamelogics.o: fial3d.h
 
console_io.o: fial3d.h


.PHONY: install uninstall clean

install:
	cp fial3d /usr/local/bin/fial3d

uninstall:
	rm -f /usr/local/bin/fial3d

clean: 
	rm -f ${OBJS} fial3d
