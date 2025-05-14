/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:26:18 by omizin            #+#    #+#             */
/*   Updated: 2025/05/14 10:50:59 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_surrounded_by_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->x)
	{
		if (map->map[0][i] <= '\r' || map->map[map->y - 1][i] <= '\r')
			;
		else if (map->map[0][i] != '1' || map->map[map->y - 1][i] != '1')
			return (ft_printf("Error: Top or bottom border not walls\n"), 0);
		i++;
	}
	i = 1;
	while (i < map->y - 1)
	{
		if (map->map[i][0] <= '\r' || map->map[i][map->x - 1] <= '\r')
			;
		else if (map->map[i][0] != '1' || map->map[i][map->x - 1] != '1')
			return (ft_printf("Err: Side wall missing at row %d\n", i + 1), 0);
		i++;
	}
	return (1);
}

static void	flood_fill_count(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->y || x < 0 || x >= map->x)
		return ;
	if (map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'F')
		return ;
	if (map->copy_map[y][x] == 'C')
		map->coin_check++;
	else if (map->copy_map[y][x] == 'E')
		map->exit_check++;
	map->copy_map[y][x] = 'F';
	flood_fill_count(map, x + 1, y);
	flood_fill_count(map, x - 1, y);
	flood_fill_count(map, x, y + 1);
	flood_fill_count(map, x, y - 1);
}

static int	check_path_error(t_map *map, int x, int y)
{
	if (y == map->y)
	{
		ft_printf("Error: Player not found\n");
		return (0);
	}
	map->coin_check = 0;
	map->exit_check = 0;
	flood_fill_count(map, x, y);
	if (map->coin != map->coin_check || map->exit_check != 1)
	{
		ft_printf("Error: Not all coins or exit reachable. "
			"Coins found: %d, Exit found: %d\n", map->coin_check,
			map->exit_check);
		return (0);
	}
	return (1);
}

static int	check_path(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		map->player_y = y;
		while (x < map->x)
		{
			map->player_x = x;
			if (map->copy_map[y][x] == 'P')
				break ;
			x++;
		}
		if (x < map->x)
			break ;
		y++;
	}
	if (!check_path_error(map, x, y))
		return (free_split(map->copy_map), map->copy_map = NULL, 0);
	free_split(map->copy_map);
	map->copy_map = NULL;
	return (1);
}

int	get_input(t_map *map, char **argv, int argc)
{
	if (argc != 2)
		return (ft_printf("Error: argc is not 2\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
		return (ft_printf("Error: map is not in .ber format\n"), 1);
	if (ft_get_map(argv[1], map) == 1)
		return (1);
	if (ft_map_check(map) || !is_surrounded_by_walls(map) || !check_path(map))
	{
		cleanup_map(map);
		return (1);
	}
	return (0);
}
