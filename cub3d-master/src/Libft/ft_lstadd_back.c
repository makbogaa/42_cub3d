/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:12:54 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 16:55:05 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastlst;

	if (lst)
	{
		if (*lst)
		{
			lastlst = ft_lstlast(*lst);
			lastlst -> next = new;
			new->next = NULL;
		}
		else
			*lst = new;
	}
}
