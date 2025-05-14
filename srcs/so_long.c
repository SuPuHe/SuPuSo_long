/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/14 14:18:25 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	img_loading(t_map *map, int i, int j)
{
	int	x;
	int	y;

	x = j * PIXEL;
	y = i * PIXEL;
	if (map->map[i][j] == 'P')
	{
		mlx_image_to_window(map->mlx, map->player_img, x, y);
	}
	// if (map->map[i][j] == '0')
	// 	mlx_image_to_window(map->mlx, map->floor, x, y);
	else
	{
		mlx_image_to_window(map->mlx, map->wall, x, y);
	}
	// else if (map->map[i][j] == 'C')
	// {
	// 	mlx_image_to_window(map->mlx, map->collectible, x, y);
	// 	map->coin++;
	// }
	// else if (map->map[i][j] == 'E')
	// {
	// 	mlx_image_to_window(map->mlx, map->exit, x, y);
	// }
}

int	map_render(t_map *map)
{
	t_texture	texture;

	map->mlx = mlx_init(PIXEL * map->x, PIXEL * map->y, "so_long", true);
	if (!map->mlx)
		return (1);

	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	texture.player = mlx_load_png("textures/player_imresizer.png");
	texture.wall = mlx_load_png("textures/wall_imresizer.png");
	if (!texture.player)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (!texture.wall)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	map->player_img = mlx_texture_to_image(map->mlx, texture.player);
	mlx_delete_texture(texture.player);
	map->wall = mlx_texture_to_image(map->mlx, texture.wall);
	mlx_delete_texture(texture.wall);
	if (!map->player_img)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	if (!map->wall)
	{
		mlx_terminate(map->mlx);
		return (1);
	}
	int	i, j;
	i = 0;
	while(i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			img_loading(map, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

void	move_player(t_map *map, int x, int y)
{
	if (map->map[map->player_y + y][map->player_x + x] == '1')
		return ;
	map->player_x += x;
	map->player_y += y;
	ft_printf("PLAYER x: %d, y: %d\n", map->player_x, map->player_y);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(map, 0, -1);
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(map, 0, 1);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(map, -1, 0);
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(map, 1, 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (1);
	if (get_input(map, argv, argc))
		return (free(map), 1);
	ft_printf("x: %d, y: %d\n", map->player_x, map->player_y);
	ft_printf("x: %d, y: %d\n", map->x, map->y);
	map_render(map);
	mlx_key_hook(map->mlx, key_handler, map);
	mlx_loop(map->mlx);
	if (map->player_img)
		mlx_delete_image(map->mlx, map->player_img);
	if (map->wall)
		mlx_delete_image(map->mlx, map->wall);
	if (map->mlx)
		mlx_terminate(map->mlx);
	cleanup_map(map);
	free(map);
	return (0);
}
