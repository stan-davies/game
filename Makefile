CMD = gcc
SRC = main.c rend/rend.c rend/text.c
OBJ = $(SRC:.c=.o)
INC = -I .

all : ${OBJ}
	clear
	${CMD} $^ ${INC} -o prog

${OBJ} : %.o: %.c
	clear
	${CMD} ${INC} -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm prog
