/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/07 12:48:34 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_all_gnl(void)
{
	int				fd;
	t_gnl			*gnl;
	static t_gnl	**gnl_array_ptr;

	gnl_array_ptr = NULL;
	if (!gnl_array_ptr)
		gnl_array_ptr = (t_gnl **)get_gnl_array();
	fd = 0;
	while (fd < 1024)
	{
		gnl = gnl_array_ptr[fd];
		if (gnl)
		{
			if (gnl->buf)
				free(gnl->buf);
			free(gnl);
			gnl_array_ptr[fd] = NULL;
		}
		fd++;
	}
}

char	*ft_get_map(char *argv)
{
	int				fd;
	unsigned long	width;
	char			*line;
	char			*joined;
	char			*tmp;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error with map name/path\n"), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf("Empty map or read error\n"), NULL);
	joined = ft_strdup("");
	width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if (width != ft_strlen(line) - 1)
			return (free(line), free(joined), close(fd), ft_printf("Error: Map is assymetric\n"), NULL);
		tmp = ft_strjoin(joined, line);
		free(joined);
		joined = tmp;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (joined);
}

int	ft_map_check(char *map, t_map *map_struct)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i] == 'C')
			map_struct->coin++;
		else if (map[i] == 'P')
			map_struct->player++;
		else if (map[i] == 'E')
			map_struct->exit++;
		else if (map[i] == '\n')
			map_struct->height++;
		else if (map[i] == '0' || map[i] == '1' || map[i] == '\r')
			;
		else
			return (ft_printf("Wrong map |%c|\n", map[i]), 1);
		i++;
	}
	if (map_struct->coin < 1 || map_struct->player != 1 || map_struct->exit != 1)
		return (ft_printf("Error: Incorrect map content \n"), 1);
	else
		return (0);
}

int	is_surrounded_by_walls(char **lines, int height, int width)
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

char	**split_map_into_lines(char *map)
{
	char	**lines;

	lines = ft_split(map, '\n');
	return (lines);
}

static void	free_split(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

void	flood_fill_count(char **map, int y, int x, int h, int w, int *coins, int *exit)
{
	if (y < 0 || y >= h || x < 0 || x >= w)
		return;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return;
	if (map[y][x] == 'C')
		(*coins)++;
	else if (map[y][x] == 'E')
		(*exit)++;
	map[y][x] = 'F';
	flood_fill_count(map, y + 1, x, h, w, coins, exit);
	flood_fill_count(map, y - 1, x, h, w, coins, exit);
	flood_fill_count(map, y, x + 1, h, w, coins, exit);
	flood_fill_count(map, y, x - 1, h, w, coins, exit);
}

int	check_path(char **original_map, t_map *map_struct, int height, int width)
{
	char	**map_copy;
	int		y, x;
	int		coins_found = 0;
	int		exit_found = 0;

	map_copy = copy_map(original_map, height);
	if (!map_copy)
		return (ft_printf("Error copying map\n"), 0);

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map_copy[y][x] == 'P')
				break ;
			x++;
		}
		if (x < width)
			break ;
		y++;
	}
	if (y == height)
		return (free_map(map_copy), ft_printf("Error: Player not found\n"), 0);

	// Modified flood fill to update counters by reference
	flood_fill_count(map_copy, y, x, height, width, &coins_found, &exit_found);

	if (coins_found != map_struct->coin || exit_found != 1)
	{
		ft_printf("Error: Not all coins or exit reachable. Coins found: %d, Exit found: %d\n",
			coins_found, exit_found);
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*map;
	t_map	map_struct;
	char	**lines;
	int		width;

	map_struct = (t_map){0, 0, 0, 0};
	if (argc != 2)
		return (ft_printf("Error: argc is not 2\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
		return (ft_printf("map is not in .ber format\n", 1));
	map = ft_get_map(argv[1]);
	if (!map)
		return (free_all_gnl(), 1);
	if (ft_map_check(map, &map_struct) == 1 )
		return (free(map), free_all_gnl(), 1);
	ft_printf("%s\n", map);
	lines = split_map_into_lines(map);
	width = ft_strlen(lines[0]);
	if (!is_surrounded_by_walls(lines, map_struct.height, width))
		return (free(map), free_split(lines), 1);
	if (!check_path(lines, &map_struct, map_struct.height, width))
		return (free(map), free_split(lines), 1);
	free_split(lines);
	free(map);
	return (0);
}
