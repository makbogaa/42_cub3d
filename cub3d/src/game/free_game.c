/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:30:22 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 16:54:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void free_map(t_game *game)
{
	int	i;

	if(game->map->matrix)
	{
		i = 0;
		while(game->map->matrix[i])
		{
			free(game->map->matrix[i]);
			i++;
		}
		free(game->map->matrix);
		game->map->matrix = NULL;
	}
	if (game->map->no_path)
		free(game->map->no_path);
	if (game->map->so_path)
		free(game->map->so_path);
	if (game->map->ea_path)
		free(game->map->ea_path);
	if (game->map->we_path)
		free(game->map->we_path);
}

void free_game(t_game *game)
{
	if (game->map->tex_no.img)
		mlx_destroy_image(game->mlx, game->map->tex_no.img);
	if (game->map->tex_so.img)
		mlx_destroy_image(game->mlx, game->map->tex_so.img);
	if (game->map->tex_we.img)
		mlx_destroy_image(game->mlx, game->map->tex_we.img);
	if (game->map->tex_ea.img)
		mlx_destroy_image(game->mlx, game->map->tex_ea.img);
	free(game->player->rays);
	mlx_destroy_image(game->mlx, game->window_data.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
	free_map(game);
}
