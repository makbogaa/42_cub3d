/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:25:00 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/02 04:56:54 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void parse_line(t_map *map, char *temp)
{
	parse_direction(map, temp);
}

static char *concate(char *buffer,char *tmp,int tmp_len)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	if(!buffer)
		return string_dup(tmp);
	result = (char *)malloc(sizeof(char) * (string_len(buffer) + tmp_len + 1));
	while(buffer[i])
		result[j++] = buffer[i++];
	i = 0;
	while(i < tmp_len)
		result[j++] = tmp[i++];
	result[j] = 0;
	free(buffer);
	return (result);
}

static char *read_map(int map_fd, t_map *map)
{
	char	*buffer;
	char	temp[128];
	int		read_byte;
	int		position;
	
	position = 0;
	buffer = NULL;
	while(1)
	{
		read_byte = read(map_fd,temp,1);
		if(read_byte <= 0)
			break;
		position = string_find_char(temp, '\n', position);
		printf("%d\n",position);
		if(position)
		{
			parse_line(map, temp);
			printf("bulundu\n");
			position++;
		}
		temp[read_byte] = 0;
		buffer = concate(buffer,temp,read_byte);
	}
	printf("%s\n",buffer);
	if(buffer)
		free(buffer);
	return NULL;
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

void open_and_read_map(char *path, t_map *map)
{
	int map_fd;
	char *result;

	map_fd = open_map(path);
	result = read_map(map_fd, map);
}