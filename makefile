CC = gcc -Wall -Werror -O0
CF = *.c 
CO = *.o 
LIB = -lwiringPi
object = main

all : ${object}
	rm -f *.o *.so 
${object} : ${CO}
	${CC} -o $@ $(CO) $(LIB)

${CO} : ${CF}
	${CC} -c ${CF}
clean:
	rm -f *.o *.so ${object}