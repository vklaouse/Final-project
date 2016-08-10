/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 10:16:12 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/10 15:11:48 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../libft/includes/libft.h"
# include <mlx.h>

# define MAX_SIZE CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 8 + 8
# define TO_SIZE PROG_NAME_LENGTH + 4
# define TO_COM	PROG_NAME_LENGTH + 8 + 4
# define TO_CHAMP TO_COM + COMMENT_LENGTH + 4
# define ESCAP 65307
# define W 0xFFFFFF
# define WIDTH 1350
# define LENGTH 2500

typedef	unsigned char	t_byte;
typedef	struct s_env	t_yolo;

typedef	struct			s_img
{
	void				*adr;
	char				*data;
	int					endian;
	int					bpp;
	int					size_line;
	t_yolo				*e;
}						t_img;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_img				**img;
	int					x_1;
	int					x_0;
	int					y_1;
	int					y_0;
}						t_env;

typedef	struct			s_ldi
{
	int					n1;
	int					n2;
	int					r;
}						t_ldi;

typedef struct			s_ligne
{
	int					dx;
	int					sx;
	int					dy;
	int					sy;
	int					err;
	int					e2;
}						t_ligne;

typedef struct			s_param
{
	int					v;
	int					a;
	int					nbr_cycles;
	int					s_lives;
	int					s_cycles;
	int					s_op;
	int					s_deaths;
	int					s_pc;
}						t_param;

typedef struct			s_champ
{
	int					size;
	long				champ_size;
	int					nb_live;
	int					last_live;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	char				prog[CHAMP_MAX_SIZE];
}						t_champ;

typedef struct			s_prog
{
	int					cycle;
	int					cycle_to_die;
	int					all_cycle;
	int					check;
	int					nb_proc;
	int					live;
}						t_prog;

typedef struct			s_proc
{
	int					player;
	int					pc;
	int					old_pc;
	int					carry;
	int					live;
	int					last_live;
	int					*r;
	int					*code;
	t_byte				*instr;
	int					wait;
	int					size;
	int					number;
}						t_proc;

typedef struct			s_glob
{
	int					cnt;
	t_byte				**bcode;
	t_byte				*arena;
	t_byte				*color;
	char				**name_files;
	int					*number_champ;
	int					nb_champ;
	t_param				*param;
	t_champ				**champ;
	t_list				*begin_lst;
	t_prog				*prog;
	t_env				*e;
}						t_glob;

/*
** ft_st_ld.c
*/

void					ft_st(int r1, int r2, t_proc *p, t_glob *g);

/*
** ft_sti_ldi.c
*/

void					ft_sti(int r, int nb, t_glob *g, t_proc *p);
void					ft_ldi(int nb, int *r, t_glob *g, t_proc *p);
void					ft_lldi(int nb, int *r, t_glob *g, t_proc *p);

/*
** ft_aff.c
*/

void					ft_aff(char x);

/*
** ft_error.c
*/

void					ft_error(char *str);
void					ft_champ_right(t_glob *g);
/*
** ft_init.c
*/

t_glob					*ft_glob_init(int nb, char **str);

/*
** ft_map.c
*/

void					ft_fill_map(t_glob *g);

/*
** ft_aff_bit_op.c
*/

void					ft_print_add(t_proc *p);
void					ft_print_sub(t_proc *p);
void					ft_print_and(t_proc *p, int p1, int p2);
void					ft_print_or(t_proc *p, int p1, int p2);
void					ft_print_xor(t_proc *p, int p1, int p2);

/*
** ft_ldi_reg.c
*/

void					ft_ldi_reg_reg(t_glob *g, t_proc *p, int n);
void					ft_ldi_dir_reg(t_glob *g, t_proc *p, int n);
void					ft_ldi_ind_reg(t_glob *g, t_proc *p, int n);
void					ft_ldi_reg_dir(t_glob *g, t_proc *p, int n);
void					ft_ldi_dir_dir(t_glob *g, t_proc *p, int n);

