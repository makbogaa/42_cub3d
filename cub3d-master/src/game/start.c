/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:52:38 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:50:06 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static double	get_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	return (0);
}

void	start_player(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (game->map->matrix[i])
	{
		j = 0;
		while (game->map->matrix[i][j])
		{
			c = game->map->matrix[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player->p_y = i;
				game->player->p_x = j;
				game->player->angle = get_angle(c);
				game->player->dir_x = cos(game->player->angle);
				game->player->dir_y = sin(game->player->angle);
			}
			j++;
		}
		i++;
	}
}

static int	game_loop(void *v_game)
{
	t_game	*game;

	game = (t_game *)v_game;
	process_movement(game);
	memset(game->window_data.addr, 0,
		game->window_data.line_length * game->height);
	draw_3d_right(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->window_data.img, 0, 0);
	return (1);
}

int	start_game(t_game *game)
{
	game->window_data.img = mlx_new_image(game->mlx,
			game->width, game->height);
	game->window_data.addr = mlx_get_data_addr(game->window_data.img,
			&game->window_data.bits_per_pixel,
			&game->window_data.line_length,
			&game->window_data.endian);
	if (!get_xpm_files(game))
		return (0);
	start_events(game);
	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);
	return (1);
}
