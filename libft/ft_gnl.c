/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:52:30 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:13 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl(int fd)
{
	char	*buffer;

	if (fd < 0)
		return (NULL);
	buffer = (char *)malloc(1000000);
	if (!buffer)
		return (NULL);
	return (ft_gnl_assign(buffer, fd));
}

char	*ft_gnl_assign(char *buffer, int fd)
{
	char	c;
	int		i;
	int		byte;

	byte = read(fd, &c, 1);
	i = 0;
	while (byte > 0)
	{
		buffer[i] = c;
		i++;
		if (c == EOF || c == '\n')
			break ;
		byte = read(fd, &c, 1);
	}
	if (i == 0 || byte < 0)
	{
		free (buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}
