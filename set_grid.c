/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_grid.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_points(t_grid *grid, int **map, t_point ***points)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	while (map[0][len] != -99999)
		len++;
	i = 0;
	j = 0;
	while (map[i][0] != -99999)
	{
		points[i] = (t_point**)malloc(sizeof(t_point*) * len);
		j = 0;
		while (map[i][j] != -99999)
		{
			points[i][j] = set_point_values(points[i][j], map, i, j);
			set_grid_min_max(grid, points[i][j]);
			j++;
		}
		points[i][len] = NULL;
		i++;
	}
	points[i] = (t_point**)malloc(sizeof(t_point*) * len);
	points[i][j] = set_point_values(points[i][j], map, i, j);
}

void	recalc_grid(t_grid *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= tmp->y_qty)
	{
		j = 0;
		while (j <= tmp->x_qty)
		{
			tmp->points[i][j]->x_pos = j * tmp->o_scale;
			tmp->points[i][j]->y_pos = i * tmp->o_scale;
			tmp->points[i][j]->x_cen = tmp->points[i][j]->x_pos - 500;
			tmp->points[i][j]->y_cen = tmp->points[i][j]->y_pos - 500;
			j++;
		}
		i++;
	}
}

void	set_scale2(int **map, t_grid *tmp, int i, int j)
{
	tmp->x_qty = j - 1;
	tmp->y_qty = i - 1;
	if (i < 3 || j < 3)
	{
		ft_putstr("error: map too small, smallest size 3x3\n");
		exit(0);
	}
	tmp->total_len = (j - 1);
	tmp->total_hig = (i - 1);
	tmp->points = (t_point***)malloc(sizeof(t_point**) * (i + 1));
	tmp->points[i] = NULL;
	set_points(tmp, map, tmp->points);
	tmp->o_scale = 1 + 1000 / \
	(1 + (tmp->total_len * fabs(cos(tmp->o_angle * M_PI / 180)))
	+ (tmp->total_hig * fabs(sin((tmp->o_angle) * M_PI / 180))));
	tmp->v_scale = (250 / ((tmp->grid_max - tmp->grid_min) % 99998 + 1) + 1);
	tmp->ctr_ofs_y = ((int)(tmp->v_scale * (tmp->grid_max - tmp->grid_min) \
	% 99998 * sin(tmp->v_angle)) % 500);
	tmp->total_len = tmp->o_scale * (j - 1);
	tmp->total_hig = tmp->o_scale * (i - 1);
}

void	set_scale1(int **map, t_grid *tmp)
{
	int		i;
	int		j;
	int		line_len;

	i = 0;
	j = 0;
	line_len = 0;
	while (map[i][0] != -99999)
	{
		j = 0;
		while (map[i][j] != -99999)
		{
			j++;
		}
		if (line_len == 0)
			line_len = j;
		else if (line_len != 0 && j != line_len)
		{
			ft_putstr("error: map invalid: lines have different lengths\n");
			exit(0);
		}
		i++;
	}
	set_scale2(map, tmp, i, j);
}

t_grid	*set_grid(int **map)
{
	t_grid	*tmp;

	tmp = (t_grid*)malloc(sizeof(t_grid) * 1);
	tmp->grid_max = -99999;
	tmp->grid_min = 99999;
	tmp->grid_min_clr = 255;
	tmp->grid_zero_clr = 65280;
	tmp->grid_max_clr = 16711680;
	tmp->o_angle = 0;
	tmp->v_angle = 0;
	tmp->total_hig = 0;
	tmp->total_len = 0;
	tmp->ctr_ofs_x = 0;
	tmp->ctr_ofs_y = 0;
	set_scale1(map, tmp);
	tmp->o_angle = -45;
	tmp->v_angle = 35;
	recalc_grid(tmp);
	o_rot_grid(tmp, 0);
	tmp->is_perspective = 0;
	return (tmp);
}
