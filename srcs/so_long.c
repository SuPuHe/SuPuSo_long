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

static void	key_a_d(mlx_key_data_t keydata, t_map *map)
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

static void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
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

// void	check_leaks(void)
// {
// 	system("leaks so_long");
// }
// 	atexit(check_leaks);
int	main(int argc, char **argv)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (1);
	if (get_input(map, argv, argc))
		return (free(map), 1);
	if (!map_render(map))
	{
		cleanup_map(map);
		free(map);
		return (1);
	}
	mlx_key_hook(map->mlx, key_handler, map);
	mlx_loop_hook(map->mlx, animate_player, map);
	mlx_loop_hook(map->mlx, animate_enemy, map);
	mlx_loop(map->mlx);
	delete_textures(map);
	delete_p_texture(map);
	delete_images(map);
	mlx_terminate(map->mlx);
	cleanup_map(map);
	free(map);
	return (0);
}
