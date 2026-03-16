/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:54:29 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:30 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *d, const char *s, size_t len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (ft_strlen(s));
	while (len - 1 > 0 && s[i])
	{
		d[i] = s[i];
		i++;
		len--;
	}
	d[i] = '\0';
	return ((size_t)ft_strlen(s));
}
