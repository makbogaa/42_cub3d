/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:56:39 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 20:44:33 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0 || !game->map->matrix[map_y]
		|| !game->map->matrix[map_y][map_x])
		return (1);
	if (game->map->matrix[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = game->player->p_x + cos(game->player->angle) * move_speed;
	new_y = game->player->p_y + sin(game->player->angle) * move_speed;
	if (!is_wall(game, new_x, game->player->p_y))
		game->player->p_x = new_x;
	if (!is_wall(game, game->player->p_x, new_y))
		game->player->p_y = new_y;
}

static void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = game->player->p_x - cos(game->player->angle) * move_speed;
	new_y = game->player->p_y - sin(game->player->angle) * move_speed;
	if (!is_wall(game, new_x, game->player->p_y))
		game->player->p_x = new_x;
	if (!is_wall(game, game->player->p_x, new_y))
		game->player->p_y = new_y;
}

static void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = game->player->p_x - sin(game->player->angle) * move_speed;
	new_y = game->player->p_y + cos(game->player->angle) * move_speed;
	if (!is_wall(game, new_x, game->player->p_y))
		game->player->p_x = new_x;
	if (!is_wall(game, game->player->p_x, new_y))
		game->player->p_y = new_y;
}

static void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = game->player->p_x + sin(game->player->angle) * move_speed;
	new_y = game->player->p_y - cos(game->player->angle) * move_speed;
	if (!is_wall(game, new_x, game->player->p_y))
		game->player->p_x = new_x;
	if (!is_wall(game, game->player->p_x, new_y))
		game->player->p_y = new_y;
}

int key_press(int keycode, void *v_game)
{
	t_game *game;

	game = (t_game *)v_game;
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode >= 0 && keycode < 65536)
		game->player->keys[keycode] = 1;
	return (0);
}

int key_release(int keycode, void *v_game)
{
	t_game *game;

	game = (t_game *)v_game;
	if (keycode >= 0 && keycode < 65536)
		game->player->keys[keycode] = 0;
	return (0);
}

void handle_movement(t_game *game)
{
	if (game->player->keys[KEY_W])
		move_forward(game);
	if (game->player->keys[KEY_S])
		move_backward(game);
	if (game->player->keys[KEY_A])
		move_left(game);
	if (game->player->keys[KEY_D])
		move_right(game);
	if (game->player->keys[LEFT_ARROW])
		game->player->angle += 0.03;
	if (game->player->keys[RIGHT_ARROW])
		game->player->angle -= 0.03;
}

int move(int keycode, void *v_game)
{
	t_game *game;

	game = (t_game *)v_game;
	if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == LEFT_ARROW)
		game->player->angle += 0.1;
	else if (keycode == RIGHT_ARROW)
		game->player->angle -= 0.1;
	else if (keycode == KEY_ESC)
		close_window(game);
	return (1);
}

int	close_window(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_loop_end(game->mlx);
	return 0;
}