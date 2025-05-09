/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:26:18 by omizin            #+#    #+#             */
/*   Updated: 2025/05/09 20:28:16 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_surrounded_by_walls(char **lines, int height, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (lines[0][i] <= '\r' || lines[height - 1][i] <= '\r')
			;
		else if (lines[0][i] != '1' || lines[height - 1][i] != '1')
			return (ft_printf("Error: Top or bottom border not walls\n"), 0);
		i++;
	}
	i = 1;
	while (i < height - 1)
	{
		if (lines[i][0] <= '\r' || lines[i][width - 1] <= '\r')
			;
		else if (lines[i][0] != '1' || lines[i][width - 1] != '1')
			return (ft_printf("Error: Side wall missing at row %d\n", i + 1), 0);
		i++;
	}
	return (1);
}

static void	flood_fill_count(t_map_copy *map_copy, int y, int x)
{
	if (y < 0 || y >= map_copy->height || x < 0 || x >= map_copy->width)
		return ;
	if (map_copy->map_copy[y][x] == '1' || map_copy->map_copy[y][x] == 'F')
		return ;
	if (map_copy->map_copy[y][x] == 'C')
		map_copy->coin++;
	else if (map_copy->map_copy[y][x] == 'E')
		map_copy->exit++;
	map_copy->map_copy[y][x] = 'F';
	flood_fill_count(map_copy, y + 1, x);
	flood_fill_count(map_copy, y - 1, x);
	flood_fill_count(map_copy, y, x + 1);
	flood_fill_count(map_copy, y, x - 1);
}

static int	check_path_error(t_map_copy *map_copy, t_map *map_struct, int height)
{
	if (map_copy->y == height)
		return (free_map(map_copy->map_copy), ft_printf("Error: Player not found\n"), 0);
	map_copy->coin = 0;
	map_copy->exit = 0;
	flood_fill_count(map_copy, map_copy->y, map_copy->x);
	if (map_copy->coin != map_struct->coin || map_copy->exit != 1)
	{
		ft_printf("Error: Not all coins or exit reachable. Coins found: %d, Exit found: %d\n",
			map_copy->coin, map_copy->exit);
		free_map(map_copy->map_copy);
		return (0);
	}
	return (1);
}

static int	check_path(char **original_map, t_map *map_struct, int height, int width)
{
	t_map_copy	map_copy;

	map_copy.map_copy = copy_map(original_map, height);
	if (!map_copy.map_copy)
		return (ft_printf("Error copying map\n"), 0);
	map_copy.y = 0;
	map_copy.height = height;
	map_copy.width = width;
	while (map_copy.y < height)
	{
		map_copy.x = 0;
		while (map_copy.x < width)
		{
			if (map_copy.map_copy[map_copy.y][map_copy.x] == 'P')
				break ;
			map_copy.x++;
		}
		if (map_copy.x < width)
			break ;
		map_copy.y++;
	}
	if (check_path_error(&map_copy, map_struct, height) == 0)
		return (0);
	free_map(map_copy.map_copy);
	return (1);
}

int	get_input(char *map, t_map *map_struct)
{
	char	**lines;
	int		width;

	if (ft_map_check(map, map_struct) == 1)
		return (free(map), free_all_gnl(), 1);
	ft_printf("%s\n", map);
	lines = split_map_into_lines(map);
	width = ft_strlen(lines[0]);
	if (!is_surrounded_by_walls(lines, map_struct->height, width))
		return (free(map), free_split(lines), 1);
	if (!check_path(lines, map_struct, map_struct->height, width))
		return (free(map), free_split(lines), 1);
	free_split(lines);
	return (0);
}
