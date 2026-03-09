/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:42:28 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:55:34 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*string;

	i = 0;
	string = (unsigned char *) s;
	while (n > 0)
	{
		if (string[i] == (unsigned char) c)
			return ((void *)&string[i]);
		i++;
		n--;
	}
	return ((void *)0);
}
