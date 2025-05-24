/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/23 16:25:54 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <math.h>

void	delete_textures(t_texture *texture, t_map *map)
{
	// int	i;

	// i = 0;
	map->coin = map->coin;
	// while (i < 6)
	// {
	// 	if (map->player.textures[i])
	// 		mlx_delete_texture(map->player.textures[i]);
	// 	i++;
	// }
	// if (texture->enemy)
	// 	mlx_delete_texture(texture->enemy);
	if (texture->wall)
		mlx_delete_texture(texture->wall);
	if (texture->floor)
		mlx_delete_texture(texture->floor);
	if (texture->coin)
		mlx_delete_texture(texture->coin);
	if (texture->exit)
		mlx_delete_texture(texture->exit);
}

void	img_load_exit_enemy(t_map *map, int i, int j, uint32_t idx)
{
	if (map->map[i][j] == 'E')
	{
		idx = mlx_image_to_window(map->mlx, map->img.exit_img, j * PIXEL, i * PIXEL);
		map->img.exit_img->instances[idx].z = 2;
		idx = mlx_image_to_window(map->mlx, map->img.exit_open, j * PIXEL, i * PIXEL);
		map->img.exit_open->instances[idx].z = 1;
	}
	else if (map->map[i][j] == 'B')
	{
		idx = mlx_image_to_window(map->mlx, map->img.enemy,j * PIXEL, i * PIXEL);
		map->img.enemy->instances[idx].z = 3;
	}
}

