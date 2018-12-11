NAME = asm
LIBFT = ../libft/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./ -I../ -I../libft/includes/
RED = \x1b[31m
GREEN = \x1b[32m
RESET = \x1b[0m

SRCS =\
	../op.c\
	error.c\
	parse_directive.c\
	parse_header.c\
	lst_func.c\
	validate_instr.c\
	parse_labels.c\
	parse_params.c\
	parse_instructions.c\
	parser.c\
	encoder.c\
	main.c\
	encoder2.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): compiling $(OBJS) $(LIBFT)
	@echo "$(GREEN)" Linking $(NAME)... "$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)" Done! "$(RESET)"

$(LIBFT):
	@echo "$(GREEN)" Compiling libft... "$(RESET)"
	@make -C ../libft

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

compiling:
	@echo "$(GREEN)" Updating objects... "$(RESET)"

clean:
	@echo "$(RED)" Cleaning libft..."$(RESET)"
	@make clean -C ../libft
	@echo "$(RED)" Cleaning objects... "$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)" Removing libft... "$(RESET)"
	@make fclean -C ../libft
	@echo "$(RED)" Removing $(NAME) executable... "$(RESET)"
	@rm -f $(NAME)

re: fclean all
