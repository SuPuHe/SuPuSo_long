/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:00:46 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 14:02:54 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_another_img(t_map *map)
{
	map->t.wall = mlx_load_png("textures/wall_dungeon.png");
	map->t.floor = mlx_load_png("textures/floor_dungeon2.png");
	map->t.coin = mlx_load_png("textures/key2.png");
	map->t.exit = mlx_load_png("textures/stairs_closed.png");
	map->t.exit_open = mlx_load_png("textures/stairs2.png");
	map->enemy.texture[0] = mlx_load_png("textures/bat1.png");
	map->enemy.texture[1] = mlx_load_png("textures/bat2.png");
	map->enemy.texture[2] = mlx_load_png("textures/bat3.png");
	map->enemy.texture[3] = mlx_load_png("textures/bat4.png");
	map->enemy.mirror[0] = mlx_load_png("textures/bat1_m.png");
	map->enemy.mirror[1] = mlx_load_png("textures/bat2_m.png");
	map->enemy.mirror[2] = mlx_load_png("textures/bat3_m.png");
	map->enemy.mirror[3] = mlx_load_png("textures/bat4_m.png");
	if (!map->t.wall || !map->t.floor || !map->t.coin
		|| !map->t.exit || !map->t.exit_open
		|| !check_e_textures(map))
		return (delete_textures(map), delete_p_texture(map), 0);
	map->img.enemy = mlx_texture_to_image(map->mlx, map->enemy.texture[0]);
	map->img.wall = mlx_texture_to_image(map->mlx, map->t.wall);
	map->img.floor = mlx_texture_to_image(map->mlx, map->t.floor);
	map->img.collectible = mlx_texture_to_image(map->mlx, map->t.coin);
	map->img.exit_img = mlx_texture_to_image(map->mlx, map->t.exit);
	map->img.exit_open = mlx_texture_to_image(map->mlx, map->t.exit_open);
	return (1);
}

static void	load_img_to_window(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			img_loading(map, i, j);
			j++;
		}
		i++;
	}
}

static int	load_p_img(t_map *map)
{
	map->player.textures[0] = mlx_load_png("textures/samurai000.png");
	map->player.textures[1] = mlx_load_png("textures/samurai001.png");
	map->player.textures[2] = mlx_load_png("textures/samurai002.png");
	map->player.textures[3] = mlx_load_png("textures/samurai003.png");
	map->player.textures[4] = mlx_load_png("textures/samurai004.png");
	map->player.textures[5] = mlx_load_png("textures/samurai005.png");
	map->player.run[0] = mlx_load_png("textures/samurai_run000.png");
	map->player.run[1] = mlx_load_png("textures/samurai_run001.png");
	map->player.run[2] = mlx_load_png("textures/samurai_run002.png");
	map->player.run[3] = mlx_load_png("textures/samurai_run003.png");
	map->player.run[4] = mlx_load_png("textures/samurai_run004.png");
	map->player.run[5] = mlx_load_png("textures/samurai_run005.png");
	map->player.run[6] = mlx_load_png("textures/samurai_run006.png");
	map->player.run[7] = mlx_load_png("textures/samurai_run007.png");
	map->player.run_left[0] = mlx_load_png("textures/samurai_run000_m.png");
	map->player.run_left[1] = mlx_load_png("textures/samurai_run001_m.png");
	map->player.run_left[2] = mlx_load_png("textures/samurai_run002_m.png");
	map->player.run_left[3] = mlx_load_png("textures/samurai_run003_m.png");
	map->player.run_left[4] = mlx_load_png("textures/samurai_run004_m.png");
	map->player.run_left[5] = mlx_load_png("textures/samurai_run005_m.png");
	map->player.run_left[6] = mlx_load_png("textures/samurai_run006_m.png");
	map->player.run_left[7] = mlx_load_png("textures/samurai_run007_m.png");
	if (!check_p_texture(map))
		return (delete_p_texture(map), 0);
	return (1);
}

static void	get_instances_for_keys(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->img.coin_instances = malloc(sizeof(uint32_t *) * map->y);
	while (i < map->y)
	{
		j = 0;
		map->img.coin_instances[i] = malloc(sizeof(uint32_t) * map->x);
		while (j < map->x)
		{
			map->img.coin_instances[i][j] = 4294967295;
			j++;
		}
		i++;
	}
}

int	map_render(t_map *map)
{
	map->mlx = mlx_init(PIXEL * map->x, PIXEL * map->y, "so_long", true);
	if (!map->mlx)
		return (0);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	get_instances_for_keys(map);
	if (!load_p_img(map) || !load_another_img(map))
		return (0);
	map->img.player_img = mlx_texture_to_image(map->mlx,
			map->player.textures[0]);
	map->img.moves = mlx_put_string(map->mlx, "0", 64, 64);
	if (!check_delete_imgs(map))
		return (0);
	load_img_to_window(map);
	initialize_player_enemy(map);
	return (1);
}
