/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:53:17 by omizin            #+#    #+#             */
/*   Updated: 2025/05/27 13:59:07 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_walkable(char tile)
{
	return (tile != '1');
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	end_logic(t_map *map)
{
	if (map->map[map->player.y][map->player.x] == 'E'
		&& map->coin_check == map->coin)
	{
		ft_printf("WIN\n");
		mlx_close_window(map->mlx);
	}
	else if (map->player.y == map->enemy.y && map->player.x == map->enemy.x)
	{
		ft_printf("LOSE\n");
		mlx_close_window(map->mlx);
	}
}
