/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:25:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:22:40 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static char	*buffer_append(t_map *map)
{
	char	*result;
	int		i;

	if (!map->read_vars.buffer)
	{
		result = malloc(sizeof(char) * (map->read_vars.total_buffer += 1));
		if (!result)
			return (perror("malloc"), NULL);
		result[0] = map->read_vars.temp[0];
		result[1] = 0;
		return (result);
	}
	result = malloc(sizeof(char) * (map->read_vars.total_buffer += 2));
	if (!result)
		return (perror("malloc"), NULL);
	i = 0;
	while (map->read_vars.buffer && map->read_vars.buffer[i])
	{
		result[i] = map->read_vars.buffer[i];
		i++;
	}
	result[i++] = map->read_vars.temp[0];
	result[i] = 0;
	free(map->read_vars.buffer);
	return (result);
}

static int	control_and_append(t_map *map)
{
	if (map->read_vars.temp[0] && map->read_vars.temp[0] != '\n')
	{
		map->read_vars.buffer = buffer_append(map);
		if (!map->read_vars.buffer)
			return (0);
	}
	else
	{
		if (map->read_vars.buffer)
		{
			if (!process_buffer(map))
				return (0);
		}
		else if (map->matrix)
			map->map_ended = 1;
	}
	return (1);
}

static int	check_and_calc_row(t_map *map)
{
	int	i;

	i = 0;
	if (!map->matrix)
	{
		printf("Cube not found\n");
		return (0);
	}
	while (map->matrix[i])
		i++;
	map->row_count = i;
	if (!map->so || !map->no || !map->ea || !map->we)
	{
		printf("Texture not found\n");
		return (0);
	}
	if (map->f.r == -1 || map->c.r == -1)
	{
		printf("Color not found\n");
		return (0);
	}
	return (1);
}

static int	read_map(t_map *map)
{
	if (map->read_vars.read_byte == -1)
	{
		perror("read:");
		if (map->read_vars.buffer)
			free(map->read_vars.buffer);
		return (0);
	}
	if (map->read_vars.read_byte == 0)
		return (-1);
	if (!control_and_append(map))
		return (0);
	return (1);
}

int	read_and_parse_map(t_map *map)
{
	int	result;

	while (1)
	{
		map->read_vars.read_byte = read(map->fd, map->read_vars.temp, 1);
		result = read_map(map);
		if (result == 0)
			return (0);
		else if (result == -1)
			break ;
	}
	if (map->read_vars.buffer)
	{
		if (!handle_eof_buffer(map))
			return (0);
	}
	if (!check_and_calc_row(map))
		return (0);
	return (1);
}
