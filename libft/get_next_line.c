/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 13:35:57 by pacovali      #+#    #+#                 */
/*   Updated: 2019/02/04 11:44:55 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line		*ft_newlines(void)
{
	t_line	*lines;
	int		i;

	i = 0;
	lines = (t_line*)malloc(sizeof(t_line));
	lines->content = (void**)malloc(sizeof(void**) * 101);
	lines->content[100] = 0;
	while (i < 100)
	{
		lines->fd[i] = -1;
		lines->content_size[i] = 0;
		lines->fin = 0;
		i++;
	}
	lines->next = 0;
	return (lines);
}

int			ft_get_line(int fd, char **line, t_line *l, int i)
{
	size_t		j;

	l->fin = i;
	if (i == -1)
		return (-1);
	i = 0;
	j = 0;
	while (l->fd[i] != fd && l->fd[i] != -1 && i < 100)
		i++;
	if (l->fin != -2 && l->content[i] && ft_strchr(l->content[i], '\n') == NULL)
		return (0);
	l->fd[i] = fd;
	if (l->content_size[i] < 1 || ft_memcmp(&(l->content[i][0]), "\0", 1) == 0)
		return (0);
	while (((char*)(l->content[i]))[j] != '\0'
		&& ((char*)(l->content[i]))[j] != '\n' && j < l->content_size[i])
		j++;
	line[0] = (char*)ft_memalloc(sizeof(char*) * (j + 1));
	ft_strncat(*line, l->content[i], j);
	ft_memmove(l->content[i], &l->content[i][j + 1], l->content_size[i] - j);
	l->content_size[i] -= (j);
	if (l->content_size[i] < 1 && !*line)
		return (0);
	return (1);
}

int			ft_aux(char *buf, int i, long int r, t_line *l)
{
	void			*tmp;

	tmp = (void*)ft_memalloc(sizeof(void*) * (l->content_size[i] + r + 1));
	if ((size_t)l->content_size[i] > 0)
		tmp = ft_strcat(tmp, (char*)l->content[i]);
	tmp = ft_strcat(tmp, buf);
	free(l->content[i]);
	l->content[i] = tmp;
	l->content_size[i] += r;
	if (ft_strchr(buf, '\n') != NULL)
	{
		free(buf);
		return (0);
	}
	return (1);
}

int			ft_set_line(int fd, t_line *l)
{
	char			*buf;
	long int		r;
	int				i;

	r = 1;
	while (r != 0)
	{
		buf = (char*)ft_memalloc(sizeof(char*) * BUFF_SIZE + 1);
		r = (long int)read(fd, buf, BUFF_SIZE);
		if (r < 0)
			return (-1);
		i = 0;
		while (l->fd[i] != fd && l->fd[i] != -1 && i < 100)
			i++;
		if (ft_aux(buf, i, r, l) == 0)
			break ;
		free(buf);
		if (r == 0)
			return (-2);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static	t_line	*lines;
	int				gl_ret;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!lines)
		lines = ft_newlines();
	gl_ret = ft_get_line(fd, line, lines, 0);
	if (gl_ret == 0)
		gl_ret = ft_get_line(fd, line, lines, ft_set_line(fd, lines));
	if (gl_ret > 0)
		return (1);
	else if (gl_ret < 0)
		return (-1);
	return (0);
}
