/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:29:15 by omizin            #+#    #+#             */
/*   Updated: 2025/05/15 22:30:09 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*read_and_join_lines(int fd, char *first_line, t_map *map,
unsigned long x)
{
	char	*line;
	char	*joined;
	char	*tmp;

	if (x != ft_strlen(first_line) - 1)
		return (free(first_line), NULL);
	joined = ft_strdup(first_line);
	map->y++;
	free(first_line);
	if (!joined)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (x != ft_strlen(line) - 1)
			return (ft_printf("map is assymethric\n"), free(line),
				free(joined), NULL);
		tmp = ft_strjoin(joined, line);
		free(joined);
		joined = tmp;
		map->y++;
		free(line);
		line = get_next_line(fd);
	}
	return (joined);
}

int	ft_get_map(char *argv, t_map *map)
{
	int				fd;
	char			*line;
	char			*joined;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error with map name/path\n"), 1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf("Empty map or read error\n"), 1);
	map->y = 0;
	map->x = ft_strlen(line) - 1;
	joined = read_and_join_lines(fd, line, map, map->x);
	if (!joined)
		return (close(fd), free_all_gnl(), 1);
	map->map = ft_split(joined, '\n');
	map->copy_map = ft_split(joined, '\n');
	free(joined);
	if (!map->map || !map->copy_map)
	{
		cleanup_map(map);
		return (1);
	}
	close(fd);
	return (0);
}

static int	ft_map_values_check(t_map *map, int x, int y)
{
	if (map->map[y][x] == 'C')
		map->coin++;
	else if (map->map[y][x] == 'P')
		map->player++;
	else if (map->map[y][x] == 'E')
		map->exit++;
	else if (map->map[y][x] == '0' || map->map[y][x] == '1' || map->map[y][x] == 'B')
		;
	else
		return (ft_printf("Wrong map |%c|\n", map->map[y][x]), 1);
	return (0);
}

int	ft_map_check(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (ft_map_values_check(map, x, y) == 1)
				return (1);
			x++;
		}
		y++;
	}
	if (map->coin < 1 || map->player != 1 || map->exit != 1)
		return (ft_printf("Error: Incorrect map content \n"), 1);
	else
		return (0);
}
