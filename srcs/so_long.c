/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/20 14:12:53 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_textures(t_texture *texture, t_map *map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (map->player.textures[i])
			mlx_delete_texture(map->player.textures[i]);
		i++;
	}
	if (texture->enemy)
		mlx_delete_texture(texture->enemy);
	if (texture->wall)
		mlx_delete_texture(texture->wall);
	if (texture->floor)
		mlx_delete_texture(texture->floor);
	if (texture->coin)
		mlx_delete_texture(texture->coin);
	if (texture->exit)
		mlx_delete_texture(texture->exit);
}

void	img_loading(t_map *map, int i, int j)
{
	int	x;
	int	y;

	x = j * PIXEL;
	y = i * PIXEL;
	mlx_image_to_window(map->mlx, map->img.floor, x, y);
	if (map->map[i][j] == 'P')
		mlx_image_to_window(map->mlx, map->img.player_img, x, y);
	else if (map->map[i][j] == '1')
		mlx_image_to_window(map->mlx, map->img.wall, x, y);
	else if (map->map[i][j] == 'C')
		mlx_image_to_window(map->mlx, map->img.collectible, x, y);
	else if (map->map[i][j] == 'E')
		mlx_image_to_window(map->mlx, map->img.exit_img, x, y);
	else if (map->map[i][j] == 'B')
		mlx_image_to_window(map->mlx, map->img.enemy, x, y);
}

