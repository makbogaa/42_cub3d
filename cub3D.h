/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:46:39 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/09 17:03:49 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# define _USE_MATH_DEFINES
# include <math.h>
# define KEY_FWD	0
# define KEY_BWD	1
# define KEY_L		2
# define KEY_R		3
# define KEY_ROTL	4
# define KEY_ROTR	5
# include "src/game/minilibx-linux/mlx.h"
# include "src/Libft/libft.h"
//MAP
typedef struct s_read_st
{
	char	*buffer;
	char	temp[2];
	int		read_byte;
	int		total_buffer;
}	t_read_st;

enum	e_MAP_PARSE_TYPES
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	ROW
};
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;
typedef struct s_map
{
	int			fd;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			order_number;
	int			orders[3];
	char		start[3];
	int			xpm_height;
	int			xpm_width;
	t_read_st	read_vars;
	void		*side_xpm_files[5];
	t_color		f;
	t_color		c;
	char		**matrix;
	int			matrix_current_row;
	int			row_count;
	int			map_ended;
}	t_map;
typedef struct s_window_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_window_data;
typedef struct s_tex_data
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex_data;
typedef struct s_ray
{
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	double	dir_x;
	double	dir_y;
	int		collision_wall_index;
	int		color;
}	t_ray;
typedef struct s_player
{
	int		state;
	double	p_x;
	double	p_y;
	double	dir_x;
	double	dir_y;
	int		size;
	int		color;
	t_ray	*rays;
	double	angle;
	int		move;
	int		keys[6];
}	t_player;
typedef struct s_dda
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	rdx;
	double	rdy;
}	t_dda;
typedef struct s_col_info
{
	int		screen_x;
	int		side;
	double	perp_dist;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_col_info;
typedef struct s_draw_info
{
	int		tex_id;
	int		tex_x;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		floor_c;
	int		ceil_c;
}	t_draw_info;
typedef struct s_game
{
	t_map			*map;
	void			*mlx;
	void			*mlx_win;
	int				width;
	int				height;
	int				max_ray;
	int				ray_color;
	t_window_data	window_data;
	t_player		*player;
	t_tex_data		textures[4];
}	t_game;
//EVENT CODE
typedef enum s_event_code
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_event_code;
typedef enum s_event_mask
{
	KEYPRESS_MASK=1L<<0,
	KEYRELEASE_MASK=1L<<1
}	t_event_mask;
typedef enum s_keycode
{
	ESC=65307,
	RIGHT_ARROW=65363,
	LEFT_ARROW=65361,
	UP_ARROW=65362,
	DOWN_ARROW=65364,
	UP=119,
	DOWN=115,
	RIGHT=100,
	LEFT=97
}	t_keycode;
int		error_print(char *msg);
//STRING UTILS
int		string_len(char *string);
char	*string_dup(char *string);
//EXTENSION AND FILE CONTROL
int		extension_control(char *name);
void	extension_error(int type);
int		file_control(char *file, t_map *map);
int		content_exist_control(char *file, t_map *map);
int		order_control(t_map *map);
//EVENT FUNCTIONS
void	start_events(t_game *game);
int		close_window(void *param);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
void	process_movement(t_game *game);
void	process_movement_two(t_game *game);
//MAP FUNCTIONS
int		read_and_parse_map(t_map *map);
int		process_buffer(t_map *map);
int		handle_eof_buffer(t_map *map);
int		parse_map(t_map *map);
int		append_texture(t_map *map, char *path, int type);
int		parse_texture_two(t_map *map, int *i);
int		color_parse(t_map *map, int type);
int		get_xpm_files(t_game *game);
int		append_row_two(t_map *map);
int		map_control(t_game *game);
char	**deep_copy_map(char **map);
char	*remove_spaces(char *str);
int		line_control(char *line);
//GAME
int		is_wall_pos(t_game *game, double x, double y);
int		start_game(t_game *game);
void	draw_3d_right(t_game *game);
void	start_player(t_game *game);
//DRAW FUNCTION
void	put_pixel(t_game *game, int x, int y, unsigned int color);
void	draw_tex_column(t_game *game, t_col_info *info);
void	draw_debug_overlay(t_game *game);
//FREE
void	free_game(t_game *game);
void	free_char_map(char **map);
enum	e_extension_error_types
{
	LENGTH,
	HIDDEN,
	EXTENSION_NAME
};

#endif