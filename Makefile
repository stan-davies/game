CMD = gcc
SRC = main.c rend/rend.c rend/text.c rend/colour/colour.c input/input.c player/player.c util/util.c carrier/carrier.c
OBJ = $(SRC:.c=.o)
INC = -I .
# TAG = -D SYS_WINDOWS

all : ${OBJ}
	clear
	${CMD} $^ ${INC} -Wall -pedantic -Wextra -o prog

${OBJ} : %.o: %.c
	clear
	${CMD} ${INC} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm prog
