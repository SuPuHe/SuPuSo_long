/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:50:18 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 17:34:58 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_move_counter(t_map *map, int x, int y)
{
	char	buf[12];
	int		len = 0;
	int		tmp = map->moves;
	int		i;
	int		pos_x = x;
	mlx_image_t	*img;

	if (tmp == 0)
		buf[len++] = '0';
	else
	{
		while (tmp > 0 && len < 11)
		{
			buf[len++] = (tmp % 10) + '0';
			tmp /= 10;
		}
	}
	for (i = len - 1; i >= 0; i--)
	{
		int digit = buf[i] - '0';
		img = mlx_texture_to_image(map->mlx, map->t.num[digit]);
		mlx_resize_image(img, 32, 32);
		mlx_image_to_window(map->mlx, img, pos_x, y);
		pos_x += 32;
	}
}

static void	update_player_pos_and_moves(t_map *map, int dx, int dy)
{
	//char	*moves_str;

	map->player.state = RUN;
	map->player.target_pixel_x = (map->player.x + dx) * PIXEL;
	map->player.target_pixel_y = (map->player.y + dy) * PIXEL;
	map->player.is_moving = 1;
	map->player.x += dx;
	map->player.y += dy;
	map->moves++;
	//if (map->img.moves)
	//	mlx_delete_image(map->mlx, map->img.moves);
	//moves_str = (ft_itoa(++map->moves));
	//map->img.moves = mlx_put_string(map->mlx, moves_str, 64, 64);
	//free(moves_str);
}

void	move_player(t_map *map, int dx, int dy)
{
	uint32_t	coin_idx;

	if (map->player.is_moving)
		return ;
	if (map->map[map->player.y + dy][map->player.x + dx] == '1')
		return ;
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
	render_move_counter(map, 64, 64);
}

static void	prepare_p_movement(t_player *p)
{
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
		if (ft_abs(p->pixel_x - p->target_pixel_x) <= p->move_speed
			&& ft_abs(p->pixel_y - p->target_pixel_y) <= p->move_speed)
		{
			p->pixel_x = p->target_pixel_x;
			p->pixel_y = p->target_pixel_y;
			p->is_moving = 0;
			p->state = IDLE;
		}
	}
}

static void	p_animation_cycle(t_player *p, int max_frames,
t_map *map, mlx_texture_t **anim)
{
	p->frame_counter++;
	if (p->frame_counter > 20)
	{
		p->frame_counter = 0;
		p->frame++;
		if (p->frame >= max_frames)
			p->frame = 0;
	}
	mlx_delete_image(map->mlx, map->img.player_img);
	map->img.player_img = mlx_texture_to_image(map->mlx, anim[p->frame]);
	mlx_image_to_window(map->mlx, map->img.player_img, p->pixel_x, p->pixel_y);
}

void	animate_player(void *param)
{
	t_map			*map;
	t_player		*p;
	mlx_texture_t	**anim;
	int				max_frames;
	static int		move_timer = 0;

	map = (t_map *)param;
	p = &map->player;
	if (p->state == RUN)
		anim = p->run;
	else
		anim = p->textures;
	if (p->dir == LEFT && p->state == RUN)
		anim = p->run_left;
	if (p->state == RUN)
		max_frames = 8;
	else
		max_frames = 6;
	prepare_p_movement(p);
	p_animation_cycle(p, max_frames, map, anim);
	if (++move_timer > 1)
	{
		move_enemy(map);
		move_timer = 0;
	}
}
