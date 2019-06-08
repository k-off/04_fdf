/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iscntrl.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 14:53:42 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/20 19:48:30 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_iscntrl(int c)
{
	if ((c > 0 && c < 32) || c == 127)
		return (1);
	if (c == 0)
		return (1);
	return (0);
}