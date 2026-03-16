/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:31:29 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/01 20:59:22 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	line_control(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ')
			return (error_print("Map Row Symbol Error\n"));
		i++;
	}
	return (1);
}

static int	is_map_row(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && (line[i] == '0' || line[i] == '1'))
		return (1);
	return (0);
}

static char	*prep_trim_buffer(t_map *map)
{
	char	*raw;

	raw = NULL;
	if (is_map_row(map->read_vars.buffer))
		raw = ft_strdup(map->read_vars.buffer);
	map->read_vars.buffer = ft_strtrim(
			map->read_vars.buffer, " \t\n\v\f\r");
	return (raw);
}

static int	swap_raw_and_parse(t_map *map, char *raw)
{
	if (raw)
	{
		free(map->read_vars.buffer);
		map->read_vars.buffer = raw;
	}
	if (!parse_map(map))
	{
		free(map->read_vars.buffer);
		return (0);
	}
	return (1);
}

int	process_buffer(t_map *map)
{
	char	*raw;

	raw = prep_trim_buffer(map);
	if (map->read_vars.buffer && map->read_vars.buffer[0] == '\0')
	{
		free(map->read_vars.buffer);
		map->read_vars.buffer = NULL;
		map->read_vars.total_buffer = 1;
		if (map->matrix)
			map->map_ended = 1;
		free(raw);
		return (1);
	}
	if (map->map_ended && (map->read_vars.buffer[0] == '0'
			|| map->read_vars.buffer[0] == '1'))
	{
		free(map->read_vars.buffer);
		free(raw);
		return (error_print("Newline in map\n"));
	}
	if (!swap_raw_and_parse(map, raw))
		return (0);
	map->read_vars.buffer = NULL;
	map->read_vars.total_buffer = 1;
	return (1);
}
