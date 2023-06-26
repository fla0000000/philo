NAME = philosofer
LIB_L = libfreal/libft.a
SRCS = ${wildcard *.c}
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(%.c)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@make -C libfreal
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_L) -o $(NAME)

%.c: %.o
	@$(CC) $(CFLAGS) -o $<

clean:
	@rm -f $(OBJS)
	@make clean -C libfreal
	
fclean: clean
	@rm -f $(NAME) $(NAME)
	@make fclean -C libfreal
	
re: fclean all

.PHONY: all clean fclean re
