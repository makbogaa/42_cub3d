/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:13:35 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/26 02:25:21 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void calculate_ray(t_game *game, int i)
{
	double start_angle;
	double angle_step;
	double ray_angle;
	double dir_x;
	double dir_y;
	double start_x;
	double start_y;
	
	start_x = (game->player->p_x * game->cell_size) + (game->cell_size / 2);
	start_y = (game->player->p_y * game->cell_size) + (game->cell_size / 2);
	game->player->rays[i].x1 = start_x;
	game->player->rays[i].y1 = start_y;
	game->player->rays[i].color = game->ray_color; 
	start_angle = game->player->angle - game->player->fov/2;
	angle_step = (game->player->fov) / (game->max_ray - 1);
	ray_angle = start_angle + i * angle_step;
	dir_y = sin(ray_angle);
	dir_x = cos(ray_angle);
	game->player->rays[i].x2 = start_x + dir_x * 3 * game->cell_size;
	game->player->rays[i].y2 = start_y + dir_y * 3 * game->cell_size;
}

static void draw_square(t_window_data *w, int py, int px, int cell_size, int s, int color)
{
    char *row;
    char *dst;
    unsigned char *p;
    int i;
    int j;
    int bpp;
    int by;
    int bx;

    bpp = w->bits_per_pixel / 8;
    by = py * cell_size + (cell_size - s) / 2;
    bx = px * cell_size + (cell_size - s) / 2;
    i = 0;
    while (i < s)
    {
        row = w->addr + (by + i) * w->line_length;
        j = 0;
        while (j < s)
        {
            dst = row + (bx + j) * bpp;
            if (bpp == 4)
                *(unsigned int *)dst = (unsigned int)color;
            else
            {
                p = (unsigned char *)dst;
                p[0] = (unsigned char)(color & 0xFF);
                if (bpp > 1) p[1] = (unsigned char)((color >> 8) & 0xFF);
                if (bpp > 2) p[2] = (unsigned char)((color >> 16) & 0xFF);
            }
            j++;
        }
        i++;
    }
}

void	draw_player(t_game *game)
{
	int	i;
	
	i = 0;

	draw_square(&game->window_data, game->player->p_y, game->player->p_x, game->cell_size, game->player->size, game->player->color);
	while(i < game->max_ray)
	{
		calculate_ray(game, i);
		draw_line(game,game->player->rays[i].x1,
			game->player->rays[i].x2,
			game->player->rays[i].y1,
			game->player->rays[i].y2,
			game->player->rays[i].color);
		i++;
	}
	if(!game->player->state)
		game->player->state = 1;
}

void	draw_map_2d(t_game *game)
{
	int i;
    int j;

    if (!game || !game->map || !game->map->matrix)
        return ;
    i = 0;
    while (game->map->matrix[i])
    {
        j = 0;
        while (game->map->matrix[i][j])
        {
            if (game->map->matrix[i][j] == '1')
				draw_square(&game->window_data, i, j, game->cell_size, game->cell_size, 0xFFDDBB);
            if (game->map->matrix[i][j] == 'P' && !game->player->state)
            {
				game->player->p_y = i;
				game->player->p_x = j;
				draw_player(game);
			}
            j++;
        }
        i++;
    }
}
