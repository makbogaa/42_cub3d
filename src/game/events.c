/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:53:15 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/10 15:00:26 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	is_wall_pos(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	row_len;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map->row_count || map_x < 0)
		return (1);
	row_len = (int)ft_strlen(game->map->matrix[map_y]);
	if (map_x >= row_len)
		return (1);
	return (game->map->matrix[map_y][map_x] != '0');
}

static double	get_margin(double delta, double margin)
{
	if (delta > 0)
		return (margin);
	if (delta < 0)
		return (-margin);
	return (0);
}

static void	move_with_collision(t_game *game, double dx, double dy)
{
	double	cur_x;
	double	cur_y;
	double	m;

	m = 0.15;
	cur_x = game->player->p_x + 0.5;
	cur_y = game->player->p_y + 0.5;
	if (!is_wall_pos(game, cur_x + dx + get_margin(dx, m), cur_y))
		game->player->p_x += dx;
	cur_x = game->player->p_x + 0.5;
	if (!is_wall_pos(game, cur_x, cur_y + dy + get_margin(dy, m)))
		game->player->p_y += dy;
}

void	process_movement_two(t_game *game)
{
	t_player	*p;
	double		speed;

	p = game->player;
	speed = 0.05;
	if (p->keys[KEY_FWD])
		move_with_collision(game, p->dir_x * speed, p->dir_y * speed);
	if (p->keys[KEY_BWD])
		move_with_collision(game, -p->dir_x * speed, -p->dir_y * speed);
	if (p->keys[KEY_R])
		move_with_collision(game, -p->dir_y * speed, p->dir_x * speed);
	if (p->keys[KEY_L])
		move_with_collision(game, p->dir_y * speed, -p->dir_x * speed);
}

void	start_events(t_game *game)
{
	mlx_hook(game->mlx_win, ON_DESTROY, 0, close_window, (void *)game);
	mlx_hook(game->mlx_win, ON_KEYDOWN, KEYPRESS_MASK, key_press, (void *)game);
	mlx_hook(game->mlx_win, ON_KEYUP, KEYRELEASE_MASK,
		key_release, (void *)game);
}