int	map_render(t_map *map)
{
	t_texture	texture;

	map->mlx = mlx_init(PIXEL * map->x, PIXEL * map->y, "so_long", true);
	if (!map->mlx)
		return (1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	texture.enemy = mlx_load_png("textures/enemy.png");
	texture.wall = mlx_load_png("textures/wall_imresizer.png");
	texture.floor = mlx_load_png("textures/floor_imresizer.png");
	texture.coin = mlx_load_png("textures/coin_imresizer.png");
	texture.exit = mlx_load_png("textures/player_imresizer_exit.png");

	map->player.textures[0] = mlx_load_png("textures/tile000.png");
	map->player.textures[1] = mlx_load_png("textures/tile001.png");
	map->player.textures[2] = mlx_load_png("textures/tile002.png");
	map->player.textures[3] = mlx_load_png("textures/tile003.png");
	map->player.textures[4] = mlx_load_png("textures/tile004.png");
	map->player.textures[5] = mlx_load_png("textures/tile005.png");

	map->player.run[0] = mlx_load_png("textures/run000.png");
	map->player.run[1] = mlx_load_png("textures/run001.png");
	map->player.run[2] = mlx_load_png("textures/run002.png");
	map->player.run[3] = mlx_load_png("textures/run003.png");
	map->player.run[4] = mlx_load_png("textures/run004.png");
	map->player.run[5] = mlx_load_png("textures/run005.png");
	map->player.run[6] = mlx_load_png("textures/run006.png");
	map->player.run[7] = mlx_load_png("textures/run007.png");

	map->img.player_img = mlx_texture_to_image(map->mlx, map->player.textures[0]);
	mlx_image_to_window(map->mlx, map->img.player_img,
		map->player.x * PIXEL, map->player.y * PIXEL);

	map->player.frame = 0;
	map->player.frame_counter = 0;

	if (!texture.coin || !texture.exit || !texture.enemy || !texture.floor
		|| !map->player.textures[0] || !texture.wall)
	{
		delete_textures(&texture, map);
		mlx_terminate(map->mlx);
		return (1);
	}

	map->img.wall = mlx_texture_to_image(map->mlx, texture.wall);
	mlx_delete_texture(texture.wall);
	map->img.floor = mlx_texture_to_image(map->mlx, texture.floor);
	mlx_delete_texture(texture.floor);
	map->img.collectible = mlx_texture_to_image(map->mlx, texture.coin);
	mlx_delete_texture(texture.coin);
	map->img.exit_img = mlx_texture_to_image(map->mlx, texture.exit);
	mlx_delete_texture(texture.exit);
	map->img.enemy = mlx_texture_to_image(map->mlx, texture.enemy);
	mlx_delete_texture(texture.enemy);

	if (!map->img.player_img || !map->img.enemy || !map->img.collectible
		|| !map->img.wall || !map->img.floor || !map->img.exit_img)
	{
		delete_textures(&texture, map);
		mlx_terminate(map->mlx);
		return (1);
	}

	for (int i = 0; i < map->y; i++)
		for (int j = 0; j < map->x; j++)
			img_loading(map, i, j);
	return (0);
}

void	move_player(t_map *map, int x, int y)
{
	ft_printf("Moves: %d\n", ++map->moves);
	if (map->map[map->player.y + y][map->player.x + x] == '1')
		return ;
	if (map->map[map->player.y + y][map->player.x + x] == 'E'
		&& map->coin_check == map->coin)
	{
		ft_printf("WIN\n");
		mlx_close_window(map->mlx);
	}
	if (map->map[map->player.y + y][map->player.x + x] == 'B')
		mlx_close_window(map->mlx);
	if (map->map[map->player.y + y][map->player.x + x] == 'C')
	{
		map->coin_check++;
		mlx_image_to_window(map->mlx, map->img.floor,
			(map->player.x + x) * PIXEL, (map->player.y + y) * PIXEL);
	}
	if (map->map[map->player.y][map->player.x] == 'E')
		mlx_image_to_window(map->mlx, map->img.exit_img,
			map->player.x * PIXEL, map->player.y * PIXEL);
	else
		mlx_image_to_window(map->mlx, map->img.floor,
			map->player.x * PIXEL, map->player.y * PIXEL);

	map->player.x += x;
	map->player.y += y;
	if (map->map[map->player.y][map->player.x] != 'E')
		map->map[map->player.y][map->player.x] = 'P';
	mlx_image_to_window(map->mlx, map->img.player_img,
		map->player.x * PIXEL, map->player.y * PIXEL);
	ft_printf("PLAYER x: %d, y: %d\n", map->player.x, map->player.y);
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
	if (map->img.enemy)
		mlx_delete_image(map->mlx, map->img.enemy);
}

void	move_enemy(t_map *map)
{
	int dx = 0;
	int dy = 0;

	// Determine the direction
	if (map->enemy.x < map->player.x)
		dx = 1;
	else if (map->enemy.x > map->player.x)
		dx = -1;
	if (map->enemy.y < map->player.y)
		dy = 1;
	else if (map->enemy.y > map->player.y)
		dy = -1;
	if (abs(map->enemy.x - map->player.x) > abs(map->enemy.y - map->player.y))
		dy = 0;
	else
		dx = 0;
	if (map->map[map->enemy.y + dy][map->enemy.x + dx] == '1')
		return;
	if (map->map[map->enemy.y][map->enemy.x] == 'B')
		map->map[map->enemy.y][map->enemy.x] = '0';
	mlx_image_to_window(map->mlx, map->img.floor, map->enemy.x * PIXEL, map->enemy.y * PIXEL);
	map->enemy.x += dx;
	map->enemy.y += dy;
	if (map->enemy.x == map->player.x && map->enemy.y == map->player.y)
		mlx_close_window(map->mlx);
	map->map[map->enemy.y][map->enemy.x] = 'B';
	mlx_image_to_window(map->mlx, map->img.enemy, map->enemy.x * PIXEL, map->enemy.y * PIXEL);
}


void	animate_player(void *param)
{
	t_map	*map = (t_map *)param;

	map->player.frame_counter++;
	if (map->player.frame_counter < 100)
		return ;
	map->player.frame_counter = 0;
	map->player.frame++;
	if (map->player.frame >= 6)
		map->player.frame = 0;
	mlx_delete_image(map->mlx, map->img.player_img);
	map->img.player_img = mlx_texture_to_image(map->mlx,
		map->player.textures[map->player.frame]);
	mlx_image_to_window(map->mlx, map->img.player_img,
		map->player.x * PIXEL, map->player.y * PIXEL);
	move_enemy(map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (1);
	if (get_input(map, argv, argc))
		return (free(map), 1);
	if (map_render(map) == 1)
	{
		delete_images(map);
		cleanup_map(map);
		free(map);
		return (1);
	}
	mlx_key_hook(map->mlx, key_handler, map);
	mlx_loop_hook(map->mlx, animate_player, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	// delete_images(map);
	// cleanup_map(map);
	// free(map);
	return (0);
}
