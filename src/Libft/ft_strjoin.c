/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:34:49 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:25 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		x;
	char	*totalstr;

	i = 0;
	x = 0;
	totalstr = malloc(sizeof(char) * ft_strlen(s1) +ft_strlen(s2) + 1);
	if (!totalstr)
		return ((char *)0);
	while (s1[x])
	{
		totalstr[i] = s1[x];
		i++;
		x++;
	}
	x = 0;
	while (s2[x])
	{
		totalstr[i] = s2[x];
		i++;
		x++;
	}
	totalstr[i] = '\0';
	return (totalstr);
}
