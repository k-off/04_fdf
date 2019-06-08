/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H

# include "libft/libft.h"
# include "lmlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_win;

typedef struct		s_point
{
	int				high;
	int				is_visible;
	int				x_pos;
	int				x_cen;
	int				y_pos;
	int				y_cen;
	int				colour;
}					t_point;

typedef struct		s_grid
{
	t_point			***points;
	int				x_qty;
	int				y_qty;
	int				total_len;
	int				total_hig;
	int				o_angle;
	int				v_angle;
	int				o_scale;
	int				v_scale;
	int				is_perspective;
	int				ctr_ofs_x;
	int				ctr_ofs_y;
	int				grid_min;
	int				grid_max;
	int				grid_min_clr;
	int				grid_max_clr;
	int				grid_zero_clr;
}					t_grid;

typedef struct		s_all
{
	t_grid			*gr;
	t_win			*win;
}					t_all;

int					main(int argc, char **argv);
void				allwingrid(int **map, t_grid **grid, t_win **window,
					t_all **all);
int					**get_map(int fd);
int					**map_realloc(int **map, char **points);
void				tmp_map_cpy(int **map, int ***tmp, int *i);
int					*line_alloc(char **points);
t_grid				*set_grid(int **map);
void				set_scale1(int **map, t_grid *tmp);
void				set_scale2(int **map, t_grid *tmp, int i, int j);
void				recalc_grid(t_grid *tmp);
void				set_points(t_grid *grid, int **map, t_point ***points);
t_point				*set_point_values(t_point *point, int **map, int i, int j);
void				set_grid_min_max(t_grid *grid, t_point *point);
void				o_rot_grid(t_grid *tmp, int is_scaled);
void				point_repos(t_grid *tmp, int i, int j, int tmp_x);
void				perspective(t_grid *gr);
int					deal_keys(int key, t_all *all);
int					deal_keys2(int key, t_all *all);
void				move_grid(t_grid *gr, t_win *p, int i);
void				rotate_grid(t_grid *gr, t_win *p, int i);
void				zoom_grid(t_grid *gr, t_win *p, int i);
void				put_grid(t_win *win, t_grid *gr);
void				put_glines(t_win *win, t_point *pt1, t_point *pt2);
void				change_xy(t_point *pt1, t_point *pt2, int *x, int *y);
void				dy_is_bigger(t_point *pt1, t_point *pt2, int *x, int *y);
void				dx_is_bigger(t_point *pt1, t_point *pt2, int *x, int *y);
void				set_point_colour(t_grid *tmp, int i, int j);
int					set_pixel_colour1(int clr1, int clr2, int len, int tmp_len);
int					set_pixel_colour2(int clr1, int clr2, int len, int tmp_len);
void				inc_dec_xy(int a, int b, int *c);

#endif
