/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 16:54:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map->matrix[y])
	{
		x = 0;
		while (game->map->matrix[y][x])
		{
			if (game->map->matrix[y][x] == 'N' || game->map->matrix[y][x] == 'S'
				|| game->map->matrix[y][x] == 'E' || game->map->matrix[y][x] == 'W')
			{
				game->player->p_x = x + 0.5;
				game->player->p_y = y + 0.5;
				if (game->map->matrix[y][x] == 'N')
					game->player->angle = 3 * acos(-1.0) / 2;
				else if (game->map->matrix[y][x] == 'S')
					game->player->angle = acos(-1.0) / 2;
				else if (game->map->matrix[y][x] == 'E')
					game->player->angle = 0;
				else if (game->map->matrix[y][x] == 'W')
					game->player->angle = acos(-1.0);
				game->map->matrix[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
