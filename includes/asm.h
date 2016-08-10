/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 10:16:12 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/14 14:13:03 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include <stdio.h>

# define BLACK    "\033[1;30m"
# define RED      "\033[1;31m"
# define GREEN    "\033[1;32m"
# define YELLOW   "\033[1;33m"
# define BLUE     "\033[1;34m"
# define PURPLE   "\033[1;35m"
# define CYAN     "\033[1;36m"
# define WHITE     "\033[0;37m"
# define TEST     "\033[1;38m"
# define TEST2    "\033[0;35m"
# define TEST3    "\033[0;31m"

typedef struct		s_par
{
	void			*p;
	int				size;
	int				type;
	char			*error;
	int				pos;
	struct s_par	*next;
}					t_par;

typedef struct		s_inst
{
	int				opcode;
	int				id;
	int				line_nb;
	char			*error;
	struct s_par	*par;
	int				par_sum;
	int				par_sum_t_h;
	struct s_inst	*next;
}					t_inst;

typedef struct		s_label
{
	char			*name;
	int				id;
	int				sum;
	char			*error;
	struct s_label	*next;
}					t_label;

typedef struct		s_n_c
{
	char			*name;
	char			*comment;
}					t_n_c;

typedef struct		s_encode
{
	int				op;
	int				fd;
	long			count;
	int				tmp;
}					t_encode;

typedef struct		s_error
{
	char			*str;
	struct s_error	*next;
}					t_error;

typedef struct		s_srcs
{
	struct s_inst	*inst;
	struct s_label	*label;
	struct s_n_c	*n_c;
	struct s_error	*error;
	int				nb_line;
	int				id;
}					t_srcs;

int					bad_n_c(char *s);
void				check_srcs(t_srcs **srcs);
void				free_all(t_srcs **srcs);
int					is_inst(char *s);
void				ft_exit(char *str);
void				ft_put(char *str, char *color);
int					nb_char(char *s, char c);
int					is_register(char *s);
char				*get_name(char *str, t_n_c *n_c, t_srcs **srcs);
int					get_pos(t_par *tmp);
int					is_hash(char *str);
int					is_ponct(char *str);
int					not_comment(char *str);
int					is_label(char *str);
int					check_lexical(t_par *par);
int					nb_number(int n);
int					add_error1(char *str, t_srcs **srcs);
char				*ft_str_join_char(char *str, char c);
char				*ft_cjoin(char *s1, char *s2);
char				*test(char *str, int i);
char				*write_inst_error(int x, int y);
char				*write_error(char *str, int i);
int					add_error(char *str, t_srcs **srcs, int i);
int					add_error1(char *str, t_srcs **srcs);
int					empty_line(char *str);
int					nb_number(int n);
char				*ft_cjoin(char *s1, char *s2);
char				*ft_str_join_char(char *str, char c);
int					verify_label_letter(char *str);
char				**ft_strsplit2(char const *s, char c);
t_inst				*create_inst(int id, int sum, int op, int i);
t_label				*create_label(char *name, int id, int par_sum);
t_error				*create_error(char *str);
t_n_c				*create_name(void);
t_par				*create_par(void);
t_srcs				*create_srcs(t_inst *inst, t_label *label, t_n_c *n_c,
		t_error *error);
char				*epur_str(char *str);
void				ft_exit(char *str);
char				get_separator_char(char *str);
int					is_space(char c);
int					verify_inst(char *str);
int					check_inst(char *str);
int					get_n_c_comment(char *str, t_n_c *n_c,
		t_srcs **srcs, int i);
int					ft_isspace(char c);
int					check_label_chars(char c);
int					get_opcode(char *str, t_inst *inst, int i, t_srcs **srcs);
int					get_value(char *str, void **par, int *size);
int					get_label(char *str, t_srcs **srcs, int id, int par_sum);
int					ft_strnchr(char *str, char c);
void				get_par(char **split, t_srcs **srcs, int i);
int					get_type(char *s, int opcode);
int					ft_get_lst_sum(t_inst **inst);
int					add_inst(char *str, t_srcs **srcs, int id, int i);
void				print_str(char *str, int size, int fd);
void				print_magic(int pfd);
int					print_int(long nb, int pfd);
int					print_adressnum(long nb, int pfd);
void				print_size(t_inst *inst, int pfd);
int					intcmp(int a, int b, char *op, int sz);
char				*par_type(int type, t_par *par);
void				check_par(t_inst *inst, t_srcs **srcs, int i);
void				add_sum_par(t_inst **inst);
int					parsing(char *str, t_srcs **srcs);
void				encode(char *str, t_label *label, t_inst *inst,
		t_n_c *n_c);
int					ft_check_and_add(char *str, t_srcs **srcs, int i);
void				print_inst(t_label *label, t_inst *inst, int pfd);
void				print_header(t_inst *inst, t_n_c *n_c, int pfd);
char				get_octet_code(t_par *params);
int					get_difflabel(t_label *label, char *str);
char				check_type_param(t_par *param, int x2, int x1);
void				print_n_label(t_n_c *n_c, t_label *label);
void				print_par(t_inst *tmp, int i);
void				print(t_inst *inst, t_label *label, t_n_c *n_c);
void				ft_put(char *str, char *color);
void				ft_print_error(t_srcs *srcs);
int					nb_char(char *s, char c);
int					there_is_char(char *s);
int					check_instru(t_srcs **srcs, int i, char *s);
void				check_n_c(t_srcs **srcs);
char				*test(char *str, int i);
int					ft_charcount(char *s, char c);
int					is_inst(char *s);
int					ft_wordcount(char **s);
char				*ft_strcdup(const char *s1, char c);
int					inst_or_error(char *str, char **split, int i,
		t_srcs **srcs);
char				ft_puissance(char nb, int puissance);
void				check_octetcode(int op, int oct);
int					get_octet_code_int(t_par *params);
int					check_type_param_int(t_par *param, int x2, int x1);

#endif
