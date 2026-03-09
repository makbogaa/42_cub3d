/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:43:06 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	put_pixel(t_game *game, int x, int y, unsigned int color)
{
	int		bpp;
	char	*dst;

	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return ;
	bpp = game->window_data.bits_per_pixel / 8;
	dst = game->window_data.addr
		+ y * game->window_data.line_length + x * bpp;
	*(unsigned int *)dst = color;
}

static unsigned int	get_tex_pixel(t_tex_data *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

static int	get_tex_id(int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0)
			return (3);
		return (2);
	}
	if (rdy > 0)
		return (0);
	return (1);
}

static void	init_draw_info(t_game *g, t_col_info *c, t_draw_info *d)
{
	double	wall_x;
	double	pos_x;
	double	pos_y;

	d->tex_id = get_tex_id(c->side, c->ray_dir_x, c->ray_dir_y);
	d->line_h = (int)(g->height / c->perp_dist);
	if (d->line_h < 1)
		d->line_h = 1;
	d->draw_start = -d->line_h / 2 + g->height / 2;
	d->draw_end = d->line_h / 2 + g->height / 2;
	pos_x = g->player->p_x + 0.5;
	pos_y = g->player->p_y + 0.5;
	if (c->side == 0)
		wall_x = pos_y + c->perp_dist * c->ray_dir_y;
	else
		wall_x = pos_x + c->perp_dist * c->ray_dir_x;
	wall_x -= floor(wall_x);
	d->tex_x = (int)(wall_x * g->textures[d->tex_id].width);
	if ((c->side == 0 && c->ray_dir_x < 0)
		|| (c->side == 1 && c->ray_dir_y > 0))
		d->tex_x = g->textures[d->tex_id].width - d->tex_x - 1;
	d->floor_c = (g->map->f.r << 16) | (g->map->f.g << 8)
		| g->map->f.b;
	d->ceil_c = (g->map->c.r << 16) | (g->map->c.g << 8)
		| g->map->c.b;
}

void	draw_tex_column(t_game *game, t_col_info *info)
{
	t_draw_info	d;
	t_tex_data	*tex;
	int			y;
	int			tex_y;

	init_draw_info(game, info, &d);
	tex = &game->textures[d.tex_id];
	y = -1;
	while (++y < d.draw_start && y < game->height)
		put_pixel(game, info->screen_x, y, d.ceil_c);
	while (y <= d.draw_end && y < game->height)
	{
		tex_y = (y - d.draw_start) * tex->height / d.line_h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(game, info->screen_x, y,
			get_tex_pixel(tex, d.tex_x, tex_y));
		y++;
	}
	while (y < game->height)
		put_pixel(game, info->screen_x, y++, d.floor_c);
}
