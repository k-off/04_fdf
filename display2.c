/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	inc_dec_xy(int a, int b, int *c)
{
	if (a < b)
		(*c)++;
	else if (a > b)
		(*c)--;
}

int		set_pixel_colour2(int clr1, int clr2, int len, int tmp_len)
{
	if (clr1 < clr2 && clr1 >= 0xFF0000 && clr2 == 0xFFFFFF)
		return (clr1 + (0x000101) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 < 0x00FF00 && clr1 < 0xFFFFFF)
		return (clr1 - (0x010000 - 1) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 >= 0x00FF00 && clr1 < 0xFFFFFF)
		return (clr1 - (65535 - 255) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr1 < clr2 && clr1 >= 0x00FF00 && clr2 == 0xFFFFFF)
		return (clr1 + (0x010001) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 >= 0xFF0000 && clr1 == 0xFFFFFF)
		return (clr1 - (0x000101) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 >= 0x00FF00 && clr1 == 0xFFFFFF)
		return (clr1 - (0x010001) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 >= 0x0000FF && clr1 == 0xFFFFFF)
		return (clr1 - (0x010100) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
		return (0xFFFFFF);
}

int		set_pixel_colour1(int clr1, int clr2, int len, int tmp_len)
{
	if (clr1 == clr2)
		return (clr1);
	if (clr1 < clr2 && clr1 < 0x00FF00 && clr2 < 0xFF0000)
		return (clr1 + 0x0000FF * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr1 < clr2 && clr1 < 0x00FF00 && clr2 < 0xFFFFFF)
		return (clr1 + (0x010000 - 1) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr1 < clr2 && clr1 < 0x00FF00 && clr2 == 0xFFFFFF)
		return (clr1 + (0x010100) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr2 < clr1 && clr2 < 0x00FF00 && clr1 < 0xFF0000)
		return (clr1 - 0x0000FF * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else if (clr1 < clr2 && clr1 >= 0x00FF00 && clr2 < 0xFFFFFF)
		return (clr1 + (65535 - 255) * (int)((tmp_len - len)
									* (256 / (double)tmp_len)));
	else
		return (set_pixel_colour2(clr1, clr2, len, tmp_len));
}

void	set_point_colour(t_grid *tmp, int i, int j)
{
	if (tmp->points[i][j]->high == 0)
		tmp->points[i][j]->colour = tmp->grid_zero_clr;
	else if ((double)(tmp->points[i][j]->high) > (0.9 * (double)tmp->grid_max))
		tmp->points[i][j]->colour = 16777215;
	else if (tmp->points[i][j]->high > 0)
		tmp->points[i][j]->colour = tmp->grid_max_clr;
	else if (tmp->points[i][j]->high < 0)
		tmp->points[i][j]->colour = tmp->grid_min_clr;
}
