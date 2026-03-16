/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 04:40:31 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/10 15:08:24 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	parse_texture(t_map *map, int type)
{
	int		i;
	char	*path;

	i = 2;
	if (!parse_texture_two(map, &i))
		return (0);
	path = string_dup(&map->read_vars.buffer[i]);
	if (path[ft_strlen(path) - 1] == '/')
		return (printf("Texture is a directory\n"), free(path), 0);
	if (map->read_vars.buffer[i] == '.' && map->read_vars.buffer[i + 1] == '/')
		i = 2;
	else
		i = 0;
	while (ft_isalnum(path[i]) || path[i] == '/' || path[i] == '_')
		i++;
	if (ft_strncmp(".xpm", &path[i], ft_strlen(".xpm"))
		|| path[i + ft_strlen(".xpm")] != 0)
		return (printf("Map extension not xpm\n"), free(path), 0);
	if (!append_texture(map, path, type))
		return (0);
	if (map->start[0] == 0)
		ft_strlcpy(map->start, map->read_vars.buffer, 3);
	free(map->read_vars.buffer);
	return (1);
}

static int	append_row(t_map *map)
{
	if (!line_control(map->read_vars.buffer))
		return (0);
	map->orders[1] = map->order_number--;
	if (!map->matrix)
	{
		map->matrix = (char **)malloc(sizeof(char *) * 2);
		if (!map->matrix)
		{
			perror("malloc:");
			return (0);
		}
		map->matrix[0] = map->read_vars.buffer;
		map->matrix[1] = NULL;
		map->matrix_current_row = 2;
	}
	else
	{
		if (!append_row_two(map))
			return (0);
	}
	return (1);
}

static int	control_type(char *line)
{
	int	i;

	if (line[0] && line[0] == 'N' && line[1] && line[1] == 'O')
		return (NO);
	else if (line[0] && line[0] == 'S' && line[1] && line[1] == 'O')
		return (SO);
	else if (line[0] && line[0] == 'W' && line[1] && line[1] == 'E')
		return (WE);
	else if (line[0] && line[0] == 'E' && line[1] && line[1] == 'A')
		return (EA);
	else if (line[0] && line[0] == 'F')
		return (F);
	else if (line[0] && line[0] == 'C')
		return (C);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] && (line[i] == '0' || line[i] == '1'))
		return (ROW);
	return (-1);
}

static int	parse_type(t_map *map, int type)
{
	if (map->matrix && (type == NO || type == SO || type == WE
			|| type == EA || type == F || type == C))
		return (error_print("Map must be last element\n"));
	if (type == NO || type == SO || type == WE || type == EA)
		return (parse_texture(map, type));
	else if (type == F || type == C)
		return (color_parse(map, type));
	else if (type == ROW)
		return (append_row(map));
	return (1);
}

int	parse_map(t_map *map)
{
	int	type;

	type = control_type(map->read_vars.buffer);
	if (type > -1)
	{
		if (!parse_type(map, type))
			return (0);
		return (1);
	}
	return (error_print("Uknown input error\n"));
}
