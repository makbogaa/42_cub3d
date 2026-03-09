/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xpm_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:48:25 by mdalkili          #+#    #+#             */
/*   Updated: 2026/02/24 00:26:56 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	start_side_arr(t_game *game, char *side_arr[5])
{
	side_arr[0] = game->map->so;
	side_arr[1] = game->map->no;
	side_arr[2] = game->map->we;
	side_arr[3] = game->map->ea;
	side_arr[4] = NULL;
}

static void	set_tex_data(t_game *game, int i, int w, int h)
{
	game->textures[i].width = w;
	game->textures[i].height = h;
	game->textures[i].addr = mlx_get_data_addr(
			game->map->side_xpm_files[i],
			&game->textures[i].bpp,
			&game->textures[i].line_len,
			&game->textures[i].endian);
}

static int	load_one_xpm(t_game *game, char *path, int i)
{
	int		w;
	int		h;
	char	*tmp;

	if (ft_strncmp("./", path, 2))
	{
		tmp = ft_strjoin("./", path);
		game->map->side_xpm_files[i] = mlx_xpm_file_to_image(
				game->mlx, tmp, &w, &h);
		free(tmp);
	}
	else
		game->map->side_xpm_files[i] = mlx_xpm_file_to_image(
				game->mlx, path, &w, &h);
	if (!game->map->side_xpm_files[i])
		return (0);
	set_tex_data(game, i, w, h);
	return (1);
}

int	get_xpm_files(t_game *game)
{
	int		i;
	char	*side_arr[5];

	i = 0;
	start_side_arr(game, side_arr);
	while (side_arr[i])
	{
		if (!load_one_xpm(game, side_arr[i], i))
			return (error_print("Xpm file not found\n"));
		i++;
	}
	return (1);
}
