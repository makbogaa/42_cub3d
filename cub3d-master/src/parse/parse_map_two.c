/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:36:42 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:00:05 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	flood_fill(char **map, int i, int j, int h)
{
	if (i < 0 || j < 0)
		return (0);
	if (i >= h || j >= (int)ft_strlen(map[i]))
		return (0);
	if (map[i][j] == ' ' || map[i][j] == '\0')
		return (0);
	if (map[i][j] == '1' || map[i][j] == 'F')
		return (1);
	map[i][j] = 'F';
	if (!flood_fill(map, i + 1, j, h))
		return (0);
	if (!flood_fill(map, i - 1, j, h))
		return (0);
	if (!flood_fill(map, i, j + 1, h))
		return (0);
	if (!flood_fill(map, i, j - 1, h))
		return (0);
	return (1);
}

static int	player_control(t_map *map, int i)
{
	int		state;
	char	c;

	state = 0;
	while (map->matrix[map->matrix_current_row])
	{
		i = 0;
		while (map->matrix[map->matrix_current_row][i])
		{
			c = map->matrix[map->matrix_current_row][i];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map->matrix[map->matrix_current_row][i] = '0';
				if (!state)
					state = 1;
				else
					return (error_print("Multiple player error\n"));
			}
			i++;
		}
		map->matrix_current_row++;
	}
	if (!state)
		return (error_print("Player not found\n"));
	return (1);
}

static int	is_zero_enclosed(char **map, int row, int col, int h)
{
	if (row == 0 || row >= h - 1)
		return (0);
	if ((int)ft_strlen(map[row - 1]) <= col)
		return (0);
	if (map[row - 1][col] == ' ' || map[row - 1][col] == '\0')
		return (0);
	if ((int)ft_strlen(map[row + 1]) <= col)
		return (0);
	if (map[row + 1][col] == ' ' || map[row + 1][col] == '\0')
		return (0);
	if (col == 0 || map[row][col - 1] == ' ')
		return (0);
	if (map[row][col + 1] == '\0' || map[row][col + 1] == ' ')
		return (0);
	return (1);
}

static int	check_remaining_zeros(char **map, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && !is_zero_enclosed(map, i, j, h))
				return (error_print("Unreachable area not enclosed\n"));
			j++;
		}
		i++;
	}
	return (1);
}

int	map_control(t_game *game)
{
	char	**copy_map;
	int		result;

	game->map->matrix_current_row = 0;
	if (game->map->row_count < 3)
		return (error_print("Map too small\n"));
	if (!player_control(game->map, 0))
		return (0);
	copy_map = deep_copy_map(game->map->matrix);
	result = flood_fill(copy_map, game->player->p_y,
			game->player->p_x, game->map->row_count);
	if (!result)
		return (free_char_map(copy_map),
			error_print("There is an escape route on the map.\n"));
	result = check_remaining_zeros(copy_map, game->map->row_count);
	free_char_map(copy_map);
	return (result);
}
