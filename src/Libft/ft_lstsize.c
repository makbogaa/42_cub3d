/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:45:40 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:55:30 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*copylst;
	int		i;

	copylst = lst;
	i = 0;
	while (copylst)
	{
		i++;
		copylst = copylst->next;
	}
	return (i);
}
