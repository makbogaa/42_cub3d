/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:10:53 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:17 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i <= len)
		{
			if (s[i] == (char)c)
				return ((char *)&s[i]);
			i++;
		}
	}
	return ((char *)0);
}
