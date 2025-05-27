/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:58:22 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 13:58:50 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_path_to_player(t_enemy *e, t_map *map, int *dx, int *dy)
{
	if (e->is_moving)
		return ;
	if (e->x < map->player.x)
		map->enemy.p_dx = 1;
	else if (e->x > map->player.x)
		map->enemy.p_dx = -1;
	if (e->y < map->player.y)
		map->enemy.p_dy = 1;
	else if (e->y > map->player.y)
		map->enemy.p_dy = -1;
	if (ft_abs(e->x - map->player.x) > ft_abs(e->y - map->player.y))
	{
		*dx = map->enemy.p_dx;
		*dy = 0;
		map->enemy.s_dx = 0;
		map->enemy.s_dy = map->enemy.p_dy;
	}
	else
	{
		*dx = 0;
		*dy = map->enemy.p_dy;
		map->enemy.s_dx = map->enemy.p_dx;
		map->enemy.s_dy = 0;
	}
}

static void	update_enemy_pos(t_map *map, t_enemy *e, int dx, int dy)
{
	map->enemy.p_dx = 0;
	map->enemy.p_dy = 0;
	map->enemy.s_dx = 0;
	map->enemy.s_dy = 0;
	find_path_to_player(e, map, &dx, &dy);
	if (is_walkable(map->map[e->y + dy][e->x + dx]))
	{
		e->x += dx;
		e->y += dy;
	}
	else if (is_walkable(map->map[e->y + map->enemy.s_dy]
			[e->x + map->enemy.s_dx]))
	{
		e->x += map->enemy.s_dx;
		e->y += map->enemy.s_dy;
	}
	else
		return ;
	if (dx < 0 || map->enemy.s_dx < 0)
		e->dir = LEFT;
	else if (dx > 0 || map->enemy.s_dx > 0)
		e->dir = RIGHT;
}

void	move_enemy(t_map *map)
{
	t_enemy	*e;
	int		dx;
	int		dy;

	dx = 0;
	dy = 0;
	e = &map->enemy;
	update_enemy_pos(map, e, dx, dy);
	if (e->x == map->player.x && e->y == map->player.y)
	{
		ft_printf("LOSE\n");
		mlx_close_window(map->mlx);
	}
	e->target_pixel_x = e->x * PIXEL;
	e->target_pixel_y = e->y * PIXEL;
	e->is_moving = 1;
}

static void	prepare_e_movement(t_enemy *e)
{
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
		if (ft_abs(e->pixel_x - e->target_pixel_x) <= e->move_speed
			&& ft_abs(e->pixel_y - e->target_pixel_y) <= e->move_speed)
		{
			e->pixel_x = e->target_pixel_x;
			e->pixel_y = e->target_pixel_y;
			e->is_moving = 0;
		}
	}
}

void	animate_enemy(void *param)
{
	t_map			*map;
	t_enemy			*e;
	mlx_texture_t	**anim;
	uint32_t		idx;

	map = (t_map *)param;
	e = &map->enemy;
	if (e->dir == LEFT)
		anim = e->mirror;
	else
		anim = e->texture;
	prepare_e_movement(e);
	e->frame_counter++;
	if (e->frame_counter > 20)
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
