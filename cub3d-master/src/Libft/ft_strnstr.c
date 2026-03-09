/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:17:42 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:41 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!str || !find)
		return (NULL);
	if (!(*find))
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while (str[i] == find[j] && str[i] && i < len)
		{
			i++;
			j++;
		}
		if (!find[j])
			return ((char *)&str[i - j]);
		i = (i - j) + 1;
	}
	return ((char *)0);
}
