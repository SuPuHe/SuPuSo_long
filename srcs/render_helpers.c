/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:39 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 17:22:54 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_p_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (map->player.textures[i])
			mlx_delete_texture(map->player.textures[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (map->player.run[i])
			mlx_delete_texture(map->player.run[i]);
		if (map->player.run_left[i])
			mlx_delete_texture(map->player.run_left[i]);
		i++;
	}
}

int	check_p_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!map->player.textures[i])
			return (0);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (!map->player.run[i] || !map->player.run_left[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_e_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->enemy.texture[i] || !map->enemy.mirror[i])
			return (0);
		i++;
	}
	return (1);
}

void	delete_textures(t_map *map)
{
	int	i;

	i = 0;
	if (map->t.wall)
		mlx_delete_texture(map->t.wall);
	if (map->t.floor)
		mlx_delete_texture(map->t.floor);
	if (map->t.coin)
		mlx_delete_texture(map->t.coin);
	if (map->t.exit)
		mlx_delete_texture(map->t.exit);
	if (map->t.exit_open)
		mlx_delete_texture(map->t.exit_open);
	while (i < 4)
	{
		if (map->enemy.texture[i])
			mlx_delete_texture(map->enemy.texture[i]);
		if (map->enemy.mirror[i])
			mlx_delete_texture(map->enemy.mirror[i]);
		i++;
	}
}

int	check_delete_imgs(t_map *map)
{
	int	helper;

	helper = 0;
	if (!map->img.wall || !map->img.floor || !map->img.collectible
		|| !map->img.exit_img || !map->img.exit_open || !map->img.enemy
		|| !map->img.player_img)
	{
		delete_textures(map);
		delete_p_texture(map);
		helper = 1;
	}
	if (helper == 1)
		return (delete_images(map), 0);
	return (1);
}
