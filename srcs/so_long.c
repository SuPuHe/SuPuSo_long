/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/06 13:01:29 by omizin           ###   ########.fr       */
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
			return (ft_printf("Error: Side wall missing at row %d\n", i), 0);
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

int	main(int argc, char **argv)
{
	char	*map;
	t_map	map_struct;

	map_struct = (t_map){0, 0, 0, 0};
	if (argc != 2)
		return (ft_printf("Error: argc is not 2\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
		return (ft_printf("map is not in .ber format\n", 1));
	map = ft_get_map(argv[1]);
	if (!map)
		return (free_all_gnl(), 1);
	ft_printf("%s\n%d\n", map, ft_strlen(map));
	if (ft_map_check(map, &map_struct) == 1 )
		return (free(map), free_all_gnl(), 1);
	char **lines = split_map_into_lines(map);
	int width = ft_strlen(lines[0]);
	ft_printf("%d\n", width);
	if (!is_surrounded_by_walls(lines, map_struct.height, width))
		return (free(map), free_split(lines), 1);
	free_split(lines);
	free(map);
	return (0);
}
