/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:59:06 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:02:31 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	append_texture(t_map *map, char *path, int type)
{
	if (type == NO && !map->no)
		map->no = path;
	else if (type == SO && !map->so)
		map->so = path;
	else if (type == WE && !map->we)
		map->we = path;
	else if (type == EA && !map->ea)
		map->ea = path;
	else
	{
		printf("Double Texture\n");
		free(path);
		return (0);
	}
	return (1);
}

void	extension_error(int type)
{
	if (type == LENGTH)
		printf("The file must be 4 characters or longer.\n");
	if (type == HIDDEN)
		printf("The map file should not be private.\n");
	if (type == EXTENSION_NAME)
		printf("The map file must have a .cub extension.\n");
}

int	append_row_two(t_map *map)
{
	int		i;
	char	**new_matrix;

	new_matrix = (char **)malloc(sizeof(char *)
			* (map->matrix_current_row + 1));
	if (!new_matrix)
	{
		perror("malloc:");
		return (0);
	}
	i = 0;
	while (map->matrix[i])
	{
		new_matrix[i] = map->matrix[i];
		i++;
	}
	new_matrix[i++] = map->read_vars.buffer;
	new_matrix[i] = NULL;
	map->matrix_current_row++;
	free(map->matrix);
	map->matrix = new_matrix;
	return (1);
}
