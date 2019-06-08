/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*line_alloc(char **points)
{
	int		i;
	int		*int_line;

	i = 0;
	while (points[i])
		i++;
	if (i % 2 == 0)
		i++;
	int_line = (int*)ft_memalloc(sizeof(int) * (i + 1));
	i = 0;
	while (points[i])
	{
		int_line[i] = ft_atoi(points[i]);
		free(points[i]);
		i++;
	}
	free(points[i]);
	int_line[i] = -99999;
	if (i % 2 == 0)
	{
		int_line[i] = -99998;
		int_line[i + 1] = -99999;
	}
	return (int_line);
}

void	tmp_map_cpy(int **map, int ***tmp, int *i)
{
	while (map[*i])
		(*i)++;
	*tmp = (int**)ft_memalloc((sizeof(int**) * (*i + 2)));
	(*i) = 0;
	while (map[*i][0] != -99999)
	{
		(*tmp)[*i] = map[*i];
		(*i)++;
	}
}

int		**map_realloc(int **map, char **points)
{
	int		i;
	int		**tmp;

	i = 0;
	if (!(*map))
	{
		tmp = (int**)ft_memalloc((sizeof(int**) * 2));
		tmp[i] = line_alloc(points);
		tmp[i + 1] = (int*)ft_memalloc((sizeof(int*) * 1));
		free(map);
		tmp[i + 1][0] = -99999;
	}
	else
	{
		tmp_map_cpy(map, &tmp, &i);
		free(map[i]);
		tmp[i] = line_alloc(points);
		tmp[i + 1] = (int*)ft_memalloc((sizeof(int*) * 1));
		free(map);
		tmp[i + 1][0] = -99999;
	}
	return (tmp);
}

int		**get_map(int fd)
{
	int		**map;
	char	*line;
	char	**points;

	map = (int**)ft_memalloc(sizeof(int**) * 1);
	while (get_next_line(fd, &line) && ft_strlen(line) > 0)
	{
		points = ft_strsplit(line, ' ');
		free(line);
		map = map_realloc(map, points);
		free(points);
	}
	return (map);
}
