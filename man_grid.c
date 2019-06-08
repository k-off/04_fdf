/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   man_grid.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		perspective(t_grid *gr)
{
	int		dist;
	int		r_dist;
	int		i;
	int		j;

	i = 0;
	dist = hypot(gr->total_len, gr->total_hig)
	* fabs(sin((gr->v_angle + 180) * M_PI / 180));
	while (i <= gr->y_qty)
	{
		j = 0;
		while (j <= gr->x_qty)
		{
			r_dist = dist + ((gr->points[i][j]->y_cen) * cos((gr->v_angle + 180)
			* M_PI / 180) + (gr->points[i][j]->high * gr->v_scale)
			* cos((gr->v_angle + 180) * M_PI / 180));
			gr->points[i][j]->x_pos = 500 + gr->ctr_ofs_x +
			(int)((double)gr->points[i][j]->x_cen * dist / r_dist);
			gr->points[i][j]->y_pos = 500 + gr->ctr_ofs_y +
			(int)((double)gr->points[i][j]->y_cen * dist / r_dist);
			j++;
		}
		i++;
	}
}

void		point_repos(t_grid *tmp, int i, int j, int tmp_x)
{
	tmp->points[i][j]->x_cen = j * tmp->o_scale - tmp->total_len / 2;
	tmp->points[i][j]->x_pos = tmp->points[i][j]->x_cen + 500 + tmp->ctr_ofs_x;
	tmp->points[i][j]->y_cen = i * tmp->o_scale - tmp->total_hig / 2;
	tmp->points[i][j]->y_pos = tmp->points[i][j]->y_cen + 500 + tmp->ctr_ofs_y;
	tmp_x = tmp->points[i][j]->x_cen;
	tmp->points[i][j]->x_cen = (tmp->points[i][j]->x_cen
	* cos(tmp->o_angle * M_PI / 180)) - (tmp->points[i][j]->y_cen
	* sin((tmp->o_angle) * M_PI / 180));
	tmp->points[i][j]->y_cen = (tmp->points[i][j]->y_cen
	* cos(tmp->o_angle * M_PI / 180)) + (tmp_x
	* sin((tmp->o_angle) * M_PI / 180));
	tmp->points[i][j]->y_cen = ((tmp->points[i][j]->high * tmp->v_scale)
	* cos((tmp->v_angle + 180) * M_PI / 180)) + (tmp->points[i][j]->y_cen
	* sin((tmp->v_angle * M_PI / 180)));
	tmp->points[i][j]->x_pos = tmp->points[i][j]->x_cen + 500 + tmp->ctr_ofs_x;
	tmp->points[i][j]->y_pos = tmp->points[i][j]->y_cen + 500 + tmp->ctr_ofs_y;
	set_point_colour(tmp, i, j);
	if (tmp->points[i][j]->x_pos > 1000 || tmp->points[i][j]->x_pos < 0
		|| tmp->points[i][j]->y_pos > 1000 || tmp->points[i][j]->y_pos < 0 ||
		tmp->points[i][j]->high == -99998)
		tmp->points[i][j]->is_visible = 0;
	else
		tmp->points[i][j]->is_visible = 1;
}

void		o_rot_grid(t_grid *tmp, int is_scaled)
{
	int		i;
	int		j;
	int		tmp_x;

	i = 0;
	j = 0;
	tmp_x = 0;
	if (!is_scaled)
		tmp->o_scale *= (tmp->o_scale / ((tmp->total_len / (tmp->x_qty)
		* fabs(sin(tmp->o_angle * M_PI / 180))) + (tmp->total_hig / (tmp->y_qty)
		* fabs(sin((tmp->o_angle + 90) * M_PI / 180)))));
	tmp->total_len = tmp->x_qty * tmp->o_scale;
	tmp->total_hig = tmp->y_qty * tmp->o_scale;
	while (i <= tmp->y_qty)
	{
		j = 0;
		while (j <= tmp->x_qty)
		{
			point_repos(tmp, i, j, tmp_x);
			j++;
		}
		i++;
	}
}

t_point		*set_point_values(t_point *point, int **map, int i, int j)
{
	point = (t_point*)malloc(sizeof(t_point));
	point->high = map[i][j];
	if (point->high != -99998)
		point->is_visible = 1;
	else
		point->is_visible = 0;
	point->x_pos = j;
	point->x_cen = 0;
	point->y_pos = i;
	point->y_cen = 0;
	point->colour = 0;
	return (point);
}

void		set_grid_min_max(t_grid *grid, t_point *point)
{
	if (point->high < grid->grid_min)
		grid->grid_min = point->high;
	if (point->high > grid->grid_max)
		grid->grid_max = point->high;
}
