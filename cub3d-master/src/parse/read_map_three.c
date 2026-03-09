/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 20:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/01 20:59:22 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	is_map_row_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && (line[i] == '0' || line[i] == '1'))
		return (1);
	return (0);
}

static int	eof_parse_content(t_map *map, char *raw)
{
	if (map->map_ended && (map->read_vars.buffer[0] == '0'
			|| map->read_vars.buffer[0] == '1'))
	{
		free(map->read_vars.buffer);
		free(raw);
		return (error_print("Newline in map\n"));
	}
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

int	handle_eof_buffer(t_map *map)
{
	char	*raw;

	raw = NULL;
	if (is_map_row_check(map->read_vars.buffer))
		raw = ft_strdup(map->read_vars.buffer);
	map->read_vars.buffer = ft_strtrim(map->read_vars.buffer,
			" \t\n\v\f\r");
	if (map->read_vars.buffer && map->read_vars.buffer[0] != '\0')
	{
		if (!eof_parse_content(map, raw))
			return (0);
	}
	else if (map->read_vars.buffer)
	{
		free(map->read_vars.buffer);
		map->read_vars.buffer = NULL;
		free(raw);
	}
	return (1);
}
