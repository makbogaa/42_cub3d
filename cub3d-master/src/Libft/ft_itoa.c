/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:37:55 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:55:02 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_variables(int *n, int *end, int *digits)
{
	if (*n < 0)
	{
		(*n) *= -1;
		*digits = 1;
		*end = 1;
	}
	else
	{
		*digits = 0;
		*end = 0;
	}
}

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	int			digits;
	int			end;

	if (n == -2147483648)
		return ((char *)"-2147483648");
	else
	{
		set_variables(&n, &end, &digits);
		digits += get_digits(n);
		str_num = (char *)malloc(sizeof(char) * digits + 1);
		if (!str_num)
			return (NULL);
		*(str_num + digits) = 0;
		while (--digits >= end)
		{
			*(str_num + digits) = n % 10 + '0';
			n /= 10;
		}
		if (end)
			*(str_num + 0) = '-';
	}
	return (str_num);
}
