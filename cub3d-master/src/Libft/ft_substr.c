/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:17:55 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:56:49 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	size;
	const char		*firstc;
	char			*address;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	firstc = &s[start];
	address = (char *)malloc(len + 1);
	if (address == NULL)
		return (NULL);
	ft_memcpy(address, firstc, len);
	address[len] = '\0';
	return (address);
}
