/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:13:39 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:55:47 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srcstr;
	unsigned char	*deststr;

	srcstr = (unsigned char *)src;
	deststr = (unsigned char *)dest;
	i = 0;
	if (!src)
		return ((void *)dest);
	while (i < n)
	{
		deststr[i] = srcstr[i];
		i++;
	}
	return ((void *)deststr);
}
