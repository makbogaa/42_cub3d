/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:02 by mdalkili          #+#    #+#             */
/*   Updated: 2026/02/18 16:23:20 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_striteri(char const *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, (char *)s);
		i++;
	}
	return ((char *)0);
}
