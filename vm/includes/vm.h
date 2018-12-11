/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:40:39 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 14:58:24 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "../../op.h"
# include <libft.h>
# include <ft_printf.h>
# include <stdint.h>
# include <stdlib.h>
# include <alu.h>
# include <ncurses.h>
# define ERROR_ENCODING 16
# define ERROR_OP_CODE -1
# define SIZE_SCREEN 64

typedef struct	s_opts
{
	int		dump_cycle;
	char	vizualizer;
	char	aff;
}				t_opts;

typedef struct	s_mem
{
	unsigned char	*mem;
	char			type;
	char			len;
}				t_mem;

typedef struct	s_player
{
	char			*name;
	char			*comment;
	uint32_t		prog_len;
	void			*prog;
	unsigned char	*initial_pc;
	int				dead;
}				t_player;

typedef struct	s_exc_instr
{
	char			op_code;
	unsigned char	encoding_byte;
	t_mem			params[MAX_ARGS_NUMBER];
	char			instr_len;
}				t_exc_instr;

typedef struct	s_process
{
	unsigned char		reg[REG_NUMBER][REG_SIZE];
	unsigned char		*pc;
	unsigned char		*old_pc;
	char				carry;
	int					timeout;
	int					player_num;
	t_exc_instr			next_instr;
	uint32_t			lived_curr_period;
	struct s_process	*prev;
	struct s_process	*next;
}				t_process;

typedef struct	s_clock
{
	uint32_t	num_cycles;
	uint32_t	period_start;
	uint32_t	cycle_to_die;
	uint16_t	checks;
	uint32_t	last_live[MAX_PLAYERS];
	uint32_t	processes_alive;
	uint32_t	lives_curr_period;
}				t_clock;

typedef struct	s_op_fn
{
	char	op_code;
	int		(*func)();
}				t_op_fn;

void			circle_mem_cpy(char	*mem_start, char *curr_mem, int len);

/*
**	init_players.c
*/
int				read_header(int fd, t_player *player);
int				read_program(int fd, t_player *player);
int				check_magic(int fd);
int				read_name(int fd, t_player *player);
int				read_prog_len(int fd, t_player *player);
int				read_comment(int fd, t_player *player);
int				load_players(char **exec_names,
	t_player *players);
int				parse_player_args(char **av, t_player *players);

/*
**	init_game.c
*/
int				init_arena(t_player *players, unsigned char **mem);

/*
**	execute.c
*/
int				dispatch_op(char op_code);
t_exc_instr		*val_instruct(unsigned char *pc, t_exc_instr	*instr);
int				exec_instruct(t_process *process, t_clock *clock,
	t_exc_instr *exc_instr, t_process **processes);
int				read_instruct(t_process *process, t_exc_instr *instr);
void			chose_op(t_process *p, t_clock *cl, t_exc_instr *i, t_op_fn *o);

/*
**	execute_get_params.c
*/
int				check_encoding_param(unsigned char check,
	unsigned char valid_param);
int				get_param_len(unsigned char check, t_mem *param,
	char shorten_dir_len, char num_params);
int				check_encoding_byte(unsigned char *curr, t_op op, t_mem *param);
int				load_params(unsigned char *pc, t_mem *param, int *i);
int				set_param_len(t_mem *param, t_op op);

/*
**	scheduling.c
*/
int				main_schedule(t_player *players, unsigned char *mem,
	t_opts opts);
int				get_winner(t_clock *clock, t_player *players);
int				kill_processes(t_process **processes, t_clock *clock);
int				check_death(t_clock *clock, t_process **pr, t_player *players);
int				execute_processes(t_process *curr, t_clock *cl, t_process **p);
int				find_dead_players(t_process **processes, t_player *players);
/*
**	move_pc.c
*/
void			set_arena_mem_start(unsigned char *mem);
void			move_pc(unsigned char **pc, long long len, char do_mod);
void			*memcpy_circle_dst(void *dst, const void *src, uint64_t len);
void			*memcpy_circle_src(void *dst, const void *src, uint64_t len);
unsigned char	*get_pc_moved(unsigned char *pc, long long len, char do_mod);

/*
**	process_lst.c
*/
t_process		*create_process(t_player player, int player_num);
void			free_process_lst(t_process *p);
int				init_process_lst(t_player *players, t_process **processes);
int				rm_process(t_process **processes, t_process **head);
int				rm_process_with_playnum(t_process **processes, int player_num);

/*
**	parse_player_args.c
*/
int				parse_player_args(char **av, t_player *players);

/*
**	util.c
*/
unsigned char	*mem_to_reg(unsigned char *mem, size_t len);
void			change_endianness(unsigned char *mem, size_t len);
int				extend_reg(unsigned char *mem, int offset);
unsigned char	*get_mem_start(void);
/*
** error.c
*/
int				error(char *msg);

/*
**	main.c
**	creates the players[] in stack memory based on how many arguments.
*/

/*
**	visualiser
**	all that deals with ncurses
*/

int				init_print(t_player *players);
int				printer_whole_mem(unsigned char *mem, t_process *processes);
void			printliveplayers(t_clock clock, int *b, t_player *player);
int				delay();
unsigned char	*get_mem_start();
void			find_loc(unsigned char *mem, unsigned char *pc, int *b, int *a);
void			disp_change_dst(unsigned char *pc, int len, int player_num);
void			print_carry(int carry, char *str);
void			disp_aff(char aff);
void			printer_info(t_clock clock, t_player *player, t_process *p);
int				print_table_empty();
void			disp_pc(unsigned char *pc, unsigned char *old, t_process *p);
int				announce_players(t_player *players);
int				sayhello(void);
int				disp_winner(char *str);
void			disp_list_pc(t_process *processes);
int				deal_arrows();

#endif
