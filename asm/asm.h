/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:17:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/06 14:49:12 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# define IS_WS(c) (c == ' ' || c == '\t')
# define IS_OP(c) (c == '+' || c == '-')

typedef struct			s_param
{
	char				type;
	uint32_t			value;
}						t_param;

typedef struct			s_instr
{
	char				op_code;
	uint32_t			out_offset;
	char				num_params;
	t_param				param[3];
	struct s_instr		*next;
}						t_instr;

typedef struct			s_label_def
{
	char				*name;
	uint32_t			value;
	struct s_label_def	*next;
}						t_label_def;

typedef struct			s_label_ref
{
	char				*name;
	uint32_t			offset_instr;
	t_param				*param;
	struct s_label_ref	*next;
}						t_label_ref;

typedef struct			s_label_env
{
	t_label_def			*label_def;
	t_label_ref			*label_ref;
}						t_label_env;

typedef struct			s_tokens
{
	t_instr				*head;
	t_instr				*tail;
	t_label_env			labels;
}						t_tokens;

/*
**	lst_func.c
*/
t_instr					*create_instr(void);
void					instr_lst_add(t_instr **end, t_instr *new);
t_label_def				*create_label_def(void);
void					label_def_lst_add(t_label_def **end, t_label_def *new);
t_label_def				*label_def_lst_find(t_label_def *label_def, char *name);

/*
**	parse_params.c
*/
void					check_op(char *str, t_param *param);
int						fill_param(char *str, t_param *param,
						t_tokens *data, uint32_t offset);
t_instr					*parse_params(char *line, t_tokens *data,
						t_instr *intstr, uint32_t offset);

/*
**	parse_instruction.c
*/
int						translate_line(char *line, t_instr **instr,
						uint32_t offset, t_tokens *data);

/*
**	parse_labels.c
*/
int						search_label(t_tokens *data, t_param *param,
						char *str, uint32_t offset);
char					*check_label(char *line, t_label_def **label,
						uint32_t offset);

/*
**	parser.c
*/

int						set_undef_refs(t_label_ref *label_ref,
						t_label_def *label_def);
int						parse_directive(int fd, int *line_nb,
						char **name, char **value);
t_header				*parse_header(int fd, int *line_nb);
int						validate_instr(t_instr *insr);
t_instr					*asm_parser(t_header **header, int fd);

/*
**	encoder.c
*/
int						asm_encode_instr(t_instr *instr, int out_fd);
int						asm_encode_header(t_header *header, int out_fd);
int						asm_encoder(t_header *header,
						t_instr *instructs, int out_fd);
void					big_endian_writer(uint32_t data, int out_fd, char size);
t_op					*get_op(char op_code);
void					write_encoding_byte(t_param params[],
						char num_params, int out_fd);

/*
**	error.c
*/

int						error(char *msg);
void					*error_null(char *msg);
void					*error_line_nb(int line_nb);
int						lexical_error(char *msg);
int						syntax_error(char *msg);

#endif
