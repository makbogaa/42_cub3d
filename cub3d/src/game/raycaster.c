/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by mdalkili          #+#    #+#             */
/*   Updated: 2026/01/06 16:54:32 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

typedef struct s_ray_data
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray_data;

static void	init_ray(t_game *game, t_ray_data *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->width - 1;
	ray->ray_dir_x = cos(game->player->angle) + sin(game->player->angle) * ray->camera_x;
	ray->ray_dir_y = sin(game->player->angle) - cos(game->player->angle) * ray->camera_x;
	ray->map_x = (int)game->player->p_x;
	ray->map_y = (int)game->player->p_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calculate_step(t_game *game, t_ray_data *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->p_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->p_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray_data *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0 || !game->map->matrix[ray->map_y]
			|| !game->map->matrix[ray->map_y][ray->map_x]
			|| game->map->matrix[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_height(t_game *game, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->p_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->p_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(game->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->height / 2;
	if (ray->draw_end >= game->height)
		ray->draw_end = game->height - 1;
}

static int	get_texture_color(t_game *game, t_ray_data *ray, int y)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		step;
	double		tex_pos;
	char		*pixel;

	if (ray->side == 0)
		wall_x = game->player->p_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player->p_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (ray->side == 1 && ray->step_y > 0)
		tex = &game->map->tex_so;
	else if (ray->side == 1 && ray->step_y < 0)
		tex = &game->map->tex_no;
	else if (ray->side == 0 && ray->step_x > 0)
		tex = &game->map->tex_ea;
	else
		tex = &game->map->tex_we;
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (y - ray->draw_start) * step;
	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
	return (*(int *)pixel);
}

static void	draw_vertical_line(t_game *game, int x, t_ray_data *ray)
{
	int				y;
	int				color;
	char			*dst;
	int				bpp;

	bpp = game->window_data.bits_per_pixel / 8;
	y = 0;
	while (y < game->height)
	{
		if (y < ray->draw_start)
			color = game->map->ceiling_color;
		else if (y >= ray->draw_start && y <= ray->draw_end)
			color = get_texture_color(game, ray, y);
		else
			color = game->map->floor_color;
		dst = game->window_data.addr + y * game->window_data.line_length
			+ x * bpp;
		if (bpp == 4)
			*(unsigned int *)dst = (unsigned int)color;
		else
		{
			dst[0] = (unsigned char)(color & 0xFF);
			if (bpp > 1)
				dst[1] = (unsigned char)((color >> 8) & 0xFF);
			if (bpp > 2)
				dst[2] = (unsigned char)((color >> 16) & 0xFF);
		}
		y++;
	}
}

void	cast_rays_3d(t_game *game)
{
	int			x;
	t_ray_data	ray;

	x = 0;
	while (x < game->width)
	{
		init_ray(game, &ray, x);
		calculate_step(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_height(game, &ray);
		draw_vertical_line(game, x, &ray);
		x++;
	}
}
