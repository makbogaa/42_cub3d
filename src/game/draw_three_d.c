/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_three_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 05:10:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:27:39 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	init_ray(t_game *game, int screen_x, double *rdx, double *rdy)
{
	double	camera_x;
	double	plane_x;
	double	plane_y;

	camera_x = 2.0 * screen_x / (double)game->width - 1.0;
	plane_x = -game->player->dir_y * .66;
	plane_y = game->player->dir_x * .66;
	*rdx = game->player->dir_x + plane_x * camera_x;
	*rdy = game->player->dir_y + plane_y * camera_x;
}

static void	init_dda_step(t_dda *d, double rdx, double rdy)
{
	d->step_x = 1;
	d->side_x = (d->map_x + 1.0 - d->pos_x) * d->delta_x;
	if (rdx < 0)
	{
		d->step_x = -1;
		d->side_x = (d->pos_x - d->map_x) * d->delta_x;
	}
	d->step_y = 1;
	d->side_y = (d->map_y + 1.0 - d->pos_y) * d->delta_y;
	if (rdy < 0)
	{
		d->step_y = -1;
		d->side_y = (d->pos_y - d->map_y) * d->delta_y;
	}
}

static void	init_dda(t_dda *d, t_player *p, double rdx, double rdy)
{
	d->rdx = rdx;
	d->rdy = rdy;
	d->pos_x = p->p_x + 0.5;
	d->pos_y = p->p_y + 0.5;
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	d->delta_x = 1e30;
	if (rdx != 0)
		d->delta_x = fabs(1.0 / rdx);
	d->delta_y = 1e30;
	if (rdy != 0)
		d->delta_y = fabs(1.0 / rdy);
	init_dda_step(d, rdx, rdy);
}

static double	run_dda(t_game *g, t_dda *d, int *side)
{
	while (!is_wall_pos(g, d->map_x, d->map_y))
	{
		if (d->side_x < d->side_y)
		{
			d->side_x += d->delta_x;
			d->map_x += d->step_x;
			*side = 0;
		}
		else
		{
			d->side_y += d->delta_y;
			d->map_y += d->step_y;
			*side = 1;
		}
	}
	if (*side == 0)
		return ((d->map_x - d->pos_x + (1 - d->step_x) / 2.0) / d->rdx);
	return ((d->map_y - d->pos_y + (1 - d->step_y) / 2.0) / d->rdy);
}

void	draw_3d_right(t_game *game)
{
	int			screen_x;
	t_dda		dda;
	t_col_info	col;
	double		rd[2];

	if (!game || !game->player)
		return ;
	screen_x = 0;
	while (screen_x < game->width)
	{
		col.side = 0;
		init_ray(game, screen_x, &rd[0], &rd[1]);
		init_dda(&dda, game->player, rd[0], rd[1]);
		col.perp_dist = run_dda(game, &dda, &col.side);
		if (col.perp_dist < 0.01)
			col.perp_dist = 0.01;
		col.screen_x = screen_x;
		col.ray_dir_x = rd[0];
		col.ray_dir_y = rd[1];
		draw_tex_column(game, &col);
		screen_x++;
	}
}
