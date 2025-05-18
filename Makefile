CMD = gcc
SRC = main.c rend/rend.c
OBJ = $(SRC:.c=.o)
INC = -I .

all : ${OBJ}
	${CMD} $^ ${INC} -o prog

${OBJ} : %.o: %.c
	${CMD} ${INC} -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm prog
