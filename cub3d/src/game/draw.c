/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 04:23:43 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/26 03:00:46 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include <math.h>

void draw_line(t_game *game, double x1, double x2, double y1, double y2,
	int color)
{
	double  dx;
	double  dy;
	double  max_step;
	int     steps;
	double  x_step;
	double  y_step;
	double  x;
	double  y;
	int     xi;
	int     yi;
	int     bpp;
	char    *row;
	char    *dst;
	unsigned char *p;

	dx = x2 - x1;
	dy = y2 - y1;
	max_step = fmax(fabs(dx), fabs(dy));
	steps = (int)ceil(max_step);
	x_step = dx / (double)steps;
	y_step = dy / (double)steps;
	x = x1;
	y = y1;
	bpp = game->window_data.bits_per_pixel / 8;
	while (steps-- >= 0)
	{
		xi = (int)round(x);
		yi = (int)round(y);
		if (xi >= 0 && xi < game->width && yi >= 0 && yi < game->height)
		{
			row = game->window_data.addr + yi * game->window_data.line_length;
			dst = row + xi * bpp;
			if (bpp == 4)
				*(unsigned int *)dst = (unsigned int)color;
			else
			{
				p = (unsigned char *)dst;
				p[0] = (unsigned char)(color & 0xFF);
				if (bpp > 1)
					p[1] = (unsigned char)((color >> 8) & 0xFF);
				if (bpp > 2)
					p[2] = (unsigned char)((color >> 16) & 0xFF);
			}
		}
		if (max_step <= 0.0)
			return ;
		x += x_step;
		y += y_step;
	}
}