/*
** ft_sti_reg.c
*/

void					ft_sti_reg_reg(t_glob *g, t_proc *p);
void					ft_sti_dir_reg(t_glob *g, t_proc *p);
void					ft_sti_ind_reg(t_glob *g, t_proc *p);
void					ft_sti_reg_dir(t_glob *g, t_proc *p);
void					ft_sti_dir_dir(t_glob *g, t_proc *p);

/*
** ft_fnct.c
*/

void					clear_byte(t_byte *tab);
long					byte_into_long(t_byte *tab);
int						byte_into_int(t_byte *tab);
short					byte_into_short(t_byte *tab);
void					reg_cpy(int r1[16], int r2[16]);

/*
** ft_fnct2.c
*/

void					ft_encode(t_byte n, t_proc *p);
int						ft_encode_space(int *code);
void					ft_print_cycle(t_glob *g);
int						number_digit(int n);

/*
** ft_instr_live.c
*/

void					ft_proc_live(t_proc *p, t_glob *g);

/*
** ft_instr_st_ld.c
*/

void					ft_proc_ld(t_proc *p, t_glob *g, int nb);
void					ft_proc_st(t_proc *p, t_glob *g);

/*
** ft_proc_op.c
*/

void					ft_proc_op(t_proc *p, t_glob *g, int n);

/*
** ft_proc_bit.c
*/

void					ft_proc_bit(t_proc *p, t_glob *g, int n);

/*
** ft_instr_zjmp.c
*/

void					ft_proc_zjmp(t_proc *p, t_glob *g);

/*
** ft_instr_ldi.c
*/

void					ft_proc_ldi(t_proc *p, t_glob *g, int nb);
void					ft_core_ldi(t_glob *g, t_proc *p, int n, t_ldi var);

/*
** ft_instr_sti.c
*/

void					ft_proc_sti(t_proc *p, t_glob *g);

/*
** ft_instr_fork.c
*/

void					ft_proc_fork(t_proc *p, t_glob *g, int n);

/*
** ft_instr_aff.c
*/

void					ft_proc_aff(t_proc *p, t_glob *g);

/*
** ft_cycle.c
*/

int						ft_nb_live(t_glob *g);
void					ft_kill_champ(t_glob *g);

/*
** ft_core.c
*/

void					ft_corewar(t_glob *g);

/*
** ft_algo.c
*/

void					ft_algo(t_glob *g);

/*
** corewar.c
*/

void					parse_flags(t_glob *g, char **av, int ac);
void					ft_print_winner(t_glob *g);

/*
** ft_parsing.c
*/

void					ft_parsing(t_glob *g);

/*
** visualisateur.c
*/

int						visualisateur(t_glob *g);

/*
** visualisateur2.c
*/

void					aff_arena(t_glob *g);
int						draw(t_glob *g);

/*
** visualisateur3.c
*/

int						key_hook(int keycode, t_env *e);
void					draw_black_2(t_glob *g);
void					draw_black_3(t_glob *g, int color, int nb_img);
int						ft_color(t_glob *g, int z);

/*
** modif_visu.c
*/

void					modif_arena(t_glob *g, int z);
void					modif_legend(t_glob *g);

/*
** ft_pixel_put_to_image.c
*/

void					ft_pixel_put_image(t_img *img, int x, int y, int color);

/*
** visu_process.c
*/

void					ft_process(t_glob *g);

/*
** Other
*/

void					print_random(t_glob *g);
void					ft_dump(t_glob *g);
void					flag_sti(t_glob *g, t_proc *p, int n1, int n2);
void					flag_ldi(t_proc *p, int n1, int n2, int r);
void					flag_lldi(t_proc *p, int n1, int n2, int r);
void					ft_print_pc(t_glob *g, t_proc *p, int size);
void					ft_buffer_screen(char *str, int n);
void					ft_print_cycle_to_die(t_glob *g);
void					ft_champ_order(t_glob *g);

#endif
