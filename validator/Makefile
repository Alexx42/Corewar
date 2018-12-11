NAME = validator
LIBFT = ../libft/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./ -I../ -I../libft/includes/

SRCS =\
	main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo Compiling libft...
	@make -C ../libft

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo Cleaning libft...
	@make clean -C ../libft
	@echo Cleaning objects...
	@rm -f $(OBJS)

fclean: clean
	@echo Removing libft...
	@make fclean -C ../libft
	@echo Removing $(NAME) executable...
	@rm -f $(NAME)

re: fclean all
