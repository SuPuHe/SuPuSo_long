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
		if (map->player_textures[i])
			mlx_delete_texture(map->player_textures[i]);
		i++;
	}
	// ft_printf("Deleting %d textures\n", map->coin_check);
	// if (texture->player)
	// 	mlx_delete_texture(texture->player);
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
	mlx_image_to_window(map->mlx, map->floor, x, y);
	if (map->map[i][j] == 'P')
	{
		mlx_image_to_window(map->mlx, map->player_img, x, y);
	}
	else if (map->map[i][j] == '1')
	{
		mlx_image_to_window(map->mlx, map->wall, x, y);
	}
	else if (map->map[i][j] == 'C')
		mlx_image_to_window(map->mlx, map->collectible, x, y);
	else if (map->map[i][j] == 'E')
		mlx_image_to_window(map->mlx, map->exit_img, x, y);
	else if (map->map[i][j] == 'B')
		mlx_image_to_window(map->mlx, map->enemy, x, y);
}

int	map_render(t_map *map)
{
	t_texture	texture;

	map->mlx = mlx_init(PIXEL * map->x, PIXEL * map->y, "so_long", true);
	if (!map->mlx)
		return (1);

	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	//texture.player = mlx_load_png("textures/player_imresizer.png");
	texture.enemy = mlx_load_png("textures/enemy.png");
	texture.wall = mlx_load_png("textures/wall_imresizer.png");
	texture.floor = mlx_load_png("textures/floor_imresizer.png");
	texture.coin = mlx_load_png("textures/coin_imresizer.png");
	texture.exit = mlx_load_png("textures/player_imresizer_exit.png");
	// map->player_textures[0] = mlx_load_png("textures/enemy.png");
	// map->player_textures[1] = mlx_load_png("textures/player_imresizer_exit.png");
	// map->player_textures[2] = mlx_load_png("textures/coin_imresizer.png");
	// map->player_textures[3] = mlx_load_png("textures/player_imresizer.png");
	map->player_textures[0] = mlx_load_png("textures/tile000.png");
	map->player_textures[1] = mlx_load_png("textures/tile001.png");
	map->player_textures[2] = mlx_load_png("textures/tile002.png");
	map->player_textures[3] = mlx_load_png("textures/tile003.png");
	map->player_textures[4] = mlx_load_png("textures/tile004.png");
	map->player_textures[5] = mlx_load_png("textures/tile005.png");


	map->player_img = mlx_texture_to_image(map->mlx, map->player_textures[0]);
	mlx_image_to_window(map->mlx, map->player_img, map->player_x * PIXEL, map->player_y * PIXEL);

	map->player_frame = 0;
	map->frame_counter = 0;
	if (!texture.coin || !texture.exit || !texture.enemy || !texture.floor
		|| !map->player_textures[0] || !texture.wall)
	{
		delete_textures(&texture, map);
		mlx_terminate(map->mlx);
		return (1);
	}
	// map->player_img = mlx_texture_to_image(map->mlx, texture.player);
	// mlx_delete_texture(texture.player);
	map->wall = mlx_texture_to_image(map->mlx, texture.wall);
	mlx_delete_texture(texture.wall);
	map->floor = mlx_texture_to_image(map->mlx, texture.floor);
	mlx_delete_texture(texture.floor);
	map->collectible = mlx_texture_to_image(map->mlx, texture.coin);
	mlx_delete_texture(texture.coin);
	map->exit_img = mlx_texture_to_image(map->mlx, texture.exit);
	mlx_delete_texture(texture.exit);
	map->enemy = mlx_texture_to_image(map->mlx, texture.enemy);
	mlx_delete_texture(texture.enemy);
	if (!map->player_img || !map->enemy || !map->collectible || !map->wall || !map->floor || !map->exit_img)
	{
		delete_textures(&texture, map);
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
	ft_printf("Moves: %d\n", ++map->moves);
	if (map->map[map->player_y + y][map->player_x + x] == '1')
		return ;
	if (map->map[map->player_y + y][map->player_x + x] == 'E' && map->coin_check == map->coin)
	{
		ft_printf("WIN\n");
		mlx_close_window(map->mlx);
	}
	if (map->map[map->player_y + y][map->player_x + x] == 'B')
		mlx_close_window(map->mlx);
	if (map->map[map->player_y + y][map->player_x + x] == 'C')
	{
		map->coin_check++;
		mlx_image_to_window(map->mlx, map->floor, (map->player_x + x) * PIXEL, (map->player_y + y) * PIXEL);
	}
	if (map->map[map->player_y][map->player_x] == 'E')
		mlx_image_to_window(map->mlx, map->exit_img, map->player_x * PIXEL, map->player_y * PIXEL);
	else
		mlx_image_to_window(map->mlx, map->floor, map->player_x * PIXEL, map->player_y * PIXEL);
	map->player_x = map->player_x + x;
	map->player_y = map->player_y + y;
	if (map->map[map->player_y][map->player_x] != 'E')
		map->map[map->player_y][map->player_x] = 'P';
	mlx_image_to_window(map->mlx, map->player_img, map->player_x * PIXEL, map->player_y * PIXEL);
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

void	delete_images(t_map *map)
{
	if (map->player_img)
		mlx_delete_image(map->mlx, map->player_img);
	if (map->wall)
		mlx_delete_image(map->mlx, map->wall);
	if (map->floor)
		mlx_delete_image(map->mlx, map->floor);
	if (map->collectible)
		mlx_delete_image(map->mlx, map->collectible);
	if (map->exit_img)
		mlx_delete_image(map->mlx, map->exit_img);
	if (map->enemy)
		mlx_delete_image(map->mlx, map->enemy);
}

void	move_enemy(void *param)
{
	t_map	*map = (t_map *)param;
	int		dx;
	int		dy;
	char	next_tile;

	dx = 0;
	dy = 0;
	if (map->enemy_x < map->player_x)
		dx = 1;
	else if (map->enemy_x > map->player_x)
		dx = -1;
	if (map->enemy_y < map->player_y)
		dy = 1;
	else if (map->enemy_y > map->player_y)
		dy = -1;
	next_tile = map->map[map->enemy_y + dy][map->enemy_x + dx];
	if (next_tile == '1' || next_tile == 'E')
		return;
	if (map->enemy_under == 'C')
		mlx_image_to_window(map->mlx, map->collectible, map->enemy_x * PIXEL, map->enemy_y * PIXEL);
	else if (map->enemy_under == 'E')
		mlx_image_to_window(map->mlx, map->exit_img, map->enemy_x * PIXEL, map->enemy_y * PIXEL);
	else
		mlx_image_to_window(map->mlx, map->floor, map->enemy_x * PIXEL, map->enemy_y * PIXEL);
	map->enemy_x += dx;
	map->enemy_y += dy;
	map->enemy_under = map->map[map->enemy_y][map->enemy_x];
	if (map->enemy_x == map->player_x && map->enemy_y == map->player_y)
		mlx_close_window(map->mlx);
	mlx_image_to_window(map->mlx, map->enemy, map->enemy_x * PIXEL, map->enemy_y * PIXEL);
}

void	animate_player(void *param)
{
	t_map	*map = (t_map *)param;

	map->frame_counter++;
	if (map->frame_counter < 15)
		return ;
	map->frame_counter = 0;
	map->player_frame++;
	if (map->player_frame >= 6)
		map->player_frame = 0;
	mlx_delete_image(map->mlx, map->player_img);
	map->player_img = mlx_texture_to_image(map->mlx, map->player_textures[map->player_frame]);
	mlx_image_to_window(map->mlx, map->player_img,
		map->player_x * PIXEL, map->player_y * PIXEL);
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
	ft_printf("x: %d, y: %d\n", map->player_x, map->player_y);
	ft_printf("x: %d, y: %d\n", map->x, map->y);
	int y, x;
	y = 0;
	while(map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			ft_printf("%c", map->map[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	if (map_render(map) == 1)
	{
		delete_images(map);
		cleanup_map(map);
		free(map);
	}
	mlx_key_hook(map->mlx, key_handler, map);
	mlx_loop_hook(map->mlx, animate_player, map);
	//mlx_loop_hook(map->mlx, move_enemy, map);
	mlx_loop(map->mlx);
	ft_printf("HERE\n");
	mlx_terminate(map->mlx);
	delete_images(map);
	cleanup_map(map);
	free(map);
	return (0);
}
