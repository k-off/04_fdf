/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 13:53:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/02/09 13:18:35 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	struct		s_line
{
	void			**content;
	size_t			content_size[100];
	int				fd[100];
	int				fin;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
