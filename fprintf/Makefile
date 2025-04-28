CC = cc

FLAGS = -Wall -Wextra -Werror -w

NAME = libfprintf.a

LIBFT = ft_fprintf.h

FILES = ft_fprintf.c ft_fprintf2.c utils.c utils2.c utils3.c\
		print_char_and_string.c print_hexa.c print_ptr.c\
		print_signed.c print_unsigned.c

OBJS = $(FILES:.c=.o)

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs $@ $^

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

bonus: $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
