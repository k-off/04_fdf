/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	allwingrid(int **map, t_grid **grid, t_win **window, t_all **all)
{
	*grid = set_grid(map);
	*window = (t_win*)malloc(sizeof(t_win*) * 1);
	(*window)->mlx_ptr = mlx_init();
	*all = (t_all*)malloc(sizeof(t_all) * 1);
	(*all)->win = *window;
	(*all)->gr = *grid;
}

int		main(int argc, char **argv)
{
	t_grid		*grid;
	int			fd;
	int			**map;
	t_win		*win;
	t_all		*all;

	map = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > -1)
		{
			map = get_map(fd);
			allwingrid(map, &grid, &win, &all);
			win->win_ptr = mlx_new_window(win->mlx_ptr, 1000, 1000, argv[1]);
			put_grid(win, grid);
			mlx_key_hook(win->win_ptr, &deal_keys, all);
			mlx_loop(win->mlx_ptr);
		}
		else
			ft_putstr("error: file not found / wrong file name\n");
	}
	else
		ft_putstr("usage: ./fdf <file_name>\n");
	return (0);
}
