/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 04:40:31 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 16:54:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void append_row(t_map *map, char *row)
{
	int		i;
	char	**new_matrix;

	if(!map->matrix)
	{
		map->matrix = (char **)malloc(sizeof(char *) * 2);
		if(!map->matrix)
			return ;
		map->matrix[0] = row;
		map->matrix[1] = NULL;
		map->matrix_current_row = 2;
	}
	else
	{
		new_matrix = (char **)malloc(sizeof(char *) * (map->matrix_current_row + 1));
		if(!new_matrix)
			return ; 
		i = 0;
		while(map->matrix[i])
		{
			new_matrix[i] = map->matrix[i];
			i++;
		}
		new_matrix[i++] = row;
		new_matrix[i] = NULL;
		map->matrix_current_row++;
		free(map->matrix);
		map->matrix = new_matrix;
	}
}

static int	control_type(char *line)
{
	if (line[0] && line[0] == 'N' && line[1] && line[1] == 'O')
		return (NO);
	else if (line[0] && line[0] == 'S' && line[1] && line[1] == 'O')
		return (SO);
	else if (line[0] && line[0] == 'W' && line[1] && line[1] == 'E')
		return (WE);
	else if (line[0] && line[0] == 'E' && line[1] && line[1] == 'A')
		return (EA);
	else if(line[0] && line[0] == 'F')
		return (F);
	else if(line[0] && line[0] == 'C')
		return (C);
	else if(line[0] && (line[0] == '0' || line[0] == '1'))
		return (ROW);
	return (-1);
}

static char	*extract_path(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*path;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1])
		i += 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	len = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
	{
		i++;
		len++;
	}
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (i < len)
	{
		path[i] = line[start + i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

static void	parse_type(t_map *map, char *line, int type)
{
	if(type == NO)
		map->no_path = extract_path(line);
	else if(type == SO)
		map->so_path = extract_path(line);
	else if(type == WE)
		map->we_path = extract_path(line);
	else if(type == EA)
		map->ea_path = extract_path(line);
	else if(type == F)
		map->floor_color = parse_color(line);
	else if(type == C)
		map->ceiling_color = parse_color(line);
	else if(type == ROW)
		append_row(map, line);
	else
		free(line);
}

void	parse_map(t_map *map, char *line)
{
	int	type;

	type = control_type(line);
	if(type > -1)
		parse_type(map, line, type);
}
