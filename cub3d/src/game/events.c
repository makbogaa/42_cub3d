/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:53:15 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 20:42:39 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void start_events(t_game *game)
{
	mlx_hook(game->mlx_win, ON_DESTROY, 0, close_window, (void *)game);
	mlx_hook(game->mlx_win, ON_KEYDOWN, KEYPRESS_MASK, key_press, (void *)game);
	mlx_hook(game->mlx_win, ON_KEYUP, KEYRELEASE_MASK, key_release, (void *)game);
}