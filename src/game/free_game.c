/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:30:22 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/10 15:30:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	free_char_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(t_game *game)
{
	int	i;

	if (game->map->no)
		free(game->map->no);
	if (game->map->so)
		free(game->map->so);
	if (game->map->ea)
		free(game->map->ea);
	if (game->map->we)
		free(game->map->we);
	if (game->map->matrix)
	{
		i = 0;
		while (game->map->matrix[i])
		{
			free(game->map->matrix[i]);
			i++;
		}
		free(game->map->matrix);
		game->map->matrix = NULL;
	}
	if (game->map->fd >= 0)
		close(game->map->fd);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->player->rays)
		free(game->player->rays);
	while (game->map->side_xpm_files[i])
		mlx_destroy_image(game->mlx, game->map->side_xpm_files[i++]);
	if (game->window_data.img)
		mlx_destroy_image(game->mlx, game->window_data.img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	game->mlx = NULL;
	free_map(game);
}