void	img_loading(t_map *map, int i, int j)
{
	int	x;
	int	y;
	uint32_t	idx;

	x = j * PIXEL;
	y = i * PIXEL;
	idx = mlx_image_to_window(map->mlx, map->img.floor, x, y);
	map->img.floor->instances[idx].z = 0;
	if (map->map[i][j] == 'P')
		idx = mlx_image_to_window(map->mlx, map->img.player_img, x, y);
	else if (map->map[i][j] == '1')
	{
		idx = mlx_image_to_window(map->mlx, map->img.wall, x, y);
		map->img.wall->instances[idx].z = 1;
	}
	else if (map->map[i][j] == 'C')
	{
		idx = mlx_image_to_window(map->mlx, map->img.collectible, x, y);
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

int	map_render(t_map *map)
{
	t_texture	texture;

	//ft_printf("Map size: %d x %d\n", map->x, map->y);
	map->mlx = mlx_init(PIXEL * map->x, PIXEL * map->y, "so_long", true);
	if (!map->mlx)
		return (1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	map->img.coin_instances = malloc(sizeof(uint32_t *) * map->y);
	for (int i = 0; i < map->y; i++)
	{
		map->img.coin_instances[i] = malloc(sizeof(uint32_t) * map->x);
		for (int j = 0; j < map->x; j++)
			map->img.coin_instances[i][j] = 4294967295; // invalid default
	}

	texture.wall = mlx_load_png("textures/wall_dungeon.png");
	texture.floor = mlx_load_png("textures/floor_dungeon2.png");
	texture.coin = mlx_load_png("textures/key2.png");
	texture.exit = mlx_load_png("textures/stairs_closed.png");
	texture.exit_open = mlx_load_png("textures/stairs2.png");

	map->enemy.texture[0] = mlx_load_png("textures/bat1.png");
	map->enemy.texture[1] = mlx_load_png("textures/bat2.png");
	map->enemy.texture[2] = mlx_load_png("textures/bat3.png");
	map->enemy.texture[3] = mlx_load_png("textures/bat4.png");

	map->enemy.mirror[0] = mlx_load_png("textures/bat1_m.png");
	map->enemy.mirror[1] = mlx_load_png("textures/bat2_m.png");
	map->enemy.mirror[2] = mlx_load_png("textures/bat3_m.png");
	map->enemy.mirror[3] = mlx_load_png("textures/bat4_m.png");

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

	map->player.run_left[0] = mlx_load_png("textures/run000_m.png");
	map->player.run_left[1] = mlx_load_png("textures/run001_m.png");
	map->player.run_left[2] = mlx_load_png("textures/run002_m.png");
	map->player.run_left[3] = mlx_load_png("textures/run003_m.png");
	map->player.run_left[4] = mlx_load_png("textures/run004_m.png");
	map->player.run_left[5] = mlx_load_png("textures/run005_m.png");
	map->player.run_left[6] = mlx_load_png("textures/run006_m.png");
	map->player.run_left[7] = mlx_load_png("textures/run007_m.png");

	map->img.player_img = mlx_texture_to_image(map->mlx, map->player.textures[0]);
	//  mlx_image_to_window(map->mlx, map->img.player_img,
	// 	map->player.x * PIXEL, map->player.y * PIXEL);
	// mlx_set_instance_depth(map->img.player_img->instances, 1);

	map->img.enemy = mlx_texture_to_image(map->mlx, map->enemy.texture[0]);
	//  mlx_image_to_window(map->mlx, map->img.enemy,
	//  	map->enemy.x * PIXEL, map->enemy.y * PIXEL);
	// mlx_set_instance_depth(map->img.enemy->instances, 2);

	// if (!texture.coin || !texture.exit || !texture.floor
	// 	|| !map->player.textures[0] || !texture.wall)
	// {
	// 	delete_textures(&texture, map);
	// 	mlx_terminate(map->mlx);
	// 	return (1);
	// }

	map->img.wall = mlx_texture_to_image(map->mlx, texture.wall);
	mlx_delete_texture(texture.wall);
	map->img.floor = mlx_texture_to_image(map->mlx, texture.floor);
	mlx_delete_texture(texture.floor);
	map->img.collectible = mlx_texture_to_image(map->mlx, texture.coin);
	mlx_delete_texture(texture.coin);
	map->img.exit_img = mlx_texture_to_image(map->mlx, texture.exit);
	mlx_delete_texture(texture.exit);
	map->img.exit_open = mlx_texture_to_image(map->mlx, texture.exit_open);
	mlx_delete_texture(texture.exit_open);

	// if (!map->img.player_img || !map->img.enemy || !map->img.collectible
	// 	|| !map->img.wall || !map->img.floor || !map->img.exit_img)
	// {
	// 	delete_textures(&texture, map);
	// 	mlx_terminate(map->mlx);
	// 	return (1);
	// }

	int i, j;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			img_loading(map, i, j);
			j++;
		}
		i++;
	}
	initialize_player_enemy(map);
	map->img.moves = mlx_put_string(map->mlx, "0", 64, 64);
	return (0);
}

void	update_player_pos_and_moves(t_map *map, int dx, int dy)
{
	map->player.state = RUN;
	map->player.target_pixel_x = (map->player.x + dx) * PIXEL;
	map->player.target_pixel_y = (map->player.y + dy) * PIXEL;
	map->player.is_moving = 1;
	map->player.x += dx;
	map->player.y += dy;
	if (map->img.moves)
		mlx_delete_image(map->mlx, map->img.moves);
	map->img.moves = mlx_put_string(map->mlx, ft_itoa(++map->moves), 64, 64);
}

void	end_logic(t_map *map)
{
	if (map->map[map->player.y][map->player.x] == 'E'
		&& map->coin_check == map->coin)
	{
		ft_printf("WIN\n");
		mlx_close_window(map->mlx);
	}
	else if (map->map[map->player.y][map->player.x] == 'B')
	{
		ft_printf("LOSE\n");
		mlx_close_window(map->mlx);
	}
}

void	move_player(t_map *map, int dx, int dy)
{
	uint32_t	coin_idx;

	if (map->player.is_moving)
		return;
	if (map->map[map->player.y + dy][map->player.x + dx] == '1')
		return;
	update_player_pos_and_moves(map, dx, dy);
	if (map->map[map->player.y][map->player.x] == 'C')
	{
		coin_idx = map->img.coin_instances[map->player.y][map->player.x];
		map->img.collectible->instances[coin_idx].enabled = false;
		map->coin_check++;
		map->map[map->player.y][map->player.x] = '0';
		if (map->coin_check == map->coin)
			mlx_delete_image(map->mlx, map->img.exit_img);
	}
	end_logic(map);
	map->map[map->player.y][map->player.x] = 'P';
}

void	key_a_d(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
	{
		map->player.dir = LEFT;
		move_player(map, -1, 0);
	}
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
	{
		map->player.dir = RIGHT;
		move_player(map, 1, 0);
	}
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	// if (keydata.action != MLX_PRESS)
	// 	return ;
	if (map->player.is_moving)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		map->player.dir = RIGHT;
		move_player(map, 0, -1);
	}
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
	{
		map->player.dir = RIGHT;
		move_player(map, 0, 1);
	}
	key_a_d(keydata, map);
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

void	update_enemy_pos(t_map *map, t_enemy *e, int dx, int dy)
{
	if (e->is_moving)
		return;
	if (e->x < map->player.x)
		dx = 1;
	else if (e->x > map->player.x)
		dx = -1;
	if (e->y < map->player.y)
		dy = 1;
	else if (e->y > map->player.y)
		dy = -1;
	if (abs(e->x - map->player.x) > abs(e->y - map->player.y))
		dy = 0;
	else
		dx = 0;
	if (map->map[e->y + dy][e->x + dx] == '1')
		return;
	if (map->map[e->y][e->x] == 'B')
		map->map[e->y][e->x] = e->under;
	e->under = map->map[e->y + dy][e->x + dx];
	e->x += dx;
	e->y += dy;
	if (dx < 0)
		e->dir = LEFT;
	else if (dx > 0)
		e->dir = RIGHT;
}

void	move_enemy(t_map *map)
{
	t_enemy	*e;
	int		dx;
	int		dy;

	e = &map->enemy;
	dx = 0;
	dy = 0;
	update_enemy_pos(map, e, dx, dy);
	if (e->x == map->player.x && e->y == map->player.y)
	{
		ft_printf("LOSE\n");
		mlx_close_window(map->mlx);
	}
	map->map[e->y][e->x] = 'B';
	e->target_pixel_x = e->x * PIXEL;
	e->target_pixel_y = e->y * PIXEL;
	e->is_moving = 1;
}

void	animate_enemy(void *param)
{
	t_map	*map;
	t_enemy *e;
	mlx_texture_t **anim;
	uint32_t idx;

	map = (t_map *)param;
	e = &map->enemy;
	if (e->dir == LEFT)
		anim = e->mirror;
	else if (e->dir == RIGHT)
		anim = e->texture;
	if (e->is_moving)
	{
		if (e->pixel_x < e->target_pixel_x)
			e->pixel_x += e->move_speed;
		else if (e->pixel_x > e->target_pixel_x)
			e->pixel_x -= e->move_speed;
		if (e->pixel_y < e->target_pixel_y)
			e->pixel_y += e->move_speed;
		else if (e->pixel_y > e->target_pixel_y)
			e->pixel_y -= e->move_speed;
		if (abs(e->pixel_x - e->target_pixel_x) <= e->move_speed &&
			abs(e->pixel_y - e->target_pixel_y) <= e->move_speed)
		{
			e->pixel_x = e->target_pixel_x;
			e->pixel_y = e->target_pixel_y;
			e->is_moving = 0;
		}
	}
	e->frame_counter++;
	if (e->frame_counter > 25)
	{
		e->frame_counter = 0;
		e->frame++;
		if (e->frame >= 4)
			e->frame = 0;
	}
	mlx_delete_image(map->mlx, map->img.enemy);
	map->img.enemy = mlx_texture_to_image(map->mlx, anim[e->frame]);
	idx = mlx_image_to_window(map->mlx, map->img.enemy, e->pixel_x, e->pixel_y);
	map->img.enemy->instances[idx].z = 3;
}


void	animate_player(void *param)
{
	t_map	*map = (t_map *)param;
	t_player *p = &map->player;
	mlx_texture_t **anim = (p->state == RUN) ? p->run : p->textures;
	if (p->dir == LEFT && p->state == RUN)
		anim = p->run_left;
	int max_frames = (p->state == RUN) ? 8 : 6;
	//uint32_t idx;

	// Smooth movement

	if (p->is_moving)
	{
		if (p->pixel_x < p->target_pixel_x)
			p->pixel_x += p->move_speed;
		else if (p->pixel_x > p->target_pixel_x)
			p->pixel_x -= p->move_speed;
		if (p->pixel_y < p->target_pixel_y)
			p->pixel_y += p->move_speed;
		else if (p->pixel_y > p->target_pixel_y)
			p->pixel_y -= p->move_speed;

		if (abs(p->pixel_x - p->target_pixel_x) <= p->move_speed &&
			abs(p->pixel_y - p->target_pixel_y) <= p->move_speed)
		{
			p->pixel_x = p->target_pixel_x;
			p->pixel_y = p->target_pixel_y;
			p->is_moving = 0;
			p->state = IDLE; // Switch to idle after movement ends
		}
	}

	// Frame animation
	p->frame_counter++;
	if (p->frame_counter > 25)
	{
		p->frame_counter = 0;
		p->frame++;
		if (p->frame >= max_frames)
			p->frame = 0;
	}

	// Draw correct frame
	mlx_delete_image(map->mlx, map->img.player_img);
	map->img.player_img = mlx_texture_to_image(map->mlx, anim[p->frame]);
	mlx_image_to_window(map->mlx, map->img.player_img, p->pixel_x, p->pixel_y);
	//map->img.player_img->instances[idx].z = 1;
	static int move_timer = 0;
	if (++move_timer > 1)
	{
		move_enemy(map);
		move_timer = 0;
	}
}


void	cleanup_mapp(t_map *map)
{
	int	i;

	if (!map)
		return;
	if (map->map)
	{
		for (i = 0; map->map[i]; i++)
			free(map->map[i]);
		free(map->map);
	}
	if (map->img.coin_instances)
	{
		for (i = 0; i < map->y; i++)
			free(map->img.coin_instances[i]);
		free(map->img.coin_instances);
	}
	// if (map->mlx)
	// 	mlx_terminate(map->mlx);
	// delete_textures(&map->img, map);
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
		cleanup_mapp(map);
		free(map);
		return (1);
	}
	mlx_key_hook(map->mlx, key_handler, map);
	mlx_loop_hook(map->mlx, animate_player, map);
	mlx_loop_hook(map->mlx, animate_enemy, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	delete_images(map);
	cleanup_mapp(map);
	free(map);
	return (0);
}
