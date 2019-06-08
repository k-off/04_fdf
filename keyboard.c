/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_grid(t_grid *gr, t_win *p, int i)
{
	if (i > 0 || (gr->o_scale > 3 && gr->v_scale > 3))
	{
		gr->v_scale += (int)(((double)gr->v_scale / gr->o_scale) * (i * 3));
		gr->o_scale += (i * 3);
	}
	o_rot_grid(gr, 1);
	if (gr->is_perspective)
		perspective(gr);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	put_grid(p, gr);
}

void	rotate_grid(t_grid *gr, t_win *p, int i)
{
	if (i == 1)
		gr->o_angle += 10;
	else if (i == 2)
		gr->o_angle -= 9;
	else if (i == 3)
		gr->v_angle += 10;
	else if (i == 4)
		gr->v_angle -= 9;
	o_rot_grid(gr, 1);
	if (gr->is_perspective)
		perspective(gr);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	put_grid(p, gr);
}

void	move_grid(t_grid *gr, t_win *p, int i)
{
	if (i == 1)
		gr->ctr_ofs_y -= 10;
	else if (i == 2)
		gr->ctr_ofs_y += 10;
	else if (i == 3)
		gr->ctr_ofs_x -= 10;
	else if (i == 4)
		gr->ctr_ofs_x += 10;
	o_rot_grid(gr, 1);
	if (gr->is_perspective)
		perspective(gr);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	put_grid(p, gr);
}

int		deal_keys2(int key, t_all *all)
{
	if (key == 13)
		move_grid(all->gr, all->win, 1);
	else if (key == 1)
		move_grid(all->gr, all->win, 2);
	else if (key == 0)
		move_grid(all->gr, all->win, 3);
	else if (key == 2)
		move_grid(all->gr, all->win, 4);
	return (0);
}

int		deal_keys(int key, t_all *all)
{
	if (key == 69)
		zoom_grid(all->gr, all->win, 1);
	else if (key == 78)
		zoom_grid(all->gr, all->win, -1);
	else if (key == 124)
		rotate_grid(all->gr, all->win, 1);
	else if (key == 123)
		rotate_grid(all->gr, all->win, 2);
	else if (key == 125)
		rotate_grid(all->gr, all->win, 3);
	else if (key == 126)
		rotate_grid(all->gr, all->win, 4);
	else if (key == 34)
		all->gr->is_perspective = 0;
	else if (key == 35)
		all->gr->is_perspective = 1;
	else if (key == 53)
		exit(0);
	else
		deal_keys2(key, all);
	return (0);
}
