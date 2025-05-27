/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_delete_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:09:24 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 14:15:18 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_images(t_map *map)
{
	if (map->img.player_img)
		mlx_delete_image(map->mlx, map->img.player_img);
	if (map->img.wall)
		mlx_delete_image(map->mlx, map->img.wall);
	if (map->img.floor)
		mlx_delete_image(map->mlx, map->img.floor);
	if (map->img.collectible)
		mlx_delete_image(map->mlx, map->img.collectible);
	if (map->img.exit_img)
		mlx_delete_image(map->mlx, map->img.exit_img);
	if (map->img.exit_open)
		mlx_delete_image(map->mlx, map->img.exit_open);
	if (map->img.enemy)
		mlx_delete_image(map->mlx, map->img.enemy);
	if (map->img.moves)
		mlx_delete_image(map->mlx, map->img.moves);
}

void	img_load_exit_enemy(t_map *map, int i, int j, uint32_t idx)
{
	if (map->map[i][j] == 'E')
	{
		idx = mlx_image_to_window(map->mlx, map->img.exit_img,
				j * PIXEL, i * PIXEL);
		map->img.exit_img->instances[idx].z = 2;
		idx = mlx_image_to_window(map->mlx, map->img.exit_open,
				j * PIXEL, i * PIXEL);
		map->img.exit_open->instances[idx].z = 1;
	}
	else if (map->map[i][j] == 'B')
	{
		idx = mlx_image_to_window(map->mlx, map->img.enemy,
				j * PIXEL, i * PIXEL);
		map->img.enemy->instances[idx].z = 3;
	}
}

void	img_loading(t_map *map, int i, int j)
{
	int			x;
	int			y;
	uint32_t	idx;

	x = j * PIXEL;
	y = i * PIXEL;
	idx = mlx_image_to_window(map->mlx, map->img.floor, x, y);
	map->img.floor->instances[idx].z = 0;
	if (map->map[i][j] == 'P')
		mlx_image_to_window(map->mlx, map->img.player_img, x, y);
	else if (map->map[i][j] == '1')
	{
		idx = mlx_image_to_window(map->mlx, map->img.wall, x, y);
		map->img.wall->instances[idx].z = 1;
	}
	else if (map->map[i][j] == 'C')
	{
		idx = mlx_image_to_window(map->mlx, map->img.collectible,
				x, y);
		map->img.collectible->instances[idx].z = 1;
		map->img.coin_instances[i][j] = idx;
	}
	else
		img_load_exit_enemy(map, i, j, idx);
}

void	initialize_player_enemy(t_map *map)
{
	map->player.frame = 0;
	map->player.frame_counter = 0;
	map->player.pixel_x = map->player.x * PIXEL;
	map->player.pixel_y = map->player.y * PIXEL;
	map->player.target_pixel_x = map->player.pixel_x;
	map->player.target_pixel_y = map->player.pixel_y;
	map->player.is_moving = 0;
	map->player.move_speed = 3;
	map->player.state = IDLE;
	map->enemy.pixel_x = map->enemy.x * PIXEL;
	map->enemy.pixel_y = map->enemy.y * PIXEL;
	map->enemy.target_pixel_x = map->enemy.pixel_x;
	map->enemy.target_pixel_y = map->enemy.pixel_y;
	map->enemy.is_moving = 0;
	map->enemy.move_speed = 2;
	map->enemy.frame = 0;
	map->enemy.frame_counter = 0;
	map->enemy.dir = RIGHT;
}
