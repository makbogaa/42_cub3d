/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:56:39 by mdalkili          #+#    #+#             */
/*   Updated: 2026/02/24 00:41:12 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	set_key(t_player *p, int keycode, int val)
{
	if (keycode == UP || keycode == UP_ARROW)
		p->keys[KEY_FWD] = val;
	if (keycode == DOWN || keycode == DOWN_ARROW)
		p->keys[KEY_BWD] = val;
	if (keycode == LEFT)
		p->keys[KEY_L] = val;
	if (keycode == RIGHT)
		p->keys[KEY_R] = val;
	if (keycode == LEFT_ARROW)
		p->keys[KEY_ROTL] = val;
	if (keycode == RIGHT_ARROW)
		p->keys[KEY_ROTR] = val;
}

int	key_press(int keycode, void *v_game)
{
	t_game	*game;

	game = (t_game *)v_game;
	if (keycode == ESC)
		return (close_window(v_game));
	set_key(game->player, keycode, 1);
	return (1);
}

int	key_release(int keycode, void *v_game)
{
	t_game	*game;

	game = (t_game *)v_game;
	set_key(game->player, keycode, 0);
	return (1);
}

void	process_movement(t_game *game)
{
	t_player	*p;

	p = game->player;
	if (!p->move)
		return ;
	if (p->keys[KEY_ROTL])
		p->angle -= 0.03;
	if (p->keys[KEY_ROTR])
		p->angle += 0.03;
	if (p->angle < 0)
		p->angle += 2 * M_PI;
	if (p->angle >= 2 * M_PI)
		p->angle -= 2 * M_PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	process_movement_two(game);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_end(game->mlx);
	return (0);
}
