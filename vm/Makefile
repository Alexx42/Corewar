NAME = corewar
LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RED = \x1b[31m
GREEN = \x1b[32m
RESET = \x1b[0m

INCLUDES = -I ./includes -I ../ -I ../libft/includes

OPS_SRCS = $(addprefix operations/, disp_op.c add.c aff.c and.c fork.c help_op.c ld.c ldi.c lfork.c live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c)
ALU_SRCS = $(addprefix alu/, alu_add.c alu_and.c alu_sub.c  alu_or.c alu_pass.c alu_xor.c alu.c alu_both.c)
SRCS_DIR = $(addprefix srcs/, $(OPS_SRCS) $(ALU_SRCS) vizstart.c error.c execute_get_params.c execute.c init_game.c load_players_utils.c load_players.c print.c main.c move_pc.c parse_player_args.c mem.c scheduling_players.c process_lst.c scheduling.c util.c)


SRCS = $(SRCS_DIR) ../op.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)" Linking $(NAME)... "$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) -lncurses
	@echo "$(GREEN)" Done! "$(RESET)"

%.o: %.c 
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

compiling:
	@echo "$(GREEN)" Updating objects... "$(RESET)"

$(LIBFT):
	@echo "$(GREEN)" Compiling libft... "$(RESET)"
	@make -C $(LIBFT_PATH)

clean:
	@echo "$(RED)" Cleaning libft..."$(RESET)"
	@make clean -C $(LIBFT_PATH)
	@echo "$(RED)" Cleaning objects... "$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)" Removing libft... "$(RESET)"
	@make fclean -C $(LIBFT_PATH)
	@echo "$(RED)" Removing $(NAME) executable... "$(RESET)"
	@rm -f $(NAME)

re: fclean all
