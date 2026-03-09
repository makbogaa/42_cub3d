/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:59:55 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:47 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen(s1 + i);
	while (len > 0 && ft_strchr(set, s1[i + len - 1]))
		len--;
	str = ft_substr(s1, i, len);
	if (!str)
		return ((char *)0);
	free(s1);
	return (str);
}
