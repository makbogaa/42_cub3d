/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 14:59:48 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = skip_spaces(line, 0);
	if (line[i] == 'F' || line[i] == 'C')
		i++;
	i = skip_spaces(line, i);
	r = ft_atoi(&line[i]);
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == ',')
		i++;
	i = skip_spaces(line, i);
	g = ft_atoi(&line[i]);
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == ',')
		i++;
	i = skip_spaces(line, i);
	b = ft_atoi(&line[i]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return ((r << 16) | (g << 8) | b);
}
