/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:47:35 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:44 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	size_t	i;
	char	*ref;

	ref = (char *)0;
	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i <= len)
		{
			if (s[i] == (char)c)
				ref = (char *)&s[i];
			i++;
		}
	}
	return (ref);
}
