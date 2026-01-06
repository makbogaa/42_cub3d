/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 16:54:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	load_texture(t_game *game, t_texture *tex, char *path)
{
	if (!path)
	{
		printf("Error: Texture path is NULL\n");
		exit(EXIT_FAILURE);
	}
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->map->tex_no, game->map->no_path);
	load_texture(game, &game->map->tex_so, game->map->so_path);
	load_texture(game, &game->map->tex_we, game->map->we_path);
	load_texture(game, &game->map->tex_ea, game->map->ea_path);
}
