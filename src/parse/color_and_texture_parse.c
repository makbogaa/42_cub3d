/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_texture_parse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:06:53 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:02:23 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	parse_texture_two(t_map *map, int *i)
{
	if (!ft_isspace(map->read_vars.buffer[*i]))
		return (error_print("Invalid Texture Path\n"));
	while (ft_isspace(map->read_vars.buffer[*i]))
		(*i)++;
	if (map->read_vars.buffer[*i] == '.' && map->read_vars.buffer[*i + 1] == '/'
		&& !ft_isalnum(map->read_vars.buffer[*i + 2]))
		return (error_print("Invalid Texture Path\n"));
	return (1);
}

static int	append_color(t_map *map, char **part, int type)
{
	if (type == F && map->f.r == -1)
	{
		map->f.r = ft_atoi(part[0]);
		map->f.g = ft_atoi(part[1]);
		map->f.b = ft_atoi(part[2]);
	}
	else if (type == C && map->c.r == -1)
	{
		map->c.r = ft_atoi(part[0]);
		map->c.g = ft_atoi(part[1]);
		map->c.b = ft_atoi(part[2]);
	}
	else
	{
		free_char_map(part);
		return (printf("Double Color"), 0);
	}
	return (1);
}

static int	is_valid_color_part(char *str)
{
	int	i;
	int	val;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	i = 0;
	while (str[i] == '0')
		i++;
	if ((int)ft_strlen(str + i) > 3)
		return (0);
	val = ft_atoi(str);
	return (val >= 0 && val <= 255);
}

static int	validate_color_buffer(t_map *map)
{
	int	i;

	i = 1;
	if (!ft_isspace(map->read_vars.buffer[i]))
		return (printf("Invalid Color\n"), 0);
	map->read_vars.buffer = remove_spaces(map->read_vars.buffer);
	i = ft_strlen(map->read_vars.buffer) - 1;
	if (map->read_vars.buffer[i] == ',')
		return (printf("Invalid Color\n"), 0);
	i = 1;
	while (ft_isdigit(map->read_vars.buffer[i])
		|| map->read_vars.buffer[i] == ',')
		i++;
	if (map->read_vars.buffer[i] != 0)
		return (printf("Invalid Color\n"), 0);
	return (1);
}

int	color_parse(t_map *map, int type)
{
	int		i;
	char	**part;

	if (!validate_color_buffer(map))
		return (0);
	part = ft_split(&map->read_vars.buffer[1], ',');
	i = 0;
	while (part[i] && is_valid_color_part(part[i]))
		i++;
	if (i != 3)
		return (free_char_map(part), error_print("Invalid Color\n"));
	if (!append_color(map, part, type))
		return (0);
	free_char_map(part);
	free(map->read_vars.buffer);
	map->orders[0] = map->order_number--;
	return (1);
}
