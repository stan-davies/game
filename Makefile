CMD = gcc
SRC = main.c rend/rend.c rend/text.c rend/colour/colour.c input/input.c player/player.c util/util.c carrier/carrier.c
OBJ = $(SRC:.c=.o)
INC = -I .
# TAG = -D SYS_WINDOWS

all : ${OBJ}
	clear
	${CMD} $^ ${INC} -o prog

${OBJ} : %.o: %.c
	clear
	${CMD} ${INC} -g -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm prog
