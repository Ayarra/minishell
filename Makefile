NAME = minishell

FILES = main.c builtin_fun.c expansions.c \
		parsing.c free.c builtin_environ.c \
		builtin_cd.c quotes.c exp_tilde.c \
		exp_dollar.c helping_fun.c

OFILES = main.o builtin_fun.o expansions.o \
		 parsing.o free.o builtin_environ.o \
		 builtin_cd.o quotes.o exp_tilde.o \
		 exp_dollar.o helping_fun.o

CFLAG = -Wextra -Werror -Wall

CC = gcc

all: $(NAME)

$(NAME): $(OFILES)
		@make -C libft
		@$(CC) $(CFLAG) -c $(FILES)
		ar rc minishell.a $(OFILES)
		@$(CC) $(CFLAG) minishell.a libft/libft.a -o $(NAME)


clean:
		@make fclean -C libft
		rm -f $(OFILES)

fclean: clean
		@rm -f $(NAME)
		@rm -f minishell.a

re:	fclean all
