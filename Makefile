NAME = philo
SRCS = ${wildcard *.c}
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(%.c)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.c: %.o
	@$(CC) $(CFLAGS) -o $<

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME) $(NAME)

	
re: fclean all

.PHONY: all clean fclean re
