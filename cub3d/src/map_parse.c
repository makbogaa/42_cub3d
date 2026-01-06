/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:25:00 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/12 03:21:39 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*buffer_append(char *buffer, char chr, int *total_len)
{
	char	*result;
	int		i;
	
	if(!buffer)
	{
		result = malloc(sizeof(char) * (*total_len += 1));
		if(!result)
			return (NULL);
		result[0] = chr;
		result[1] = 0;
		return (result);
	}
	result = malloc(sizeof(char) * (*total_len += 2));
	if(!result)
		return (NULL);
	i = 0;
	while(buffer && buffer[i])
	{
		result[i] = buffer[i];
		i++;
	}
	result[i++] = chr;
	result[i] = 0;
	free(buffer);
	return (result);
}

static char *read_map(int map_fd, t_map *map)
{
	char	*buffer;
	char	temp[2];
	int		read_byte;
	int		total_buffer;
	
	total_buffer = 1;
	buffer = NULL;
	temp[1] = 0;
	while(1)
	{
		read_byte = read(map_fd,temp,1);
		if(read_byte <= 0)
			break ;
		if(temp[0] && temp[0] != '\n')
			buffer = buffer_append(buffer, temp[0], &total_buffer);
		else
		{
			if(buffer)
			{
				parse_map(map, buffer);
				buffer = NULL;
				total_buffer = 1;
			}
		}
	}
	if(buffer)
		parse_map(map, buffer);
	return (NULL);
}

static int open_map(char *path)
{
	int map_fd;

	map_fd = open(path,0);
	if(map_fd == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	return map_fd;
}

void read_and_parse_map(char *path, t_map *map)
{
	int map_fd;

	map_fd = open_map(path);
	read_map(map_fd, map);
}