/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:12:25 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/12 03:20:43 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void extension_error(int type)
{
	if(type == LENGTH)
		printf("Dosya 4 Karakter'den Veya Daha Uzun Olmalı\n");
	if(type == HIDDEN)
		printf("Harita Dosyası Gizli Olmamalı\n");
	if(type == EXTENSION_NAME)
		printf("Yanlış Uzantı Dosyanız .cub Uzantılı Olmalı\n");
}

int extension_control(char *name)
{
	char *extension;
	int i;
	int j;

	j = 0;
	i = 0;
	if(string_len(name) < 5)
		return (extension_error(0),0);
	if( name[i] == '.' && (name[i + 1] != '/' && name[i + 1] != '.'))
		return (extension_error(1),0);
	while (i < string_len(name) - 4 && name[i])
	{
		if(name[i] == '/')
			j = i;
		i++;
	}
	if(name[j + 1] && name[j + 1] == '.')
				return (extension_error(1),0);
	if(i + 4 == string_len(name))
	{
		extension = string_dup(".cub");
		while(name[i] && name[i] == extension[i + 4 - string_len(name)])
			i++;
		free(extension);
		if(string_len(name) == i)
			return (1);
		else
			return (extension_error(2),0);
	}
	return (extension_error(2),0);
}
