/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dx_is_bigger(t_point *pt1, t_point *pt2, int *x, int *y)
{
	int		dx;
	int		dy;

	dx = (int)abs(pt1->x_pos - pt2->x_pos);
	dy = (int)abs(pt1->y_pos - pt2->y_pos);
	inc_dec_xy(pt1->x_pos, pt2->x_pos, x);
	if (dx % dy != 0)
	{
		if (abs(*x - pt1->x_pos) > 0 && (abs(abs((int)ceil((*x - pt1->x_pos)
		/ ((double)dx / dy))) - (abs((int)ceil(((*x - 1) - pt1->x_pos)
		/ ((double)dx / dy))))) == 1))
			inc_dec_xy(pt1->y_pos, pt2->y_pos, y);
	}
	else if (abs(*x - pt1->x_pos) % (dx / dy) == 0)
		inc_dec_xy(pt1->y_pos, pt2->y_pos, y);
}

void	dy_is_bigger(t_point *pt1, t_point *pt2, int *x, int *y)
{
	int		dx;
	int		dy;

	dx = (int)abs(pt1->x_pos - pt2->x_pos);
	dy = (int)abs(pt1->y_pos - pt2->y_pos);
	inc_dec_xy(pt1->y_pos, pt2->y_pos, y);
	if (dy % dx != 0)
	{
		if ((abs(*y - pt1->y_pos) > 0 && abs((int)ceil((abs(*y - pt1->y_pos)
		/ ((double)dy / dx))) - (int)ceil((abs((*y - 1) - pt1->y_pos)
		/ ((double)dy / dx)))) == 1))
			inc_dec_xy(pt1->x_pos, pt2->x_pos, x);
	}
	else if (abs(*y - pt1->y_pos) % (dy / dx) == 0)
		inc_dec_xy(pt1->x_pos, pt2->x_pos, x);
}

void	change_xy(t_point *pt1, t_point *pt2, int *x, int *y)
{
	int		dx;
	int		dy;

	dx = (int)abs(pt1->x_pos - pt2->x_pos);
	dy = (int)abs(pt1->y_pos - pt2->y_pos);
	if (dy != 0 && dx != 0 && dy == dx)
	{
		inc_dec_xy(pt1->x_pos, pt2->x_pos, x);
		inc_dec_xy(pt1->y_pos, pt2->y_pos, y);
	}
	else if (dy == 0 && dx != 0)
		inc_dec_xy(pt1->x_pos, pt2->x_pos, x);
	else if (dy != 0 && dx == 0)
		inc_dec_xy(pt1->y_pos, pt2->y_pos, y);
	else if (dx > dy)
		dx_is_bigger(pt1, pt2, x, y);
	else if (dy > dx)
		dy_is_bigger(pt1, pt2, x, y);
}

void	put_glines(t_win *win, t_point *pt1, t_point *pt2)
{
	int		len;
	int		tmp_len;
	int		x;
	int		y;

	len = (int)hypot(pt1->x_pos - pt2->x_pos, pt1->y_pos - pt2->y_pos);
	tmp_len = len;
	x = pt1->x_pos;
	y = pt1->y_pos;
	mlx_pixel_put((t_win*)win->mlx_ptr, (t_win*)win->win_ptr, x, y,
	pt1->colour);
	while (len > 0 && x > -1 && y > -1 && x < 1001 && y < 1001)
	{
		change_xy(pt1, pt2, &x, &y);
		mlx_pixel_put((t_win*)win->mlx_ptr, (t_win*)win->win_ptr, x, y,
		set_pixel_colour1(pt1->colour, pt2->colour, len, tmp_len));
		len = tmp_len - abs((int)hypot(pt1->x_pos - x, pt1->y_pos - y));
	}
}

void	put_grid(t_win *win, t_grid *gr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= gr->y_qty)
	{
		j = 0;
		while (j <= gr->x_qty)
		{
			if (j < gr->x_qty && gr->points[i][j] && gr->points[i][j + 1] &&
				gr->points[i][j + 1]->high != -99998 &&
			(gr->points[i][j]->is_visible || gr->points[i][j + 1]->is_visible))
				put_glines(win, gr->points[i][j], gr->points[i][j + 1]);
			if (i < gr->y_qty && gr->points[i][j] && gr->points[i + 1][j] &&
				gr->points[i + 1][j]->high != -99998 &&
			(gr->points[i][j]->is_visible || gr->points[i + 1][j]->is_visible))
				put_glines(win, gr->points[i][j], gr->points[i + 1][j]);
			j++;
		}
		i++;
	}
}
