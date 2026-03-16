/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:12:25 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/10 15:30:05 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	extension_control_two(char *name, int *i, int *j)
{
	if (string_len(name) < 5)
		return (extension_error(0), 0);
	if (name[*i] == '.' && (name[*i + 1] != '/' && name[*i + 1] != '.'))
		return (extension_error(1), 0);
	while (*i < string_len(name) - 4 && name[*i])
	{
		if (name[*i] == '/')
			*j = *i;
		(*i)++;
	}
	return (1);
}

int	extension_control(char *name)
{
	char	*extension;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!extension_control_two(name, &i, &j))
		return (0);
	if (name[j + 1] && name[j + 1] == '.')
		return (extension_error(1), 0);
	if (i + 4 == string_len(name))
	{
		extension = string_dup(".cub");
		while (name[i] && name[i] == extension[i + 4 - string_len(name)])
			i++;
		free(extension);
		if (string_len(name) == i)
			return (1);
		else
			return (extension_error(2), 0);
	}
	return (extension_error(2), 0);
}

int	file_control(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY | O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (error_print("File is a directory\n"));
	}
	else if (errno == ENOTDIR)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return (0);
		}
		map->fd = fd;
		return (1);
	}
	else
	{
		perror("open");
		return (0);
	}
}

int	content_exist_control(char *file, t_map *map)
{
	char	c[3];
	int		i;

	i = 0;
	c[2] = 0;
	if (read(map->fd, c, 2) == 0)
	{
		printf("Empty map file\n");
		return (0);
	}
	while (c[i])
	{
		map->start[i] = c[i];
		i++;
	}
	close(map->fd);
	map->fd = open(file, O_RDONLY);
	return (1);
}

int	order_control(t_map *map)
{
	if (ft_strncmp("NO", map->start, ft_strlen("NO"))
		&& ft_strncmp("SO", map->start, ft_strlen("SO"))
		&& ft_strncmp("WE", map->start, ft_strlen("WE"))
		&& ft_strncmp("EA", map->start, ft_strlen("EA")))
	{
		printf("Map file order error\n");
		close(map->fd);
		return (0);
	}
	if (map->orders[1] > map->orders[0])
	{
		printf("Map file order error\n");
		close(map->fd);
		return (0);
	}
	return (1);
}
