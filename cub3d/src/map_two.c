/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 04:40:31 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/02 04:42:07 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_direction(t_map *map, char *temp)
{
	if (temp[0] == 'N' && temp[1] && temp[1] == 'O')
	{
		printf("Parse NO\n");
	}
	else if (temp[0] == 'S' && temp[1] && temp[1] == 'O')
	{
		printf("Parse SO\n");
	}
	else if (temp[0] == 'W' && temp[1] && temp[1] == 'E')
	{
		printf("Parse WE\n");
	}
	else if (temp[0] == 'E' && temp[1] && temp[1] == 'A')
	{
		printf("Parse EA\n");
	}
}
